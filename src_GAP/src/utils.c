/*
 * ----------------------------------------------------------------------
 *
 * File: utils.c
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

#include "utils.h"
#include "globals.h"

#include "gaplib/ImgIO.h"
#include "gaplib/fs_switch.h"

#include "pmsis.h"

void print_avail_l2() {
  uint32_t max_mem, max_block;
  pi_l2_available_get(&max_mem, &max_block);
  LOG_INF("Remaining L2 %u\n", max_mem);
  LOG_INF("Largest block L2 %u\n", max_block);
}

void print_avail_l1() {
  uint32_t max_mem, max_block;
  pi_cl_l1_available_get(&max_mem, &max_block);
  LOG_INF("Remaining L1 %u\n", max_mem);
  LOG_INF("Largest block L1 %u\n", max_block);
}

/**
 * Downsample the image by a factor and crop it and convert it to RGB.
 * If the downsampled image is smaller then the provided output, it is zero padded.
 */
void image_downsample_crop_to_rgb(unsigned char *In, unsigned char *Out, int H_in, int W_in, int H_out, int W_out,
                                  int downsample) {
  int H = MIN(H_in / downsample, H_out);
  int W = MIN(W_in / downsample, W_out);

  for (int j = 0; j < H; j++) {
    for (int i = 0; i < W; i++) {
      int in_y = j * downsample;
      int in_x = i * downsample;

      if (downsample == 1) {
        // Debayer at full resolution
        // Determine the Bayer position based on even/odd row/col
        int is_row_even = (in_y % 2 == 0);
        int is_col_even = (in_x % 2 == 0);

        unsigned char R, G, B;
        if (is_row_even && is_col_even) {
          // R pixel (top-left of RGGB)
          R = In[in_y * W_in + in_x];
          G = (In[in_y * W_in + in_x + 1] + In[(in_y + 1) * W_in + in_x]) / 2;
          B = In[(in_y + 1) * W_in + in_x + 1];
        } else if (is_row_even && !is_col_even) {
          // G pixel (top-right)
          R = (In[in_y * W_in + in_x - 1] + In[in_y * W_in + in_x + 1]) / 2;
          G = In[in_y * W_in + in_x];
          B = (In[(in_y + 1) * W_in + in_x]) / 1;
        } else if (!is_row_even && is_col_even) {
          // G pixel (bottom-left)
          R = (In[(in_y - 1) * W_in + in_x]) / 1;
          G = In[in_y * W_in + in_x];
          B = (In[in_y * W_in + in_x + 1] + In[(in_y + 1) * W_in + in_x]) / 2;
        } else {
          // B pixel (bottom-right)
          R = In[(in_y - 1) * W_in + in_x - 1];
          G = (In[in_y * W_in + in_x - 1] + In[(in_y - 1) * W_in + in_x]) / 2;
          B = In[in_y * W_in + in_x];
        }

        Out[(j * W_out + i) * 3 + 0] = R;
        Out[(j * W_out + i) * 3 + 1] = G;
        Out[(j * W_out + i) * 3 + 2] = B;

      } else {
        // Downsampled debayering using 2x2 RGGB blocks
        if (in_y + 1 >= H_in || in_x + 1 >= W_in) {
          Out[(j * W_out + i) * 3 + 0] = 0;
          Out[(j * W_out + i) * 3 + 1] = 0;
          Out[(j * W_out + i) * 3 + 2] = 0;
          continue;
        }

        unsigned char R = In[in_y * W_in + in_x];
        unsigned char G1 = In[in_y * W_in + in_x + 1];
        unsigned char G2 = In[(in_y + 1) * W_in + in_x];
        unsigned char B = In[(in_y + 1) * W_in + in_x + 1];
        unsigned char G = (G1 + G2) / 2;

        Out[(j * W_out + i) * 3 + 0] = R;
        Out[(j * W_out + i) * 3 + 1] = G;
        Out[(j * W_out + i) * 3 + 2] = B;
      }
    }

    // Pad row to full width
    for (int i = W; i < W_out; i++) {
      Out[(j * W_out + i) * 3 + 0] = 0;
      Out[(j * W_out + i) * 3 + 1] = 0;
      Out[(j * W_out + i) * 3 + 2] = 0;
    }
  }

  // Pad remaining rows
  for (int j = H; j < H_out; j++) {
    for (int i = 0; i < W_out; i++) {
      Out[(j * W_out + i) * 3 + 0] = 0;
      Out[(j * W_out + i) * 3 + 1] = 0;
      Out[(j * W_out + i) * 3 + 2] = 0;
    }
  }
}

/**
 * Downsample the image by a factor and crop it.
 * If the downsampled image is smaller then the provided output, it is zero padded.
 */
void image_downsample_crop(unsigned char *In, unsigned char *Out, int H_in, int W_in, int H_out, int W_out,
                           int downsample) {
  int block_h = H_in / 2;
  int block_w = W_in / 2;
  int H = MIN(block_h / downsample, H_out / 2);
  int W = MIN(block_w / downsample, W_out / 2);

  for (int bj = 0; bj < H; bj++) {
    for (int bi = 0; bi < W; bi++) {
      int in_block_y = bj * downsample * 2;
      int in_block_x = bi * downsample * 2;

      int out_block_y = bj * 2;
      int out_block_x = bi * 2;

      for (int dy = 0; dy < 2; dy++) {
        for (int dx = 0; dx < 2; dx++) {
          int in_idx = (in_block_y + dy) * W_in + (in_block_x + dx);
          int out_idx = (out_block_y + dy) * W_out + (out_block_x + dx);

          Out[out_idx] = In[in_idx];
        }
      }
    }
  }

  // Optional: zero-pad remaining output if needed
  for (int j = H * 2; j < H_out; j++) {
    for (int i = 0; i < W_out; i++) {
      Out[j * W_out + i] = 0;
    }
  }
  for (int j = 0; j < H * 2; j++) {
    for (int i = W * 2; i < W_out; i++) {
      Out[j * W_out + i] = 0;
    }
  }
}

int WriteToFile(unsigned char *image, char *filename, int size) {

  struct pi_fs_conf host_fs_conf;
  pi_fs_conf_init(&host_fs_conf);
  struct pi_device host_fs;

  host_fs_conf.type = PI_FS_HOST;
  pi_open_from_conf(&host_fs, &host_fs_conf);

  if (pi_fs_mount(&host_fs))
    return -1;

  void *File = pi_fs_open(&host_fs, filename, PI_FS_FLAGS_WRITE);
  LOG_INF("Writing image to file: %s\n", filename);

  pi_fs_write(File, image, size);

  pi_fs_close(File);
  pi_fs_unmount(&host_fs);

  return 0;
}
