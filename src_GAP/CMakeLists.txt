# Copyright (c) 2024 ETH Zurich and University of Bologna
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.19.5)

# ##############################################################################
# Panel Control
# ##############################################################################
set(TARGET_NAME "main")

# set(CMAKE_MESSAGE_LOG_LEVEL "DEBUG")

# ##############################################################################
# CMake pre initialization
# ##############################################################################
set(GAP_CUSTOM_BSP $ENV{SENSEI_SDK_ROOT}/GAP9)

# Cmake pre-inits
set(CONFIG_GAP_SDK_HOME $ENV{GAP_SDK_HOME})
include($ENV{GAP_SDK_HOME}/utils/cmake/setup.cmake)

# ##############################################################################
# CMake Configuration
# ##############################################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Target Configuration
set(PMSIS_OS freertos)

# KConfig options
set(io host)

# Frequency and Voltage COnfiguration
set(FREQ_CL 370)
set(FREQ_FC 370)
set(VOLTAGE 800)

# Folder Configuration
set(GAP9_SDK_DIR $ENV{GAP_SDK_HOME})
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Memory Configuration
set(PRI1_FLASH_TYPE     "mram")

set(FLASH_TYPE DEFAULT)
set(RAM_TYPE DEFAULT)
set(MODEL_L3_FLASH AT_MEM_L3_MRAMFLASH)
set(MODEL_L3_RAM AT_MEM_L3_DEFAULTRAM)
set(EXEC_FROM_FLASH true)

set(MODEL_FLASH_LAYOUT "custom_layout_multi.json")

# Autotiler Configuration
set(AT_DSP_FLOAT_TYPE 1)

# Yolo Configuration
set(YOLO_INPUT_CHANNEL 3)
set(YOLO_INPUT_SIZE 64)

################################################################################
# YOLOv5 Configuration
################################################################################

# Switch config based on YOLO_INPUT_SIZE variable (64, 128, 192, 256, 320, 384, 448, 512)
if (YOLO_INPUT_SIZE EQUAL 64)
    math(EXPR ROWS "1512 / 6")
    set(YOLO_INPUT_WIDTH 64)
    set(YOLO_INPUT_HEIGHT 64)
    set(INPUT_IN_L3 0)
    set(DOWNSAMPLE_FACTOR 8)
elseif (YOLO_INPUT_SIZE EQUAL 128)
    math(EXPR ROWS "6048 / 6")
    set(YOLO_INPUT_WIDTH 128)
    set(YOLO_INPUT_HEIGHT 128)
    set(INPUT_IN_L3 0)
    set(DOWNSAMPLE_FACTOR 4)
elseif (YOLO_INPUT_SIZE EQUAL 192)
    math(EXPR ROWS "13608 / 6")
    set(YOLO_INPUT_WIDTH 192)
    set(YOLO_INPUT_HEIGHT 192)
    set(INPUT_IN_L3 0)
    set(DOWNSAMPLE_FACTOR 2)
elseif (YOLO_INPUT_SIZE EQUAL 256)
    math(EXPR ROWS "24192 / 6")
    set(YOLO_INPUT_WIDTH 256)
    set(YOLO_INPUT_HEIGHT 256)
    set(INPUT_IN_L3 0)
    set(DOWNSAMPLE_FACTOR 2)
elseif (YOLO_INPUT_SIZE EQUAL 320)
    math(EXPR ROWS "37800 / 6")
    set(YOLO_INPUT_WIDTH 320)
    set(YOLO_INPUT_HEIGHT 320)
    set(INPUT_IN_L3 0)
    set(DOWNSAMPLE_FACTOR 1)
elseif (YOLO_INPUT_SIZE EQUAL 384)
    math(EXPR ROWS "54432 / 6")
    set(YOLO_INPUT_WIDTH 384)
    set(YOLO_INPUT_HEIGHT 384)
    set(INPUT_IN_L3 0)
    set(DOWNSAMPLE_FACTOR 1)
elseif (YOLO_INPUT_SIZE EQUAL 448)
    math(EXPR ROWS "74088 / 6")
    set(YOLO_INPUT_WIDTH 448)
    set(YOLO_INPUT_HEIGHT 448)
    set(INPUT_IN_L3 1)
    set(DOWNSAMPLE_FACTOR 1)
elseif (YOLO_INPUT_SIZE EQUAL 512)
    math(EXPR ROWS "96768 / 6")
    set(YOLO_INPUT_WIDTH 512)
    set(YOLO_INPUT_HEIGHT 512)
    set(INPUT_IN_L3 1)
    set(DOWNSAMPLE_FACTOR 1)
else()
    message(FATAL_ERROR "Invalid YOLO_INPUT_SIZE: ${YOLO_INPUT_SIZE}. Must be one of 64, 128, 192, 256, 320, 384, 448, or 512.")
endif()

set(YOLO_MODEL_DIR generated_${YOLO_INPUT_WIDTH}x${YOLO_INPUT_HEIGHT})
# ##############################################################################
# Autotiler Models and Sources
# ##############################################################################

# YOLO Network
set(YOLO_MODEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/networks/YOLOv5/${YOLO_MODEL_DIR}/model.c)
set(YOLO_TENSORS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/networks/YOLOv5/${YOLO_MODEL_DIR}/weights_tensors)

autotiler_add_model(
    TARGET_NAME YOLOv5
    MODEL_PATH ${YOLO_MODEL_PATH}
    MODEL_TENSORS_DIR ${YOLO_TENSORS_DIR}
    PRI1_USED TRUE
    PRI1_FLASH ${PRI1_FLASH_TYPE}
    PRI1_FILENAME "L3_Flash_Const.dat"
    L1_MEMORY ${CONFIG_MODEL_L1_MEMORY}
    L2_MEMORY ${CONFIG_MODEL_L2_MEMORY}
    L3_MEMORY ${CONFIG_MODEL_L3_MEMORY}
    L2STATIC_MEMORY ${CONFIG_MODEL_L2STATIC_MEMORY}
    L3STATIC_MEMORY ${CONFIG_MODEL_L3STATIC_MEMORY}
    MODEL_FLASH_LAYOUT ${MODEL_FLASH_LAYOUT}
    APP_NAME ${TARGET_NAME}
)

# Image Proceccing
set(MODEL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/ISPModel.c)

autotiler_add_model(
    TARGET_NAME ISP
    MODEL_PATH ${MODEL_SRC}
    PRI1_USED TRUE
    PRI1_FLASH ${PRI1_FLASH_TYPE}
    L1_MEMORY ${CONFIG_MODEL_L1_MEMORY}
    L2_MEMORY ${CONFIG_MODEL_L2_MEMORY}
    L3_MEMORY ${CONFIG_MODEL_L3_MEMORY}
    L2STATIC_MEMORY ${CONFIG_MODEL_L2STATIC_MEMORY}
    L3STATIC_MEMORY ${CONFIG_MODEL_L3STATIC_MEMORY}
    MODEL_EXTRA_COMPILE_FLAGS "-DIMG_W=${YOLO_INPUT_WIDTH};-DIMG_H=${YOLO_INPUT_HEIGHT}"
    MODEL_FLASH_LAYOUT ${MODEL_FLASH_LAYOUT}
    APP_NAME ${TARGET_NAME}
)

# AutoTiler Include and Sources
list(APPEND AT_SRCS
    ${CNN_LIB}
    ${KERNEL_C_PATHS}
    ${TILER_ISP_KERNEL_PATH}/ISP_BasicKernels.c
)

list(APPEND AT_INCS
    ${TILER_INC}
    ${TILER_EMU_INC}
    ${CNN_LIB_INCLUDE_NOPREPEND}
    ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_MODEL_BUILDDIR}
    ${TILER_ISP_KERNEL_PATH}
)

# ##############################################################################
# CMake Sources
# ##############################################################################

# list(APPEND TARGET_SRCS
# )

list(APPEND TARGET_INCS
    ${GAP9_SDK_DIR}/libs/gap_lib/include
    ${GAP9_SDK_DIR}/rtos/pmsis/bsp/include/bsp
    ${GAP9_SDK_DIR}/rtos/pmsis/bsp/include/bsp/flash
    ${GAP9_SDK_DIR}/rtos/pmsis/bsp/include/bsp/ram
    ${GAP9_SDK_DIR}/utils/power_meas_utils
)

# ##############################################################################
# CMake Compiler Options
# ##############################################################################

# Compiler Flags
list(APPEND TARGET_CFLAGS
    -O2
    -mno-memcpy
    -mhwloopalign
    -fno-tree-loop-distribute-patterns
    -Wno-incompatible-pointer-types
    -Wno-maybe-uninitialized
    -Wno-unused-but-set-variable
    -Wno-unused-variable
)

# Preprocessor Flags
list(APPEND TARGET_PREPROCESSOR
    -DSTACK_SIZE=${CONFIG_CL_MASTER_CORE_STACK_SIZE}
    -DSLAVE_STACK_SIZE=${CONFIG_CL_SLAVE_CORE_STACK_SIZE}
    -DFREQ_FC=${FREQ_FC}
    -DFREQ_CL=${FREQ_CL}
    -DVOLTAGE=${VOLTAGE}
)

list(APPEND TARGET_PREPROCESSOR
    -DROWS=${ROWS}
    -DYOLO_INPUT_CHANNEL=${YOLO_INPUT_CHANNEL}
    -DYOLO_INPUT_WIDTH=${YOLO_INPUT_WIDTH}
    -DYOLO_INPUT_HEIGHT=${YOLO_INPUT_HEIGHT}
    -DYOLO_MODEL_DIR="${YOLO_MODEL_DIR}"
    -DINPUT_IN_L3=${INPUT_IN_L3}
    -DDOWNSAMPLE_FACTOR=${DOWNSAMPLE_FACTOR}
)

# ##############################################################################
# CMake Project and Target
# ##############################################################################
project(${TARGET_NAME} C ASM)

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE ${TARGET_SRCS} ${AT_SRCS})
target_include_directories(${TARGET_NAME} PRIVATE ${TARGET_INCS} ${AT_INCS})

target_compile_options(${TARGET_NAME} PRIVATE ${TARGET_CFLAGS}
                                                ${TARGET_PREPROCESSOR})


target_link_libraries(${TARGET_NAME} PRIVATE m)
target_link_libraries(${TARGET_NAME} PRIVATE ${TILER_LIB})

# ##############################################################################
# CMake Included
# ##############################################################################
add_subdirectory(src)

# ##############################################################################
# CMake post initialization
# ##############################################################################
setupos(${TARGET_NAME})

# ##############################################################################
# CMake Debugging
# ##############################################################################
# include(CMakePrintHelpers)

# cmake_print_properties(
#     TARGETS ${TARGET_NAME}
#     PROPERTIES INCLUDE_DIRECTORIES
# )
