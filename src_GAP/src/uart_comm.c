/*
 * ----------------------------------------------------------------------
 *
 * File: uart_comm.c
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

#include "uart_comm.h"

uint8_t UART_START_BBOX[] = {0xAB, 0xBA};
uint8_t UART_END_BBOX[] = {0xAC, 0xCA};

uint8_t UART_START_JPEG[] = {0xBC, 0xCB};
uint8_t UART_END_JPEG[] = {0xBD, 0xDB};

uint8_t UART_START_IMAGE[] = {0xCD, 0xDC};
uint8_t UART_END_IMAGE[] = {0xCE, 0xEC};

// WIESEP: Sync with printf mutex
extern SemaphoreHandle_t g_printf_mutex;

// WIESEP: Adopted from source code of
// GAP-Model-Zoo/object_classification/yolox_people_detection/gap_functions/utils/uart_comm.c
void send_image_to_uart(pi_device_t *uart_dev, uint8_t *img, int img_w, int img_h, int pixel_size) {

  xSemaphoreTake(g_printf_mutex, portMAX_DELAY);
  pi_uart_write(uart_dev, UART_START_IMAGE, 2);
  // Write Image row by row
  for (int i = 0; i < img_h; i++)
    pi_uart_write(uart_dev, &(img[i * img_w * pixel_size]), img_w * pixel_size);

  pi_uart_write(uart_dev, UART_END_IMAGE, 2);

  xSemaphoreGive(g_printf_mutex);
}

void send_bboxes_to_uart(pi_device_t *uart_dev, Box *bbox, int num_boxes) {

  xSemaphoreTake(g_printf_mutex, portMAX_DELAY);
  pi_uart_write(uart_dev, UART_START_BBOX, 2);
  // Write Bboxes (only write first 5 bytes)
  for (int i = 0; i < num_boxes; i++) {
    pi_uart_write(uart_dev, &(bbox[i]), sizeof(Box));
  }
  pi_uart_write(uart_dev, UART_END_BBOX, 2);
  pi_uart_write(uart_dev, "\n", 1);
  xSemaphoreGive(g_printf_mutex);
}

void send_jpeg_to_uart(pi_device_t *uart_dev, uint8_t *img, uint32_t img_size) {
  xSemaphoreTake(g_printf_mutex, portMAX_DELAY);

  pi_uart_write(uart_dev, UART_START_JPEG, 2);
  pi_uart_write(uart_dev, &img_size, 4);
  // Write Image row by row
  // pi_uart_write(uart_dev, img, img_size);
  int size = img_size;
  int idx = 0;
  while (size > 0) {
    int size_to_write = (size > 256) ? 256 : size;
    pi_uart_write(uart_dev, &(img[idx]), size_to_write);
    size -= size_to_write;
    idx += size_to_write;
  }

  pi_uart_write(uart_dev, UART_END_JPEG, 2);
  pi_uart_write(uart_dev, "\n", 1);
  xSemaphoreGive(g_printf_mutex);
}