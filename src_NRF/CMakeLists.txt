# Copyright (c) 2024 ETH Zurich and University of Bologna
# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)

# Enable shields UT_SensorShield_v1 and SENSEI_DebugBoard_v1
set(SHIELD UT_SensorShield_v1 SENSEI_DebugBoard_v1)

# Setup SENSEI SDK
set(SENSEI_SDK_ROOT $ENV{SENSEI_SDK_ROOT})
if(NOT SENSEI_SDK_ROOT)
    message(FATAL_ERROR "SENSEI_SDK_ROOT is not defined")
endif()

# Append UBXLIB as a Zephyr module
get_filename_component(UBXLIB_BASE "${CMAKE_CURRENT_LIST_DIR}/third_party/ubxlib" ABSOLUTE)

list(APPEND EXTRA_ZEPHYR_MODULES
    ${SENSEI_SDK_ROOT}/NRF
    ${UBXLIB_BASE}
)

# Do not use the default configuration
set(UBXLIB_NO_DEF_CONF)

# Configure the project
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(sensei_yolov5_demo)

target_sources(app PRIVATE
    main.c
    i2c_helpers.c
    bsp/pwr_bsp.c
    bluetooth.c
)

target_include_directories(app PRIVATE
    .
)
