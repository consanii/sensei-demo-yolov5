# Copyright (c) 2024 ETH Zurich and University of Bologna
# SPDX-License-Identifier: Apache-2.0

# ##############################################################################
# CMake Sources
# ##############################################################################

list(APPEND MAIN_SRCS
    main.c
    utils.c
    uart_comm.c
)

list(APPEND MAIN_INCS
    ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_MODEL_BUILDDIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${TARGET_NAME} PRIVATE ${MAIN_SRCS})
target_include_directories(${TARGET_NAME} PRIVATE ${MAIN_INCS})

# ##############################################################################
# CMake Included
# ##############################################################################
add_subdirectory(networks/YOLOv5)
