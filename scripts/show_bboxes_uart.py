# ----------------------------------------------------------------------
#
# File: uart_show_bboxes copy.py
#
# Last edited: 30.01.2025
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

import argparse
import logging

import cv2
import numpy as np
import serial
import serial.tools.list_ports
from serial.tools.miniterm import ask_for_port
from show_bboxes_util import INPUT_H, INPUT_W, PIXEL_SIZE, RingBuffer, dump_hex, process_serial_data, set_log_level

# Configuration
GAP_UART_BAUDRATE = 921600
BUFFER_SIZE = 128 * 1024  # Configurable ring buffer size


# Main function to handle serial communication and processing
def main(args):
    # List serial ports and allow user to select one
    port = ask_for_port()

    if not port:
        logging.error("No valid serial port selected.")
        return

    # Open the selected serial port
    try:
        logging.info(f"Opening serial port: {port}")
        with serial.Serial(port, args.baudrate, timeout = 0.01) as ser:
            ring_buffer = RingBuffer(BUFFER_SIZE)
            logging.info(f"Connected to {port} at {args.baudrate} baud rate.")

            cv2.imshow("Bounding Boxes", np.zeros((INPUT_H, INPUT_W, PIXEL_SIZE), dtype = np.uint8))

            while True:
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break

                # Read dataq from the serial port

                serial_data = ser.read(ser.in_waiting or 1)

                if serial_data:
                    # Process the received data
                    ring_buffer.append(serial_data)

                    if args.verbose > 2:
                        dump_hex(ring_buffer)

                while process_serial_data(ring_buffer):
                    pass

    except Exception as e:
        logging.error(f"Error: {str(e)}")
        # Print exception traceback
        import traceback
        traceback.print_exc()
    finally:
        cv2.destroyAllWindows()


if __name__ == "__main__":
    # Parse arguments for verbosity
    parser = argparse.ArgumentParser(description = "Serial Communication for Bounding Boxes")
    parser.add_argument("-v",
                        "--verbose",
                        action = "count",
                        default = 0,
                        help = "Increase verbosity (use -v, -vv, etc.)")

    # Optional baudrate argument
    parser.add_argument("-b",
                        "--baudrate",
                        type = int,
                        default = GAP_UART_BAUDRATE,
                        help = "Set UART baudrate (default: 921600)")

    args = parser.parse_args()

    # Set logging level based on verbosity
    set_log_level(args.verbose)

    main(args)
