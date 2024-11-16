/*
 * ----------------------------------------------------------------------
 *
 * File: yolo_utils.h
 *
 * Last edited: 30.10.2025
 *
 * Copyright (c) 2024 ETH Zurich and University of Bologna
 *
 * Authors:
 * - Philip Wiese (wiesep@iis.ee.ethz.ch), ETH Zurich
 * - Cristian Cioflan (cioflanc@iis.ee.ethz.ch), ETH Zurich
 * - Vlad Niculescu, (vladn@iis.ee.ethz.ch), ETH Zurich
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

#ifndef __YOLO_UTILS_H__
#define __YOLO_UTILS_H__

#include <stdbool.h>
#include <stdint.h>

#define THRESHOLD_BOX 0.4f  // Filter all boxes below this threshold
#define THRESHOLD_NMS 0.65f // Threshold for IoU in NMS
#define MAX_BOXES 20        // having more than 5 overlapping boxes is unrealistic

typedef struct yolo_output {
  float x;
  float y;
  float w;
  float h;
  float conf;
  float class;
} yolo_output_t;

typedef struct __attribute__((__packed__)) Box {
  float x1, y1, x2, y2;
  float obj_conf, cls_conf;
  char cls_id;
  bool alive;
} Box;

typedef struct yolo_dequantize_arg {
  unsigned char *buffer;
  float *buffer_float;
  uint32_t num_of_cores;
} yolo_dequantize_arg_t;

void print_box(int print_level, Box *box);

void yolo_dequantize_output_cluster(void *arg);

float iou(Box *box1, Box *box2);

int nms(Box *boxes, Box *boxes_out, float nms_thresh, int num_val_boxes);

int yolo_perform_nms_singleclass(float *output_buffer_1_float, Box *bboxes_out);

#endif