# Copyright (c) 2025 ETH Zurich and University of Bologna
# SPDX-License-Identifier: Apache-2.0

# Load FreeRTOS Plugin
python import freertos_gdb

# Load the program
file ./build/main

# Connect to OpenOCD
target remote :3333

# Enable pretty printing
set print pretty on

# Load the program into the target's memory
load

# Optional: Break at main
break main
