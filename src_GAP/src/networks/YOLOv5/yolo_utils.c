/*
 * ----------------------------------------------------------------------
 *
 * File: yolo_utils.c
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

#include "yolo_utils.h"

#include "globals.h"
#include "main.h"

#include <stdbool.h>

#include "CNN_Defines.h"
#include "YOLOv5.h"
#include "at_api.h"
#include "pmsis.h"

#include "modelInfos.h"

static Box bboxes[ROWS];

/**
 * @brief Print the box information.
 *
 * @param box Box to print.
 */
void print_box(int print_level, Box *box) {
  if (box->alive == false) {
    LOG(print_level, "Class: %d\n (not active)", box->cls_id);
  } else {
    LOG(print_level, "Class: %d\n", box->cls_id);
  }
  LOG(print_level, " - Box: %.4f %.4f %.4f %.4f\n", box->x1, box->y1, box->x2, box->y2);
  LOG(print_level, " - Obj conf: %0.2f, Class conf: %0.2f\n", box->obj_conf, box->cls_conf);
}

/**
 * @brief Dequantize the output of the YOLO model on the cluster
 *
 * Uses the quantization parameters of the YOLO model to dequantize the output.
 * (`YOLOv5_Output_1_OUT_ZERO_POINT`, `YOLOv5_Output_1_OUT_SCALE`)
 *
 * @param arg Pointer to the argument structure containing the output buffer and the number of cores.
 */
void yolo_dequantize_output_cluster(void *arg) {
  struct yolo_dequantize_arg *yolo_dequantize_arg = (struct yolo_dequantize_arg *)arg;
  uint32_t num_of_cores = yolo_dequantize_arg->num_of_cores;

  uint32_t core_id = pi_core_id();
  uint32_t rows_per_core = (ROWS + num_of_cores - 1) / num_of_cores; // Divide rows among cores
  uint32_t start_row = core_id * rows_per_core;
  uint32_t end_row = MIN(start_row + rows_per_core, ROWS);

  for (uint32_t i = start_row; i < end_row; i++) {
    for (uint32_t j = 0; j < 6; j++) {
      yolo_dequantize_arg->buffer_float[i * 6 + j] =
          (((float)yolo_dequantize_arg->buffer[i * 6 + j]) - YOLOv5_Output_1_OUT_ZERO_POINT) *
          YOLOv5_Output_1_OUT_SCALE;
    }
  }
}

/**
 * @brief Calculate the Intersection over Union (IoU) between two boxes.
 *
 * @param box1 First box.
 * @param box2 Second box.
 * @return float IoU value.
 */
float iou(Box *box1, Box *box2) {
  float x_left = MAX(box1->x1, box2->x1);
  float y_top = MAX(box1->y1, box2->y1);
  float x_right = MIN(box1->x2, box2->x2);
  float y_bottom = MIN(box1->y2, box2->y2);

  if (x_right < x_left || y_bottom < y_top) {
    return 0.0;
  }

  float intersection_area = (x_right - x_left) * (y_bottom - y_top);

  float box1_area = (box1->x2 - box1->x1) * (box1->y2 - box1->y1);
  float box2_area = (box2->x2 - box2->x1) * (box2->y2 - box2->y1);

  float iou = intersection_area / (box1_area + box2_area - intersection_area);

#ifndef SILENT
  if (iou < 0.0) {
    LOG_WRN("Warning: iou is %f < 0.0 \n", iou);
  } else if (iou > 1.0 && (iou - 1.0) > 1e-3) {
    LOG_WRN("Warning: iou is %f > 1.0 \n", iou);
  }
#endif

  return iou;
}

/**
 * @brief Perform Non-Maximum Suppression (NMS) on the boxes.
 *
 * Iterate through all boxes and compare them to each other. If the Intersection over Union (IoU) is above the t
 * hreshold, keep the box with the higher object confidence and discard the other one.
 *
 * @param boxes Array of boxes to perform NMS on.
 * @param Output Output array to store the final boxes.
 * @param nms_thresh Threshold for the IoU.
 */
int nms(Box *boxes, Box *boxes_out, float nms_thresh, int num_val_boxes) {
  int count = 0;
  int val_final_boxes = 0;

  for (int i = 0; i < num_val_boxes; i++) {
    if (boxes[i].alive == true) {

      for (int j = 0; j < num_val_boxes; j++) {
        if (i != j && boxes[j].alive == true) {

          // Calculate Intersection over Union
          float iou_val = iou(&boxes[i], &boxes[j]);

          // If IoU is above threshold, keep the box with the higher object confidence
          if (iou_val >= nms_thresh) {
            LOG_TRC("IoU between box %d and box %d: %f\n", i, j, iou_val);
            LOG_TRC("Box1 %d: ", i);
            print_box(LOG_LEVEL_TRC, &boxes[i]);
            LOG_TRC("Box2 %d: ", j);
            print_box(LOG_LEVEL_TRC, &boxes[j]);
            if (boxes[i].obj_conf > boxes[j].obj_conf) {
              boxes[j].alive = false;
              LOG_TRC("=> Turn off box2 %d\n", j);
              print_box(LOG_LEVEL_TRC, &boxes[j]);
            } else {
              LOG_TRC("=> Turn off box1 %d\n", i);
              print_box(LOG_LEVEL_TRC, &boxes[i]);
              boxes[i].alive = false;
            }
          }
        }
      }

      // Copy final boxes to the output buffer
      if (boxes[i].alive == 1) {
        LOG_TRC("Append box %d\n", i);
        print_box(LOG_LEVEL_TRC, &boxes[i]);
        memcpy(&boxes_out[val_final_boxes], &boxes[i], sizeof(Box));
        val_final_boxes += 1;
      }
    }
  }

  // Return the number of final boxes
  return val_final_boxes;
}

/*
 * @param output_buffer_1_float Output buffer of the YOLO model.
 */
int yolo_perform_nms_singleclass(float *output_buffer_1_float, Box *bboxes_out) {
  // All boxes above threshold
  int num_val_boxes = 0;

  // Top MAX_BOXES boxes
  int nms_valid_boxes = 0;

  // Final boxes after NMS
  int final_valid_boxes = 0;

  yolo_output_t *prediction = (yolo_output_t *)output_buffer_1_float;

  // Extract all the boxes above the threshold
  for (int i = 0; i < ROWS; i++) {
    float score = (prediction[i]).conf;
    if (score > THRESHOLD_BOX) {
      bboxes[num_val_boxes].x1 = prediction[i].x - prediction[i].w / 2;
      bboxes[num_val_boxes].y1 = prediction[i].y - prediction[i].h / 2;
      bboxes[num_val_boxes].x2 = prediction[i].x + prediction[i].w / 2;
      bboxes[num_val_boxes].y2 = prediction[i].y + prediction[i].h / 2;
      bboxes[num_val_boxes].alive = true;
      bboxes[num_val_boxes].obj_conf = prediction[i].conf;
      bboxes[num_val_boxes].cls_conf = prediction[i].class;
      bboxes[num_val_boxes].cls_id = 1;
      num_val_boxes++;
    }
  }
  LOG_TRC("Found %d initial boxes\n", num_val_boxes);

  // Only keep the top MAX_BOXES boxes
  nms_valid_boxes = (num_val_boxes > MAX_BOXES) ? (MAX_BOXES) : (num_val_boxes);

  // Perform Non-Maximum Suppression to extract the final boxes
  final_valid_boxes = nms(bboxes, bboxes_out, THRESHOLD_NMS, nms_valid_boxes);

  LOG_INF("Found %d final boxes\n", final_valid_boxes);

  return final_valid_boxes;
}