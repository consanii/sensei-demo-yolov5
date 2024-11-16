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

import asyncio

from bleak import BleakClient, BleakScanner

UART_TX_UUID = "6e400002-b5a3-f393-e0a9-e50e24dcca9e"  #Nordic NUS characteristic for TX
UART_RX_UUID = "6e400003-b5a3-f393-e0a9-e50e24dcca9e"  #Nordic NUS characteristic for RX

import argparse
import logging

import cv2
import numpy as np
from show_bboxes_util import INPUT_H, INPUT_W, PIXEL_SIZE, RingBuffer, dump_hex, process_serial_data, set_log_level

# Configuration
BUFFER_SIZE = 5 * 2048  # Configurable ring buffer size


def notification_handler(sender, data):
    """Simple notification handler which prints the data received."""
    global ring_buffer
    ring_buffer.append(data)

    dump_hex(ring_buffer)

    while process_serial_data(ring_buffer):
        pass


# Main function to handle serial communication and processing
async def run_ble(args):
    address = await scan_and_select()

    # Open the selected serial port
    try:

        logging.info(f"Opening BLE device: {address}")
        async with BleakClient(address) as client:
            global ring_buffer
            ring_buffer = RingBuffer(BUFFER_SIZE)

            x = client.connect()
            logging.info(f"Connected to BLE device: {address}")

            await client.start_notify(UART_RX_UUID, notification_handler)

            while True:

                await asyncio.sleep(0.01)

    except Exception as e:
        logging.error(f"Error: {str(e)}")
        # Print exception traceback
        import traceback
        traceback.print_exc()
    finally:
        cv2.destroyAllWindows()


def display_devices(devices, default_index = 0):
    print("Available BLE devices:")
    for i, device in enumerate(devices):
        print(f"[{i}] {device.address} - {device.name if device.name else 'Unknown'}")

        # If there is a nevice with SENSEI in the name, select it
        if device.name and "SENSEI" in device.name:
            default_index = i

    return default_index


async def scan_and_select():
    print("Scanning for BLE devices...")
    devices = await BleakScanner.discover()

    if not devices:
        print("No devices found.")
        return None

    default_index = display_devices(devices)

    while True:
        try:
            index = input(f"Select a device by number: [{default_index}]")
            # Check if just pressing enter
            if index == "":
                return devices[default_index].address

            index = int(index)
            if 0 <= index < len(devices):
                return devices[index].address
            else:
                print("Invalid selection. Try again.")
        except ValueError:
            print("Please enter a valid number.")


async def run_image(args):

    image = np.zeros((INPUT_H, INPUT_W, PIXEL_SIZE), dtype = np.uint8)
    cv2.imshow("Bounding Boxes", image)

    while True:
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        await asyncio.sleep(0.01)


if __name__ == "__main__":
    # Parse arguments for verbosity
    parser = argparse.ArgumentParser(description = "Serial Communication for Bounding Boxes")
    parser.add_argument("-v",
                        "--verbose",
                        action = "count",
                        default = 0,
                        help = "Increase verbosity (use -v, -vv, etc.)")

    args = parser.parse_args()

    # Set logging level based on verbosity
    set_log_level(args.verbose)

    loop = asyncio.get_event_loop()
    single = asyncio.gather(run_ble(args), run_image(args))
    loop.run_until_complete(single)
