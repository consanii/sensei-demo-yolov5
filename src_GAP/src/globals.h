/*
 * ----------------------------------------------------------------------
 *
 * File: globals.h
 *
 * Last edited: 30.10.2025
 *
 * Copyright (c) 2024 ETH Zurich and University of Bologna
 *
 * Authors:
 * - Philip Wiese (wiesep@iis.ee.ethz.ch), ETH Zurich
 *
 * ----------------------------------------------------------------------
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#define DEBUG_LEVEL 1
#define ENABLE_WATCHDOG // Enable watchdog timer
// #define DEBUG_SAVE_CAMERA // Save camera image file
// #define DEBUG_SAVE_YOLO // Save YOLO image file
// #define DEBUG_SAVE_JPEG // Save JPEG image files
#define DEBUG_STREAM_JPEG_UART // Stream JPEG image to UART
// #define DEBUG_INPUT // Load input from file
// #define DEBUG_INPUT_PATTERN // Configure camera to generate a test pattern
// #define DEBUG_PRINT_TIME // Print time taken for each step

// Default values
#ifndef ROWS
#define ROWS 4032
#endif

#ifndef YOLO_INPUT_CHANNEL
#define YOLO_INPUT_CHANNEL 3
#endif

#ifndef YOLO_INPUT_WIDTH
#define YOLO_INPUT_WIDTH 256
#endif

#ifndef YOLO_INPUT_HEIGHT
#define YOLO_INPUT_HEIGHT 256
#endif

#ifndef DOWNSAMPLE_FACTOR
#define DOWNSAMPLE_FACTOR 1
#endif

#ifndef INPUT_IN_L3
#define INPUT_IN_L3 0
#endif

#ifdef SILENT
#define PRINTF(...) ((void)0)
#else
#define PRINTF printf
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

// Global declaration for cluster setup
struct pi_device cluster_dev;
struct pi_cluster_conf cl_conf;
struct pi_cluster_task cl_task;

#include "log.h"

#endif /* GLOBALS_H */