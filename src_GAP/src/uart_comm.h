/*
 * ----------------------------------------------------------------------
 *
 * File: uart_comm.h
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

#ifndef __UART_COMM_H__
#define __UART_COMM_H__

#include "bsp/bsp.h"
#include "pmsis.h"
#include "yolo_utils.h"

void send_image_to_uart(pi_device_t *uart_dev, uint8_t *img, int img_w, int img_h, int pixel_size);
void send_bboxes_to_uart(pi_device_t *uart_dev, Box *bbox, int num_boxes);
void send_jpeg_to_uart(pi_device_t *uart_dev, uint8_t *img, uint32_t img_size);
#endif /* __UART_COMM_H__ */