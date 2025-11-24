#!/usr/bin/env python3

"""
@file serial_to_db.py
@brief Stream YOLO detections from GAP9 to InfluxDB v2 and archive frames locally.

@details
This module implements a real-time data acquisition system for YOLO object detection
results transmitted over UART from a GAP9 microcontroller. It decodes framed serial
packets containing bounding box coordinates, JPEG image frames, and device logs, then
persists the data to both local filesystem and InfluxDB time-series database.

@author Mattia Consani
@date 2025
"""

import argparse
import configparser
import hashlib
import logging
import math
import signal
import struct
import sys
import time
from collections import deque
from datetime import datetime, timezone
from pathlib import Path
from typing import Callable, Deque, Dict, List, Optional, Tuple

import serial

import influxdb_client
from influxdb_client.client.write_api import SYNCHRONOUS

import picamera


# --------------- Constants  -------------

# InfluxDB Configuration
# Path to INI configuration file (config.ini)
_ini_path = Path(__file__).resolve().parent / "config.ini"

# InfluxDB authentication token (loaded from config.ini)
token: Optional[str] = None
# InfluxDB organization name
org: Optional[str] = None
# InfluxDB server URL
url: Optional[str] = None
# InfluxDB bucket name for data storage
bucket: Optional[str] = None
# InfluxDB measurement name for YOLO detections
measurement: Optional[str] = None

# Image Processing Configuration
# Target image width in pixels
INPUT_W = 512
# Target image height in pixels
INPUT_H = 512

# Flip bounding box coordinates horizontally
FLIP_X = True
# Flip bounding box coordinates vertically
FLIP_Y = False

# UART Protocol Constants - Frame delimiters
# Start marker for bounding box frame (0xABBA)
UART_START_BBOX = b"\xAB\xBA"
# End marker for bounding box frame (0xACCA)
UART_END_BBOX = b"\xAC\xCA"

# Start marker for JPEG image frame (0xBCCB)
UART_START_JPEG = b"\xBC\xCB"
# End marker for JPEG image frame (0xBDDB)
UART_END_JPEG = b"\xBD\xDB"

# Serial Communication Configuration
# Default ring buffer size in bytes (128 KB)
DEFAULT_BUFFER_SIZE = 128 * 1024
# Default UART baud rate
DEFAULT_BAUDRATE = 921_600

# Log pattern matching configuration
# Tuple of (start_pattern, end_pattern, log_function, prefix) for extracting
# and forwarding device logs from GAP9 and nRF52 to Python logging system.
# Each entry maps a serial log marker to its corresponding Python log level.
TEXT_PATTERNS: Tuple[Tuple[bytes, bytes, Callable[..., None], str], ...] = (
    (b"[GAP9-TRC]", b"\n", logging.debug, "[GAP9-TRC]"),
    (b"[GAP9-DBG]", b"\n", logging.debug, "[GAP9-DBG]"),
    (b"[GAP9-INF]", b"\n", logging.info, "[GAP9-INF]"),
    (b"[GAP9-WRN]", b"\n", logging.warning, "[GAP9-WRN]"),
    (b"[GAP9-ERR]", b"\n", logging.error, "[GAP9-ERR]"),
    (b"<dbg>", b"\r\n", logging.debug, "[nRF-DBG]"),
    (b"<inf>", b"\r\n", logging.info, "[nRF-INF]"),
    (b"<wrn>", b"\r\n", logging.warning, "[nRF-WRN]"),
    (b"<err>", b"\r\n", logging.error, "[nRF-ERR]"),
)
# ----------------------------------------

# --------------- Helpers  ---------------

def _ensure_influx_config() -> None:
    """Lazy-load InfluxDB credentials from config.ini when needed.
    
    This function reads the configuration file only when database connectivity
    is required (i.e., not in dry-run mode). It populates the global configuration
    variables (token, org, url, bucket, measurement) from the [influx] section
    of config.ini.
    
    Raises:
        RuntimeError: If config.ini does not exist in the script's directory.
    
    Note:
        This function modifies global variables and should only be called once
        before establishing the InfluxDB connection.
    """
    global token, org, url, bucket, measurement
    if not _ini_path.exists():
        raise RuntimeError("Configuration file ./config.ini not found!")
    _cfg = configparser.ConfigParser()
    _cfg.read(_ini_path)
    token = _cfg.get("influx", "token")
    org = _cfg.get("influx", "org")
    url = _cfg.get("influx", "url")
    bucket = _cfg.get("influx", "bucket")
    measurement = _cfg.get("influx", "measurement")

def _graceful_shutdown(signum: int, frame) -> None:
    """Handle shutdown signals gracefully.
    
    Logs the received signal and performs a clean exit. Registered as handler
    for SIGINT and SIGTERM in main().
    
    Args:
        signum: Signal number received (e.g., SIGINT, SIGTERM).
        frame: Current stack frame (unused).
    """
    logging.info("Received signal %s, shutting down", signum)
    sys.exit(0)


def _clamp(value: float, lower: float, upper: float) -> float:
    """Clamp a value to a specified range.
    
    Used to constrain normalized bounding box coordinates to [0, 1] and pixel
    coordinates to valid image dimensions.
    
    Args:
        value: The input value to clamp.
        lower: Lower bound of the range (inclusive).
        upper: Upper bound of the range (inclusive).
    
    Returns:
        Clamped value within [lower, upper].
    """
    return max(lower, min(upper, value))
# ----------------------------------------


class RingBuffer:
    """Simple deque-backed ring buffer for searching framed UART payloads.
    
    Implements a circular buffer using collections.deque that automatically
    discards oldest data when full. Provides pattern matching for extracting
    framed payloads delimited by start/end markers.
    """

    def __init__(self, size: int) -> None:
        """Initialize ring buffer with specified capacity.
        
        Args:
            size: Maximum buffer size in bytes (oldest data auto-discarded when full).
        """
        self._buffer: Deque[int] = deque(maxlen=size)

    def append(self, data: bytes) -> None:
        """Append data to the ring buffer.
        
        Args:
            data: Byte string to append to the buffer.
        """
        self._buffer.extend(data)

    def get_data(self) -> bytes:
        """Retrieve current buffer contents as bytes.
        
        Returns:
            Complete buffer contents as byte string.
        """
        return bytes(self._buffer)

    def clear(self) -> None:
        """Clear all data from the buffer."""
        self._buffer.clear()

    def extract_between(self, start_pattern: bytes, end_pattern: bytes) -> Tuple[Optional[bytes], bool]:
        """Extract payload between start and end markers, removing frame from buffer.
        
        Searches for complete frame (start + payload + end). If found, extracts
        payload, removes entire frame from buffer, and preserves remaining data.
        If incomplete or not found, buffer is unchanged.
        
        Args:
            start_pattern: Byte sequence marking frame start.
            end_pattern: Byte sequence marking frame end.
        
        Returns:
            Tuple of (payload_bytes, found_flag) where:
                - payload_bytes: Extracted data between markers (None if not found)
                - found_flag: True if complete frame found and extracted
        """
        data = self.get_data()
        start_idx = data.find(start_pattern)
        if start_idx == -1:
            return None, False
        end_idx = data.find(end_pattern, start_idx + len(start_pattern))
        if end_idx == -1:
            return None, False

        extracted = data[start_idx + len(start_pattern):end_idx]
        remaining = data[:start_idx] + data[end_idx + len(end_pattern):]
        self._buffer.clear()
        self._buffer.extend(remaining)
        return extracted, True


def parse_bboxes(serial_data: bytes) -> List[Dict[str, object]]:
    """Decode UART bounding box payload into list of pixel-space dictionaries.
    
    Each bounding box is encoded as 26 bytes:
        - 4 floats (x1, y1, x2, y2): Normalized coordinates [0.0, 1.0]
        - 2 floats (obj_conf, cls_conf): Confidence scores
        - 1 byte (cls_id): Class ID
        - 1 byte (alive): Tracking flag
    
    Processing steps:
        1. Validate payload size (must be multiple of 26)
        2. Unpack binary structure using struct.unpack("4f2fBc", ...)
        3. Check for NaN values and skip invalid boxes
        4. Clamp normalized coordinates to [0.0, 1.0]
        5. Apply FLIP_X/FLIP_Y transformations if enabled
        6. Convert to pixel coordinates using INPUT_W/INPUT_H
        7. Validate final coordinates (x1 < x2, y1 < y2)
    
    Args:
        serial_data: Raw byte payload containing one or more bounding boxes.
    
    Returns:
        List of dictionaries, each containing:
            - x1, y1, x2, y2: Pixel coordinates (int)
            - obj_conf: Object confidence score [0.0, 1.0] (float)
            - cls_conf: Class confidence score [0.0, 1.0] (float)
            - cls_id: Class identifier (int)
            - alive: Object tracking state (bool)
    
    Warning:
        Invalid boxes (NaN, out-of-range, malformed) are logged and skipped.
    """
    if not serial_data:
        return []

    if len(serial_data) % 26 != 0:
        logging.warning("Bounding box payload size %d is not a multiple of 26 bytes", len(serial_data))

    boxes: List[Dict[str, object]] = []
    num_boxes = len(serial_data) // 26
    for idx in range(num_boxes):
        start = idx * 26
        chunk = serial_data[start:start + 26]
        if len(chunk) < 26:
            logging.warning("Incomplete bounding box chunk at index %d", idx)
            continue
        try:
            x1, y1, x2, y2, obj_conf, cls_conf, cls_id, alive = struct.unpack("4f2fBc", chunk)
        except struct.error as exc:
            logging.warning("Failed to unpack bounding box %d: %s", idx, exc)
            continue

        if any(map(math.isnan, [x1, y1, x2, y2, obj_conf, cls_conf])):
            logging.warning("Skipping bounding box %d due to NaN values", idx)
            continue

        x1 = _clamp(x1, 0.0, 1.0)
        y1 = _clamp(y1, 0.0, 1.0)
        x2 = _clamp(x2, 0.0, 1.0)
        y2 = _clamp(y2, 0.0, 1.0)

        if FLIP_X:
            width = x2 - x1
            x1 = 1.0 - x2
            x2 = x1 + width
        if FLIP_Y:
            height = y2 - y1
            y1 = 1.0 - y2
            y2 = y1 + height

        if x1 >= x2 or y1 >= y2:
            logging.warning(
                "Invalid bbox #%d coordinates after normalization: x1=%f, x2=%f, y1=%f, y2=%f",
                idx, x1, x2, y1, y2
            )
            continue

        if not 0.0 <= obj_conf <= 1.0:
            logging.warning("Object confidence %.3f out of range for bounding box %d", obj_conf, idx)
            continue

        boxes.append(
            {
                "x1": int(_clamp(x1 * INPUT_W, 0, INPUT_W)),
                "y1": int(_clamp(y1 * INPUT_H, 0, INPUT_H)),
                "x2": int(_clamp(x2 * INPUT_W, 0, INPUT_W)),
                "y2": int(_clamp(y2 * INPUT_H, 0, INPUT_H)),
                "obj_conf": float(obj_conf),
                "cls_conf": float(cls_conf),
                "cls_id": int(cls_id),
                "alive": alive != b"\x00",
            }
        )

    return boxes


def drain_ring_buffer(ring_buffer: RingBuffer) -> Tuple[List[bytes], List[bytes]]:
    """Extract all available frames from the ring buffer.
    
    Repeatedly searches buffer for all frame types until no more complete frames
    are found. Processes in order:
        1. Text logs (GAP9/nRF patterns) - forwarded to Python logging
        2. Bounding box frames (UART_START_BBOX...UART_END_BBOX)
        3. JPEG image frames (UART_START_JPEG...UART_END_JPEG)
    
    Logs are immediately dispatched to logging system. Binary payloads (bboxes,
    images) are accumulated and returned for downstream processing.
    
    Args:
        ring_buffer: RingBuffer instance containing incoming serial data.
    
    Returns:
        Tuple of (bbox_payloads, image_payloads) where:
            - bbox_payloads: List of raw bounding box byte arrays
            - image_payloads: List of raw JPEG byte arrays
    
    Note:
        Empty bbox payloads are preserved; empty JPEG payloads trigger warnings.
    """
    bbox_payloads: List[bytes] = []
    image_payloads: List[bytes] = []

    while True:
        progress = False

        for start, end, log_fn, prefix in TEXT_PATTERNS:
            payload, found = ring_buffer.extract_between(start, end)
            if found:
                progress = True
                message = payload.decode("utf-8", errors="ignore").strip()
                if message:
                    log_fn("%s%s", prefix, message)

        payload, found = ring_buffer.extract_between(UART_START_BBOX, UART_END_BBOX)
        if found:
            progress = True
            bbox_payloads.append(payload or b"")

        payload, found = ring_buffer.extract_between(UART_START_JPEG, UART_END_JPEG)
        if found:
            progress = True
            if payload:
                image_payloads.append(payload)
            else:
                logging.warning("Received empty JPEG payload")

        if not progress:
            break

    return bbox_payloads, image_payloads


def save_image_payload(payload: bytes, image_dir: Path, hash_algorithm: str) -> Optional[Dict[str, object]]:
    """Persist JPEG payload to disk and return metadata.
    
    Processing pipeline:
        1. Validate payload size (minimum 4 bytes for header)
        2. Extract declared size from first 4 bytes (little-endian)
        3. Verify declared size matches actual JPEG byte count
        4. Compute hash digest over JPEG data
        5. Generate filename: YYYYMMDDTHHMMSSffffffZ_HASH[:8].jpg
        6. Create image_dir if it doesn't exist
        7. Write JPEG bytes to disk
    
    Args:
        payload: Raw byte array containing size header (4 bytes LE) + JPEG data.
        image_dir: Directory path where images will be saved.
        hash_algorithm: Hash algorithm name (e.g., "sha256", "sha1").
    
    Returns:
        Dictionary containing image metadata on success, None on failure:
            - path: Full Path object to saved file
            - timestamp: UTC datetime when image was saved
            - byte_size: Size of JPEG data in bytes
    
    Returns:
        None if:
            - Payload too small (< 4 bytes)
            - Size mismatch between header and actual data
            - Invalid hash algorithm
            - File write fails (logged as error)
    """
    if len(payload) < 4:
        logging.warning("JPEG payload too small (%d bytes)", len(payload))
        return None

    declared_size = int.from_bytes(payload[:4], byteorder="little")
    jpeg_bytes = payload[4:]
    if declared_size != len(jpeg_bytes):
        logging.warning(
            "JPEG size mismatch: header=%d bytes, payload=%d bytes",
            declared_size,
            len(jpeg_bytes),
        )
        return None

    try:
        digest = hashlib.new(hash_algorithm)
    except ValueError as exc:
        logging.error("Unsupported hash algorithm '%s': %s", hash_algorithm, exc)
        return None
    digest.update(jpeg_bytes)
    image_hash = digest.hexdigest()

    timestamp = datetime.now(timezone.utc)
    image_dir.mkdir(parents=True, exist_ok=True)
    filename = f"{timestamp.strftime('%Y%m%dT%H%M%S%f')}Z_{image_hash[:8]}.jpg"
    path = image_dir / filename

    try:
        path.write_bytes(jpeg_bytes)
    except OSError as exc:
        logging.error("Failed to write image %s: %s", path, exc)
        return None

    logging.info("Stored image %s (%d bytes)", path, len(jpeg_bytes))
    return {
        "path": path,
        "timestamp": timestamp,
        "byte_size": len(jpeg_bytes),
    }


def build_point(
    measurement: str,
    bbox_index: int,
    bbox: Dict[str, object],
    image_meta: Optional[Dict[str, object]],
) -> Dict[str, object]:
    """Create an InfluxDB point containing bbox coordinates and metadata.
    
    Correlates detection with corresponding image using metadata. If no image
    metadata is available, uses placeholder values.
    
    Args:
        measurement: InfluxDB measurement name.
        bbox_index: Zero-based index of this bbox within current detection batch.
        bbox: Bounding box dictionary (output from parse_bboxes).
        image_meta: Image metadata dictionary (from save_image_payload) or None.
    
    Returns:
        InfluxDB point dictionary with structure::
        
            {
              "measurement": str,
              "time": datetime (UTC),
              "fields": {
                "bbox_index": int,
                "x1", "y1", "x2", "y2": int (pixel coords),
                "width", "height": int (pixels),
                "obj_conf", "cls_conf": float,
                "cls_id": int,
                "alive": bool,
                "image_bytes": int,
                "image_filename": str (if image available)
              }
            }
    """
    image_hash = image_meta["hash"] if image_meta else "missing"
    fields = {
        "bbox_index": bbox_index,
        "x1": int(bbox["x1"]),
        "y1": int(bbox["y1"]),
        "x2": int(bbox["x2"]),
        "y2": int(bbox["y2"]),
        "width": int(bbox["x2"] - bbox["x1"]),
        "height": int(bbox["y2"] - bbox["y1"]),
        "obj_conf": float(bbox["obj_conf"]),
        "cls_conf": float(bbox["cls_conf"]),
        "cls_id": int(bbox["cls_id"]),
        "alive": bool(bbox["alive"]),
        "image_bytes": int(image_meta["byte_size"]) if image_meta else 0,
    }
    if image_meta:
        fields["image_filename"] = image_meta["path"].name

    return {
        "measurement": measurement,
        "time": datetime.now(timezone.utc),
        "fields": fields,
    }

def capture_groundtruth_image(fullPath: str) -> None:
    """Capture ground truth image from Raspberry Pi Camera v3.
    
    Placeholder function for synchronized ground truth capture using the
    Raspberry Pi camera module. When implemented, will capture a reference
    image at the same time as the GAP9 frame for validation.
    
    Args:
        fullPath: Base path for the captured image (will append "_gt" suffix).
    
    Todo:
        Implement picamera2 integration for actual image capture.
    
    Note:
        Currently unused/unimplemented.
    """



def run(args: argparse.Namespace) -> None:
    """Main processing loop - read UART frames, save images, push to InfluxDB.
    
    Core event loop that:
        1. Initializes InfluxDB connection (if not dry-run)
        2. Opens serial port and creates ring buffer
        3. Continuously reads serial data chunks
        4. Drains ring buffer to extract frames
        5. Saves JPEG images to disk with hash computation
        6. Decodes bounding boxes and writes to InfluxDB
        7. Handles errors gracefully with logging
    
    Args:
        args: Parsed command-line arguments from argparse.
    
    Note:
        In dry-run mode:
            - Skips config loading and database connection
            - Still saves images locally
            - Prints bbox summaries to console instead of DB writes
    
    Warning:
        Exits on serial port errors (open failure, read errors).
    """
    image_dir = Path(args.image_dir)
    write_client = None
    write_api = None

    if args.dry_run:
        logging.warning("Running in dry-run mode: InfluxDB writes are disabled")
    else:
        try:
            _ensure_influx_config()
        except RuntimeError as exc:
            logging.error("%s", exc)
            return
        missing = {"token": token, "org": org, "url": url, "bucket": bucket, "measurement": measurement}
        if any(value is None for value in missing.values()):
            logging.error("InfluxDB config incomplete: %s", ", ".join(k for k, v in missing.items() if v is None))
            return
        try:
            logging.info("Connecting to InfluxDB at %s", url)
            write_client = influxdb_client.InfluxDBClient(url=url, token=token, org=org)
            write_api = write_client.write_api(write_options=SYNCHRONOUS)
            logging.info("Connected to InfluxDB bucket '%s' (org: '%s')", bucket, org)
        except Exception as exc:
            logging.error("Failed to connect to InfluxDB: %s", exc)
            return

    logging.info("Opening serial port %s @ %d baud", args.serial_port, args.baudrate)

    try:
        try:
            ser = serial.Serial(
                port=args.serial_port,
                baudrate=args.baudrate,
                timeout=args.serial_timeout,
            )
        except (serial.SerialException, OSError) as exc:
            logging.error("Unable to open serial port: %s", exc)
            sys.exit(1)

        ser.reset_input_buffer()
        ring_buffer = RingBuffer(args.buffer_size)
        latest_image_meta: Optional[Dict[str, object]] = None

        with ser:
            while True:
                try:
                    chunk = ser.read(ser.in_waiting or 1)
                except (serial.SerialException, OSError) as exc:
                    logging.error("Serial port error: %s", exc)
                    sys.exit(1)

                if not chunk:
                    time.sleep(args.idle_sleep)
                    continue

                ring_buffer.append(chunk)
                bbox_payloads, image_payloads = drain_ring_buffer(ring_buffer)

                for payload in image_payloads:
                    meta = save_image_payload(payload, image_dir, args.hash_algorithm)
                    if meta:
                        latest_image_meta = meta
                        capture_groundtruth_image(meta["path"])

                for payload in bbox_payloads:
                    boxes = parse_bboxes(payload)
                    if not boxes:
                        logging.debug("No bounding boxes decoded from payload (%d bytes)", len(payload))
                        continue
                    logging.info(
                        "Decoded %d bounding boxes (image hash: %s)",
                        len(boxes),
                        latest_image_meta["hash"] if latest_image_meta else "missing",
                    )
                    for idx, bbox in enumerate(boxes):
                        if args.dry_run:
                            logging.info(
                                "DRY-RUN bbox #%d hash=%s cls=%d conf=%.2f coords=(%d,%d,%d,%d)",
                                idx,
                                latest_image_meta["hash"] if latest_image_meta else "missing",
                                bbox["cls_id"],
                                bbox["obj_conf"],
                                bbox["x1"],
                                bbox["y1"],
                                bbox["x2"],
                                bbox["y2"],
                            )
                        else:
                            point = build_point(measurement, idx, bbox, latest_image_meta)
                            try:
                                write_api.write(bucket=bucket, org=org, record=point)
                            except Exception as exc:
                                logging.error("Failed to write bbox to InfluxDB: %s", exc)
    finally:
        if write_client is not None:
            try:
                write_client.close()
            except Exception:
                logging.error("Failed to close InfluxDB client on exit")


def build_arg_parser() -> argparse.ArgumentParser:
    """Build command-line argument parser.
    
    Defines CLI interface with arguments:
        - serial_port (positional): Device path (e.g., /dev/ttyUSB0)
        - --baudrate: UART speed (default: 921600)
        - --serial-timeout: Read timeout in seconds (default: 0.01)
        - --idle-sleep: Sleep when no data available (default: 0.01)
        - --buffer-size: Ring buffer capacity in bytes (default: 128KB)
        - --image-dir: Output directory for JPEG frames
        - --hash-algorithm: Hash function for fingerprinting (default: sha256)
        - --dry-run: Disable database writes (testing mode)
        - --log-level: Python logging verbosity (default: INFO)
    
    Returns:
        Configured ArgumentParser instance.
    """
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("serial_port", help="Serial device to read from, e.g. /dev/ttyUSB0")
    parser.add_argument("--baudrate", type=int, default=DEFAULT_BAUDRATE, help="Serial port baud rate")
    parser.add_argument("--serial-timeout", type=float, default=0.01, help="Serial read timeout in seconds")
    parser.add_argument("--idle-sleep", type=float, default=0.01, help="Sleep duration when no data is available")
    parser.add_argument("--buffer-size", type=int, default=DEFAULT_BUFFER_SIZE, help="Ring buffer size in bytes")
    parser.add_argument(
        "--image-dir",
        default=Path(__file__).resolve().parent / "captured_frames",
        help="Directory where incoming JPEG frames are stored",
    )
    parser.add_argument(
        "--hash-algorithm",
        default="sha256",
        help="Hash algorithm used for image fingerprinting (e.g. sha1, sha256)",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Skip InfluxDB writes and print decoded bounding boxes instead",
    )
    parser.add_argument(
        "--log-level",
        default="INFO",
        choices=["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"],
        help="Logging verbosity",
    )
    return parser




# --------------- Main ---------------

def main() -> None:
    """Application entry point.
    
    Orchestrates:
        1. Command-line argument parsing
        2. Logging system initialization
        3. Signal handler registration (SIGINT, SIGTERM)
        4. Invocation of main processing loop (run)
        5. Graceful shutdown on keyboard interrupt
    
    Note:
        This function never returns during normal operation; terminates via
        signal handlers or exceptions.
    """
    parser = build_arg_parser()
    args = parser.parse_args()
    logging.basicConfig(
        level=getattr(logging, args.log_level),
        format="%(asctime)s %(levelname)s %(message)s",
        stream=sys.stderr,
    )

    signal.signal(signal.SIGINT, _graceful_shutdown)
    signal.signal(signal.SIGTERM, _graceful_shutdown)

    try:
        run(args)
    except KeyboardInterrupt: # Redundant, but safe
        logging.info("Error, interrupt not handled gracefully. Exiting.")


if __name__ == "__main__":
    main()