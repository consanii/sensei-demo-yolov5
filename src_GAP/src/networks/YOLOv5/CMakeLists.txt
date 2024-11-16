# Copyright (c) 2025 ETH Zurich
# SPDX-License-Identifier: Apache-2.0

# ##############################################################################
# CMake Configuration
# ##############################################################################

# ##############################################################################
# CMake Sources
# ##############################################################################
list(APPEND YOLO_SRCS
    yolo_utils.c
    ${YOLO_MODEL_DIR}/Expression_Kernels.c
)

# Check if directory exists
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${YOLO_MODEL_DIR})
    message(STATUS "Directory ${YOLO_MODEL_DIR} exists.")
else()
    message(FATAL_ERROR "Directory ${YOLO_MODEL_DIR} does not exist.")
endif()

list(APPEND YOLO_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${YOLO_MODEL_DIR}
)

target_sources(${TARGET_NAME} PRIVATE ${YOLO_SRCS})
target_include_directories(${TARGET_NAME} PRIVATE ${YOLO_INCS})


