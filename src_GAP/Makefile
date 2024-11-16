# Copyright (c) 2025 ETH Zurich and University of Bologna
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
# Philip Wiese <wiesep@iis.ee.ethz.ch>
#

GAPY := gapy
TARGET := gap9.evk
TARGET_DIR := $(GAP_SDK_HOME)/utils/gapy_v2/targets
PLATFORM := board
WORK_DIR := $(PWD)/build
FLASH_DEVICE := mram
BOOT_MODE := flash
OPENOCD_CABLE := interface/ftdi/olimex-arm-usb-ocd-h.cfg
OPENOCD_SCRIPT := $(GAP_SDK_HOME)/utils/openocd_tools/tcl/gap9revb.tcl
OPENOCD_TOOLS := $(GAP_SDK_HOME)/utils/openocd_tools
FLASH_LAYOUT := $(PWD)/custom_layout_multi.json
MAIN_BINARY := $(WORK_DIR)/main
MODEL_FILE := $(WORK_DIR)/BUILD_MODEL/YOLOv5_L3_Flash_Const.dat
FSBL := $(GAP_SDK_HOME)/install/target/bin/fsbl
SSBL := $(GAP_SDK_HOME)/install/target/bin/ssbl
FLASH_SIZE := 67108864 # 64MB (64×1024×1024) for external flash

COMMON_ARGS := \
	--target=$(TARGET) \
	--target-dir=$(TARGET_DIR) \
	--platform=$(PLATFORM) \
	--work-dir=$(WORK_DIR) \
	--target-property=boot.flash_device=$(FLASH_DEVICE) \
	--target-property=boot.mode=$(BOOT_MODE) \
	--openocd-cable=$(OPENOCD_CABLE) \
	--openocd-script=$(OPENOCD_SCRIPT) \
	--openocd-tools=$(OPENOCD_TOOLS) \
	--multi-flash-content=$(FLASH_LAYOUT) \
	--flash-property=$(MAIN_BINARY)@$(FLASH_DEVICE):app:binary \
	--binary=$(MAIN_BINARY) \
	--flash-property=$(MODEL_FILE)@$(FLASH_DEVICE):readfs_mram:files \
	--flash-property=$(FSBL)@$(FLASH_DEVICE):fsbl:binary \
	--flash-property=$(SSBL)@$(FLASH_DEVICE):ssbl:binary \
	--flash-size=$(FLASH_SIZE) \
	--py-stack

run:
	$(GAPY) $(COMMON_ARGS) run

flash:
	$(GAPY) $(COMMON_ARGS) flash


build:
	cmake --build build -j 3

clean:
	rm -rf build
	gap init

all: flash run

.PHONY: run flash all clean build
