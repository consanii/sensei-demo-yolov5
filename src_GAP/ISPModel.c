/*
 * ----------------------------------------------------------------------
 *
 * File: ISPModel.c
 *
 * Last edited: 30.10.2025
 *
 * Copyright (c) 2025 ETH Zurich and University of Bologna
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

#include <stdint.h>
#include <stdio.h>

// AutoTiler Libraries
#include "AutoTilerLib.h"
// Resize generator
#include "ISP_Generators.h"

int main(int argc, char **argv) {
  // This will parse AutoTiler options and perform various initializations
  if (TilerParseOptions(argc, argv)) {
    printf("Failed to initialize or incorrect output arguments directory.\n");
    return 1;
  }
  // Setup AutTiler configuration. Used basic kernel libraries, C names to be used for code generation,
  // compilation options, and amount of shared L1 memory that the AutoTiler can use, here 110000 bytes
  SetInlineMode(ALWAYS_INLINE);
  SetSymbolDynamics();

  SetUsedFilesNames(0, 1, "ISP_BasicKernels.h");
  SetGeneratedFilesNames("ISPKernels.c", "ISPKernels.h");

  SetMemoryDeviceInfos(
      3, AT_MEM_L1, 110000, "ISP_L1_Memory", 0, 0, AT_MEM_L2, 0, "ISP_L2_Memory", 0, 0, AT_MEM_L3_DEFAULTRAM, 0,
      "ISP_L3_Memory", 0,
      1); // This one means that the Ram is externally handled (the user takes care of opening and closing)

  // Load the Resize basic kernels template library
  LoadISPLibrary();
  // Call Resize generator
  BayerOrder_t bayer_mask = RGGB;

  GenerateDeMosaic_OutHWC("demosaic_image_HWC_L2L2", IMG_W, IMG_H, sizeof(unsigned char), 0, 0, bayer_mask);
  GenerateDeMosaic_OutHWC("demosaic_image_HWC_L2L3", IMG_W, IMG_H, sizeof(unsigned char), 0, 1, bayer_mask);

  // Size is coming from CMakelists.txt
  GenerateWB_HWC("white_balance_HWC_L2L2", IMG_W, IMG_H, 0);
  GenerateWB_HWC("white_balance_HWC_L3L3", IMG_W, IMG_H, 1);

  // Now that we are done with model parsing we generate the code
  GenerateTilingCode();
  return 0;
}