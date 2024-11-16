# ----------------------------------------------------------------------
#
# File: show_bboxes_util.py
#
# Last Edited: 12.04.2025
#
# Copyright (c) 2025 ETH Zurich and University of Bologna
#
# Authors:
# - Philip Wiese (wiesep@iis.ee.ethz.ch), ETH Zurich
#
# ----------------------------------------------------------------------
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the License); you may
# not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an AS IS BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import logging
import struct
from collections import deque

import coloredlogs
import cv2
import numpy as np

# Configuration
INPUT_W = 512
INPUT_H = 512
PIXEL_SIZE = 3

UART_START_BBOX = b'\xAB\xBA'
UART_END_BBOX = b'\xAC\xCA'

UART_START_JPEG = b'\xBC\xCB'
UART_END_JPEG = b'\xBD\xDB'

UART_START_IMAGE = b'\xCD\xDC'
UART_END_IMAGE = b'\xCE\xEC'

FLIP_X = True
FLIP_Y = False


class RingBuffer:

    def __init__(self, size):
        self.buffer = deque(maxlen = size)  # Automatically removes oldest data when full

    def append(self, data):
        self.buffer.extend(data)

    def get_data(self):
        return bytes(self.buffer)

    def clear(self, size = 0):
        # Remove size bytes from the buffer
        if size == 0:
            self.buffer.clear()
        else:
            for _ in range(size):
                self.buffer.popleft()

    def find(self, pattern):
        data = self.get_data()
        return data.find(pattern)

    def extract_between(self, start_pattern, end_pattern, clear = False):
        data = self.get_data()
        start_idx = data.find(start_pattern)

        if start_idx == -1:
            return None, False
        # logging.debug(f"Found start pattern {start_pattern.hex()} at index {start_idx}")

        end_idx = data.find(end_pattern, start_idx)
        if end_idx == -1:
            return None, False

        # logging.debug(f"Found end pattern {end_pattern.hex()} at index {end_idx}")
        extracted = data[start_idx + len(start_pattern):end_idx]

        # Set new buffer to the remaining data
        data_remaining = data[0:start_idx] + data[end_idx + len(end_pattern):]
        self.buffer.clear()
        self.buffer.extend(data_remaining)

        return extracted, True


def dump_hex(buffer, length = 32):
    data = buffer.get_data()
    for i in range(0, len(data), length):
        hex_values = ' '.join(f'{b:02X}' for b in data[i:i + length])
        ascii_values = ''.join(chr(b) if 32 <= b < 127 else '.' for b in data[i:i + length])
        logging.debug(f'{i:08X}  {hex_values:<48}  {ascii_values}')


# Function to set logging level based on verbosity
def set_log_level(verbosity):
    levels = {0: logging.WARNING, 1: logging.INFO, 2: logging.DEBUG}
    log_level = levels.get(verbosity, logging.DEBUG)
    logging.basicConfig(level = log_level,
                        format = '%(asctime)s - %(levelname)s - %(message)s',
                        handlers = [logging.StreamHandler(),
                                    logging.FileHandler('serial_log.log', mode = 'a')])

    coloredlogs.install(level = log_level, fmt = '%(asctime)s - %(levelname)s - %(message)s')

    logging.info(f"Log level set to: {logging.getLevelName(log_level)}")


# Function to decode the bounding box structure from the byte stream
def parse_bboxes(serial_data):
    num_boxes = (len(serial_data)) // 26  # Each box is 19 bytes (5 * 4 bytes + 1 byte + 1 byte)
    boxes = []

    for i in range(num_boxes):
        start_idx = i * 26
        box_data = serial_data[start_idx:start_idx + 26]
        x1, y1, x2, y2, obj_conf, cls_conf, cls_id, alive = struct.unpack('4f2fBc', box_data)
        # Ccheck if any of the values are NaN
        if any(np.isnan([x1, y1, x2, y2, obj_conf, cls_conf])):
            logging.warning(f"Found NaN value in bounding box data at index {i}. Skipping box.")
            continue

        # Crop the values to be between 0 and 1
        x1 = max(0, min(1, x1))
        y1 = max(0, min(1, y1))
        x2 = max(0, min(1, x2))
        y2 = max(0, min(1, y2))

        # Flip the coordinates for the bounding box
        if FLIP_X:
            width = x2 - x1
            x1 = 1 - x2
            x2 = x1 + width
        if FLIP_Y:
            height = y2 - y1
            y1 = 1 - y2
            y2 = y1 + height

        box = {
            'x1': int(x1 * INPUT_W),
            'y1': int(y1 * INPUT_H),
            'x2': int(x2 * INPUT_W),
            'y2': int(y2 * INPUT_H),
            'obj_conf': obj_conf,
            'cls_conf': cls_conf,
            'cls_id': cls_id,
            'alive': alive
        }

        # Check if x1 < x2 and y1 < y2
        if x1 >= x2 or y1 >= y2:
            logging.warning(f"Invalid bounding box coordinates at index {i}. Skipping box.")
            logging.warning(
                f" - Box: {box['x1']:3d}, {box['y1']:3d}, {box['x2']:3d}, {box['y2']:3d} ({box['obj_conf']*100:.2f}%)")
            continue

        # Check if object confidence is between 0 and 1
        if not 0 <= obj_conf <= 1:
            logging.warning(f"Object confidence out of range at index {i}. Skipping box.")
            continue

        boxes.append(box)

    for box in boxes:
        logging.info(
            f" - Box: {box['x1']:3d}, {box['y1']:3d}, {box['x2']:3d}, {box['y2']:3d} ({box['obj_conf']*100:.2f}%)")

    return boxes


# Function to draw bounding boxes on the image
def draw_bboxes(image, bboxes):
    # Duplicate the image to avoid modifying the original
    image = image.copy()

    for box in bboxes:
        color = (0, 255, 0) if box['alive'] else (0, 0, 255)
        cv2.rectangle(image, (box['x1'], box['y1']), (box['x2'], box['y2']), color, 2)

        # Draw small bar to show confidence
        r = int(255 * (1 - box['obj_conf']))
        g = int(255 * box['obj_conf'])
        confidence_color = (0, g, r)
        cv2.rectangle(image, (box['x1'], box['y1'] - 15), (box['x1'] + int(
            (box['x2'] - box['x1']) * box['obj_conf']), box['y1'] - 5), confidence_color, -1)

        # Write class percentage
        text = f"{box['obj_conf']*100:.1f}%"
        cv2.putText(image, text, (box['x1'], box['y1'] - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)

    return image


bboxes_static = []
image_static = np.zeros((INPUT_H, INPUT_W, PIXEL_SIZE), dtype = np.uint8)


# Function to process serial data
def process_serial_data(ring_buffer):
    global bboxes_static
    global image_static

    # Print content of ring buffer
    # logging.debug(f"Buffer: {ring_buffer.get_data().hex()}")

    found_data = False
    #### GAP9 Trace, Debug, Info, Warning, Error ####
    text_gap9_trace_data, _ = ring_buffer.extract_between(b'[GAP9-TRC]', b'\n')
    if text_gap9_trace_data:
        found_data = True
        logging.debug(f"[GAP9-TRC]{text_gap9_trace_data.decode('utf-8', errors='ignore')}")

    text_gap9_debug_data, _ = ring_buffer.extract_between(b'[GAP9-DBG]', b'\n')
    if text_gap9_debug_data:
        found_data = True
        logging.debug(f"[GAP9-DBG]{text_gap9_debug_data.decode('utf-8', errors='ignore')}")

    text_gap9_info_data, _ = ring_buffer.extract_between(b'[GAP9-INF]', b'\n')
    if text_gap9_info_data:

        if b'Staring main program' in text_gap9_info_data:
            logging.warning("[GAP9-WRN] GAP9 was reset.")
        found_data = True
        logging.info(f"[GAP9-INF]{text_gap9_info_data.decode('utf-8', errors='ignore')}")

    text_gap9_warn_data, _ = ring_buffer.extract_between(b'[GAP9-WRN]', b'\n')
    if text_gap9_warn_data:
        found_data = True
        logging.warning(f"[GAP9-WRN]{text_gap9_warn_data.decode('utf-8', errors='ignore')}")

    text_gap9_error_data, _ = ring_buffer.extract_between(b'[GAP9-ERR]', b'\n')
    if text_gap9_error_data:
        found_data = True
        logging.error(f"[GAP9-ERR]{text_gap9_error_data.decode('utf-8', errors='ignore')}")

    #### nRF52 Debug, Info, Warning, Error ####
    text_nrf_debug_data, _ = ring_buffer.extract_between(b'<dbg>', b'\r\n')
    if text_nrf_debug_data:
        found_data = True
        logging.debug(f"[nRF-DBG]{text_nrf_debug_data.decode('utf-8', errors='ignore')}")

    text_nrf_info_data, _ = ring_buffer.extract_between(b'<inf>', b'\r\n')
    if text_nrf_info_data:
        found_data = True
        logging.info(f"[nRF-INF]{text_nrf_info_data.decode('utf-8', errors='ignore')}")

    text_nrf_warn_data, _ = ring_buffer.extract_between(b'<wrn>', b'\r\n')
    if text_nrf_warn_data:
        found_data = True
        logging.warning(f"[nRF-WRN]{text_nrf_warn_data.decode('utf-8', errors='ignore')}")

    text_nrf_error_data, _ = ring_buffer.extract_between(b'<err>', b'\r\n')
    if text_nrf_error_data:
        found_data = True
        logging.error(f"[nRF-ERR]{text_nrf_error_data.decode('utf-8', errors='ignore')}")

    bboxes_data, empty_box = ring_buffer.extract_between(UART_START_BBOX, UART_END_BBOX)
    if bboxes_data or empty_box:
        found_data = True
        bboxes_static = parse_bboxes(bboxes_data)
        logging.info(f"Decoded {len(bboxes_static)} bounding boxes.")

    image_data, _ = ring_buffer.extract_between(UART_START_JPEG, UART_END_JPEG)
    if image_data:
        found_data = True
        image_array = np.frombuffer(image_data, np.uint8)
        image_size = int.from_bytes(image_array[:4], byteorder = 'little')

        if image_size != len(image_array[4:]):
            logging.warning(f"Image size mismatch: got {len(image_array[4:])} but expected {image_size} bytes!")
            return

        image = cv2.imdecode(image_array[4:], cv2.IMREAD_COLOR)
        if image is not None:
            image_static = cv2.resize(image, (INPUT_W, INPUT_H), interpolation = cv2.INTER_AREA)
            if FLIP_X:
                image_static = cv2.flip(image_static, 1)
            if FLIP_Y:
                image_static = cv2.flip(image_static, 0)
            logging.debug(f"Decoded JPEG image ({image.shape[1]}x{image.shape[0]})")

    image = draw_bboxes(image_static, bboxes_static)

    cv2.imshow("Bounding Boxes", image)

    return found_data
