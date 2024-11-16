/*
 * ----------------------------------------------------------------------
 *
 * File: log.h
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

#ifndef __LOG_H__
#define __LOG_H__

#define LOG_LEVEL_TRC 4
#define LOG_LEVEL_DBG 3
#define LOG_LEVEL_INF 2
#define LOG_LEVEL_WRN 1
#define LOG_LEVEL_ERR 0
#define LOG_LEVEL_NONE -1

// Base macro
#define _LOG(level, level_str, ...)                                                                                    \
  {                                                                                                                    \
    if (DEBUG_LEVEL >= level)                                                                                          \
      PRINTF("[GAP9-" level_str "] " __VA_ARGS__);                                                                     \
  }

#define LOG(level, ...) _LOG(level, "INF", __VA_ARGS__)

// Logging level wrappers
#define LOG_ERR(...) _LOG(0, "ERR", __VA_ARGS__)
#define LOG_WRN(...) _LOG(1, "WRN", __VA_ARGS__)
#define LOG_INF(...) _LOG(2, "INF", __VA_ARGS__)
#define LOG_DBG(...) _LOG(3, "DBG", __VA_ARGS__)
#define LOG_TRC(...) _LOG(4, "TRC", __VA_ARGS__)

#endif // __LOG_H__