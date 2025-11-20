#!/usr/bin/env python3

"""Stream YOLO detections from GAP9 to InfluxDB v2 and archive frames locally."""

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
_ini_path = Path(__file__).resolve().parent / "config.ini"
token: Optional[str] = None
org: Optional[str] = None
url: Optional[str] = None
bucket: Optional[str] = None
measurement: Optional[str] = None

INPUT_W = 512
INPUT_H = 512

UART_START_BBOX = b"\xAB\xBA"
UART_END_BBOX = b"\xAC\xCA"

UART_START_JPEG = b"\xBC\xCB"
UART_END_JPEG = b"\xBD\xDB"

FLIP_X = True
FLIP_Y = False

DEFAULT_BUFFER_SIZE = 128 * 1024
DEFAULT_BAUDRATE = 921_600

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
    """Lazy-load InfluxDB credentials from config.ini when needed."""
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
    """Handle shutdown signals gracefully."""
    logging.info("Received signal %s, shutting down", signum)
    sys.exit(0)


def _clamp(value: float, lower: float, upper: float) -> float:
    return max(lower, min(upper, value))
# ----------------------------------------


class RingBuffer:
    """Simple deque-backed ring buffer for searching framed UART payloads."""

    def __init__(self, size: int) -> None:
        self._buffer: Deque[int] = deque(maxlen=size)

    def append(self, data: bytes) -> None:
        self._buffer.extend(data)

    def get_data(self) -> bytes:
        return bytes(self._buffer)

    def clear(self) -> None:
        self._buffer.clear()

    def extract_between(self, start_pattern: bytes, end_pattern: bytes) -> Tuple[Optional[bytes], bool]:
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


# Each box is 19 bytes (5 * 4 bytes + 1 byte + 1 byte)
def parse_bboxes(serial_data: bytes) -> List[Dict[str, object]]:
    """Decode UART bbox payload into a list of pixel-space dictionaries."""
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
    """Extract textual logs, bbox payloads, and JPEG payloads from the buffer."""
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
    """Persist JPEG payload to disk and return metadata."""
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
    """Create an InfluxDB point containing bbox coordinates and metadata."""
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
    """Capture an image from RPi v3 camera, saves it as fullPath_gt"""



def run(args: argparse.Namespace) -> None:
    """Continuously read UART frames, save images, and push bbox metadata to InfluxDB."""
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
    """Build command-line argument parser."""
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