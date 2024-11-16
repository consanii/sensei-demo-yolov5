/*
 * ----------------------------------------------------------------------
 *
 * File: main.c
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

#include "main.h"
#include "hm0360_regs.h"

// Peripherals
#include "Gap.h"
#include "pmsis.h"

#include "bsp/bsp.h"
#include "bsp/camera/hm0360.h"
#include "bsp/ram.h"
#include "gaplib/ImgIO.h"
#include "gaplib/fs_switch.h"
#include "gaplib/jpeg_encoder.h"

#include "l2_malloc.h"
#include "l2_priv_malloc.h"
#include "linker.h"

// Models
#include "YOLOv5.h"

#include "ISPKernels.h"
#include "YOLOv5Kernels.h"

#include "at_api.h"
#include "at_api_pmsis.h"

#include "uart_comm.h"
#include "utils.h"
#include "yolo_utils.h"

#define PAD_GPIO_46 (PI_PAD_046)
#define PAD_GPIO_47 (PI_PAD_047)
#define PAD_GPIO_48 (PI_PAD_048)
#define PAD_GPIO_49 (PI_PAD_049)
#define PAD_GPIO_50 (PI_PAD_050)
#define PAD_GPIO_51 (PI_PAD_051)

#define DEBUG_BUTTON_3 (PAD_GPIO_46)
#define DEBUG_LED_RED (PAD_GPIO_47)

AT_DEFAULTFLASH_EXT_ADDR_TYPE YOLOv5_L3_Flash = 0;

#define CAMERA_WIDTH CONFIG_DRIVER_HM0360_FORMAT_WIDTH
#define CAMERA_HEIGHT CONFIG_DRIVER_HM0360_FORMAT_HEIGHT

// Buffer size is max of the two output sizes using preprocessor
#define CAMERA_BUFFER_SIZE (CAMERA_WIDTH * CAMERA_HEIGHT)
#define YOLO_BUFFER_SIZE (YOLO_INPUT_CHANNEL * YOLO_INPUT_WIDTH * YOLO_INPUT_HEIGHT)
#define JPEG_BUFF_SIZE 32 * 1024

#define ISP_ADJUST_DELAY_US 500000
pi_device_t *camera_device;
pi_device_t *uart_dev;

pi_evt_t end_of_capture_evt;
pi_evt_t cb_gpio_task;

PI_L2 unsigned char *camera_buffer;
PI_L2 unsigned char *yolo_buffer;
PI_L2 unsigned char *yolo_buffer_L2;
PI_L2 unsigned char *jpeg_buffer;
PI_L2 unsigned char *Output_1;
PI_L2 float *Output_1_float;

L2_MEM Box bboxes_out[MAX_BOXES];

static uint32_t iteration = 0;

struct pi_device DefaultRam;

bool enable_jtag_stream = true;

/*******************************************************************************
 * Utils Functions
 ******************************************************************************/
#ifdef DEBUG_INPUT
switch_fs_t input_fs;
void *Input_File_Input_1;
int Input_File_Input_1_Position;
int open_inputs() {
  __FS_INIT(input_fs);

  Input_File_Input_1 = __OPEN_READ(input_fs, "../src/networks/YOLOv5/" YOLO_MODEL_DIR "/Input_1.bin");

  if (!Input_File_Input_1)
    return 1;
  Input_File_Input_1_Position = 0;
  return 0;
}

int copy_inputs() {
  int ret_Input_1 = 0;
  __SEEK(Input_File_Input_1, Input_File_Input_1_Position);

#if (INPUT_IN_L3 == 1)
  unsigned char *yolo_buffer_L2 = (unsigned char *)pi_l2_malloc(YOLO_BUFFER_SIZE);
  ret_Input_1 = __READ(Input_File_Input_1, yolo_buffer_L2, YOLO_BUFFER_SIZE);
  pi_ram_write(&DefaultRam, (uint32_t)yolo_buffer, yolo_buffer_L2, YOLO_BUFFER_SIZE);
  pi_l2_free(yolo_buffer_L2, YOLO_BUFFER_SIZE);
#else
  ret_Input_1 = __READ(Input_File_Input_1, yolo_buffer, YOLO_BUFFER_SIZE);
#endif
  if (ret_Input_1 != YOLO_BUFFER_SIZE) {
    return 0;
  }
  Input_File_Input_1_Position = 0;
  return 1;
}
#endif

void cluster_config() {
  pi_cluster_conf_init(&cl_conf);
  cl_conf.cc_stack_size = STACK_SIZE;
  cl_conf.id = 0; /* Set cluster ID. */
                  // Enable the special icache for the master core
  cl_conf.icache_conf = PI_CLUSTER_MASTER_CORE_ICACHE_ENABLE |
                        // Enable the prefetch for all the cores, it's a 9bits mask (from bit 2
                        // to bit 10), each bit correspond to 1 core
                        PI_CLUSTER_ICACHE_PREFETCH_ENABLE |
                        // Enable the icache for all the cores
                        PI_CLUSTER_ICACHE_ENABLE;
  pi_open_from_conf(&cluster_dev, (void *)&cl_conf);
  if (pi_cluster_open(&cluster_dev)) {
    LOG_ERR("Cluster open failed !\n");
    pmsis_exit(-10);
  }
}

void dump_allocators(int print_level, bool print_L1) {
  pi_aps256xxn_data_t *aps256xxn = (pi_aps256xxn_data_t *)DefaultRam.data;

  LOG(print_level, "=> L3\n");
  extern_alloc_dump(&aps256xxn->alloc);
  LOG(print_level, "=> L2\n");
  pi_l2_malloc_dump();
  print_avail_l2();
  if (print_L1) {
    LOG(print_level, "=> L1\n");
    pi_l1_malloc_dump(0);
    print_avail_l1();
  }
}

/*******************************************************************************
 * Cluster Functions
 ******************************************************************************/
static void cluster_yolo(void *arg) { YOLOv5CNN(yolo_buffer, Output_1); }

static void cluster_image_preprocess(void *arg) {
#if (INPUT_IN_L3 == 1)
  demosaic_image_HWC_L2L3(camera_buffer, yolo_buffer);
  white_balance_HWC_L3L3(yolo_buffer, yolo_buffer, 96);
#else
  demosaic_image_HWC_L2L2(camera_buffer, yolo_buffer);
  white_balance_HWC_L2L2(yolo_buffer, yolo_buffer, 96);
#endif
}

static void cluster_dequantize_output(void *arg) {
  struct yolo_dequantize_arg *yolo_dequantize_arg = (struct yolo_dequantize_arg *)arg;
  pi_cl_team_fork(yolo_dequantize_arg->num_of_cores, yolo_dequantize_output_cluster, arg);
  return;
}

/*******************************************************************************
 * YOLOv5 Functions (Call from FC)
 ******************************************************************************/
int32_t yolo_construct() {
  LOG_INF("YOLOv5CNN_Construct\n");
  cluster_config();

#if (DEBUG_LEVEL >= LOG_LEVEL_TRC)
  LOG_TRC("Before YOLOv5CNN_Construct\n");
  dump_allocators(LOG_LEVEL_TRC, 1);
#endif

  int ConstructorErr = YOLOv5CNN_Construct();
  if (ConstructorErr) {
    LOG_ERR("Graph constructor exited with error: (%s)\n", GetAtErrorName(ConstructorErr));
    return -1;
  }

#if (DEBUG_LEVEL >= LOG_LEVEL_TRC)
  LOG_TRC("After YOLOv5CNN_Construct\n");
  dump_allocators(LOG_LEVEL_TRC, 1);
#endif

  return 0;
}

void yolo_destruct() {
  YOLOv5CNN_Destruct();
#if (DEBUG_LEVEL >= LOG_LEVEL_TRC)
  LOG_TRC("After YOLOv5CNN_Destruct\n");
  dump_allocators(LOG_LEVEL_TRC, 1);
#endif
  pi_cluster_close(&cluster_dev);
}

void yolo_inference() {
  struct pi_cluster_task task;

  pi_cluster_task(&task, (void (*)(void *))cluster_yolo, NULL);
  pi_cluster_task_stacks(&task, NULL, SLAVE_STACK_SIZE);

  pi_cluster_send_task_to_cl(&cluster_dev, &task);
}

/*******************************************************************************
 * Dequantization Functions (Call from FC)
 ******************************************************************************/
void dequantize_output(unsigned char *buffer, float *buffer_float) {
  cluster_config();

  struct pi_cluster_task task;
  struct yolo_dequantize_arg yolo_dequantize_arg;
  yolo_dequantize_arg.buffer = buffer;
  yolo_dequantize_arg.buffer_float = buffer_float;
  yolo_dequantize_arg.num_of_cores = pi_cl_cluster_nb_cores();

  pi_cluster_task(&task, (void (*)(void *))cluster_dequantize_output, &yolo_dequantize_arg);
  pi_cluster_task_stacks(&task, NULL, SLAVE_STACK_SIZE);

  pi_cluster_send_task_to_cl(&cluster_dev, &task);

  pi_cluster_close(&cluster_dev);
}

/*******************************************************************************
 * Image Preprocessing Functions (Call from FC)
 ******************************************************************************/
void image_preprocess() {
  cluster_config();

  struct pi_cluster_task task;

  pi_cluster_task(&task, (void (*)(void *))cluster_image_preprocess, NULL);
  pi_cluster_task_stacks(&task, NULL, SLAVE_STACK_SIZE);

  ISP_L1_Memory = (char *)pi_l1_malloc(&cluster_dev, _ISP_L1_Memory_SIZE);
  if (ISP_L1_Memory == 0) {
    LOG_ERR("Failed to allocate %d bytes for L1_memory\n", _ISP_L1_Memory_SIZE);
    pmsis_exit(-12);
  }

  ISP_L2_Memory = (char *)pi_l2_malloc(_ISP_L2_Memory_SIZE);
  if (ISP_L2_Memory == 0) {
    LOG_ERR("Failed to allocate %d bytes for L2_memory\n", _ISP_L2_Memory_SIZE);
    pmsis_exit(-13);
  }

  pi_cluster_send_task_to_cl(&cluster_dev, &task);

  pi_l1_free(&cluster_dev, ISP_L1_Memory, _ISP_L1_Memory_SIZE);
  pi_l2_free(ISP_L2_Memory, _ISP_L2_Memory_SIZE);

  pi_cluster_close(&cluster_dev);
}

/*******************************************************************************
 * JPEG Functions (Call from FC)
 ******************************************************************************/
void jpeg_compress(uint8_t *image, uint8_t *jpeg_image, int *size, int height, int width, int channels) {

  jpeg_encoder_t enc;
  unsigned int image_size = height * width * channels;

  struct jpeg_encoder_conf enc_conf;
  jpeg_encoder_conf_init(&enc_conf);

#ifdef RUN_ENCODER_ON_CLUSTER
  enc_conf.flags = JPEG_ENCODER_FLAGS_CLUSTER_OFFLOAD;
#else
  enc_conf.flags = 0x0;
#endif

  // For color Jpeg this flag can be added
  enc_conf.flags |= JPEG_ENCODER_FLAGS_COLOR;
  enc_conf.width = width;
  enc_conf.height = height;

  if (jpeg_encoder_open(&enc, &enc_conf)) {
    LOG_ERR("Error opening JPEG encoder\n");
    pmsis_exit(-14);
  }

  if (jpeg_encoder_start(&enc)) {
    LOG_ERR("Error starting JPEG encoder\n");
    pmsis_exit(-15);
  }

  // Get the header so that we can produce full JPEG image
  pi_buffer_t bitstream;
  bitstream.data = jpeg_image;
  bitstream.size = image_size;
  uint32_t header_size, footer_size, body_size;

  if (jpeg_encoder_header(&enc, &bitstream, &header_size)) {
    LOG_ERR("Error getting JPEG header\n");
    pmsis_exit(-16);
  }

  // Now get the encoded image
  pi_buffer_t buffer;
  buffer.data = image;
  buffer.size = image_size;
  buffer.width = width;
  buffer.height = height;
  bitstream.data = &jpeg_image[header_size];

  if (jpeg_encoder_process(&enc, &buffer, &bitstream, &body_size)) {
    LOG_ERR("Error encoding JPEG image\n");
    pmsis_exit(-17);
  }

  // An finally get the footer
  bitstream.data = &jpeg_image[body_size + header_size];
  if (jpeg_encoder_footer(&enc, &bitstream, &footer_size)) {
    LOG_ERR("Error getting JPEG footer\n");
    pmsis_exit(-18);
  }

  // calculate the total size and return it
  int bitstream_size = body_size + header_size + footer_size;
  *size = bitstream_size;

  // close the endoer
  jpeg_encoder_stop(&enc);

  jpeg_encoder_close(&enc);
}

static void __pi_gpio_cb() {
  // Switch enable_jtag_stream
  enable_jtag_stream = !enable_jtag_stream;

  // Debounce the button
  pi_time_wait_us(100000);
}

/*******************************************************************************
 * Main Application
 ******************************************************************************/
int main(void) {

  // Configure the LED
  pi_pad_function_set(DEBUG_LED_RED, PI_PAD_FUNC1);
  pi_gpio_pin_configure(DEBUG_LED_RED, PI_GPIO_OUTPUT | PI_GPIO_PULL_DISABLE | PI_GPIO_DRIVE_STRENGTH_LOW);
  pi_pad_function_set(DEBUG_BUTTON_3, PI_PAD_FUNC1);
  pi_gpio_pin_configure(DEBUG_BUTTON_3, PI_GPIO_INPUT | PI_GPIO_PULL_UP | PI_GPIO_DRIVE_STRENGTH_HIGH);

  pi_evt_callback_no_irq_init(&cb_gpio_task, __pi_gpio_cb, NULL);
  if (pi_gpio_pin_task_add(DEBUG_BUTTON_3, &cb_gpio_task, PI_GPIO_NOTIF_FALL)) {
    LOG_ERR("Failed to add GPIO task\n");
    pmsis_exit(-1);
  }

  pi_gpio_pin_write(DEBUG_LED_RED, 1);
  pi_time_wait_us(1000000); //  Wait for 1s
  pi_gpio_pin_write(DEBUG_LED_RED, 0);

  LOG_INF("Starting main program\n");

  LOG_INF("UART Configuration\n");
  if (pi_open(PI_UART_UART0, &uart_dev)) {
    LOG_ERR("UFailed to open uart device\n");
    pmsis_exit(-1);
  }
  LOG_DBG("UART device opened\n");

  LOG_INF("Frequency Configuration\n");
  if (pi_freq_set(PI_FREQ_DOMAIN_FC, FREQ_FC * 1000 * 1000)) {
    LOG_ERR("Error setting frequency !\n");
    pi_gpio_pin_write(DEBUG_LED_RED, 1);
    pmsis_exit(-2);
  }
  if (pi_freq_set(PI_FREQ_DOMAIN_PERIPH, 225 * 1000 * 1000)) {
    LOG_ERR("Error setting frequency !\n");
    pi_gpio_pin_write(DEBUG_LED_RED, 1);
    pmsis_exit(-3);
  }
  LOG_DBG("Frequency set\n");

  LOG_INF("Voltage Configuration\n");
  if (pi_pmu_voltage_set(PI_PMU_VOLTAGE_DOMAIN_CHIP, PI_PMU_VOLT_800)) {
    LOG_ERR("Error setting voltage !\n");
    pi_gpio_pin_write(DEBUG_LED_RED, 1);
    pmsis_exit(-4);
  }
  LOG_DBG("Voltage set\n");

  // Wait for a short moment  to ensure power is stable
  pi_time_wait_us(100000);

  LOG_INF("RAM Configuration\n");
  struct pi_default_ram_conf ram_conf;
  pi_default_ram_conf_init(&ram_conf);

  ram_conf.baudrate = FREQ_FC * 1000 * 1000;
  pi_open_from_conf(&DefaultRam, &ram_conf);
  if (bsp_aps256xxn_open(&DefaultRam)) {
    LOG_ERR("Error ram open !\n");
    pi_gpio_pin_write(DEBUG_LED_RED, 1);
    pmsis_exit(-5);
  }
  LOG_DBG("RAM Opened\n");

  LOG_INF("Cluster Configuration\n");
  cluster_config();
  pi_cluster_close(&cluster_dev);
  LOG_DBG("Cluster configured\n");

  LOG_INF("Frequency Configuration\n");
  pi_freq_set(PI_FREQ_DOMAIN_CL, FREQ_CL * 1000 * 1000);
  LOG_DBG("Frequency set\n");

  LOG_INF("Camera Configuration\n");
  pi_err_t err = pi_open(PI_CAMERA_HM0360, &camera_device);
  if (err) {
    LOG_ERR("Failed to open camera device\n");
    pi_gpio_pin_write(DEBUG_LED_RED, 1);
    pmsis_exit(-6);
  }

  // Vertically and horizontally flip the image
  uint8_t reg_value = 0b11;
  pi_camera_reg_set(camera_device, HM0360_IMAGE_ORIENTATION, &reg_value);

  // Enable premeter after every wakeup
  reg_value = 0x01;
  pi_camera_reg_set(camera_device, HM0360_PMU_CFG_5, &reg_value);

  // Configure go capture one frame
  reg_value = 0x01;
  pi_camera_reg_set(camera_device, HM0360_PMU_CFG_7, &reg_value);
  pi_time_wait_us(ISP_ADJUST_DELAY_US);

#if (defined DEBUG_INPUT_PATTERN)
  // WIESEP: Disable auto exposure
  reg_value = 0x00;
  pi_camera_reg_set(camera_device, HM0360_AE_CTRL, &reg_value);
  pi_camera_reg_set(camera_device, HM0360_AE_CTRL1, &reg_value);

  // WIESEP: Make camera generat test pattern to not change the integration time
  reg_value = 0x01;
  pi_camera_reg_set(camera_device, HM0360_TEST_PATTERN_MODE, &reg_value);
#endif
  LOG_DBG("Camera configured\n");

  char ImageName[128];

#ifdef DEBUG_INPUT
  LOG_INF("Open Inputs\n");
  if (open_inputs()) {
    pmsis_exit(-7);
  }
  LOG_DBG("Inputs opened\n");
#endif

#ifdef ENABLE_WATCHDOG
  LOG_INF("Watchdog Configuration\n");
  if (pi_watchdog_timer_set(2000000)) {
    LOG_ERR("Error when setting the watchdog timer\n");
    pi_gpio_pin_write(DEBUG_LED_RED, 1);
    pmsis_exit(-8);
  }
  LOG_DBG("Watchdog timer set\n");
#endif

#if (DEBUG_LEVEL >= LOG_LEVEL_INF)
  LOG_INF("Heap Allocation Info\n");
  dump_allocators(LOG_LEVEL_INF, 0);
#endif

  uint64_t t1, t2, t3, t4, t5, t6;
  t1 = pi_time_get_us();
  while (1) {

    pi_gpio_pin_toggle(DEBUG_LED_RED);
    pi_gpio_pin_toggle(DEBUG_BUTTON_3);

    ////////////////////////////////////////////////////////////////////////////
    // Input Image Acquisition and Preprocessing
    ////////////////////////////////////////////////////////////////////////////

    //
    // Buffer Allocation
    //
#if (INPUT_IN_L3 == 1)
    pi_ram_alloc(&DefaultRam, (void **)&yolo_buffer, YOLO_BUFFER_SIZE);
#else
    yolo_buffer = (unsigned char *)pi_l2_malloc(YOLO_BUFFER_SIZE);
#endif

#ifndef DEBUG_INPUT
    LOG_INF("Allocating %d bytes for camera_buffer\n", CAMERA_BUFFER_SIZE);
    camera_buffer = (unsigned char *)pi_l2_malloc(CAMERA_BUFFER_SIZE);

    if (yolo_buffer == NULL) {
      LOG_ERR("Failed to allocate %d bytes for yolo_buffer\n", YOLO_BUFFER_SIZE);
      pmsis_exit(-9);
    }

    //
    // Image Acquisition
    //
    LOG_INF("Acquiring Image\n");
    pi_camera_capture_async(camera_device, camera_buffer, CAMERA_BUFFER_SIZE, pi_evt_sig_init(&end_of_capture_evt));

    // Capture single frame
    // WIESEP: Fix weird bug for configuration
#if (YOLO_INPUT_WIDTH == 320) && (YOLO_INPUT_HEIGHT == 320)
    reg_value = 0x01;
#else
    reg_value = 0x01;
#endif
    pi_camera_reg_set(camera_device, HM0360_PMU_CFG_7, &reg_value);
    pi_camera_control(camera_device, PI_CAMERA_CMD_SNAPSHOT, 0);
    pi_camera_control(camera_device, PI_CAMERA_CMD_START, 0);

    // Wait to acquire an image
    pi_evt_wait(&end_of_capture_evt);
    pi_camera_control(camera_device, PI_CAMERA_CMD_STOP, 0);

#if (defined DEBUG_SAVE_CAMERA)
    LOG_INF("Saving Grayscale Image...\n");
    sprintf(ImageName, "../images/Image_%04d.pgm", iteration);
    WriteImageToFile(ImageName, CAMERA_WIDTH, CAMERA_HEIGHT, 1, camera_buffer, GRAY_SCALE_IO);
#endif

    //
    // Image Preprocessing
    //
    t2 = pi_time_get_us();
    pi_gpio_pin_toggle(DEBUG_BUTTON_3);

    LOG_INF("Converting to RGB\n");
    image_downsample_crop((unsigned char *)camera_buffer, (unsigned char *)camera_buffer, CAMERA_HEIGHT, CAMERA_WIDTH,
                          YOLO_INPUT_HEIGHT, YOLO_INPUT_WIDTH, DOWNSAMPLE_FACTOR);

    LOG_INF("Allocating %d bytes for yolo_buffer\n", YOLO_BUFFER_SIZE);

    LOG_INF("Performing white balance\n");
    image_preprocess();

    pi_l2_free(camera_buffer, CAMERA_BUFFER_SIZE);

    //
    // JPEG Image Compression and Streaming
    //
#if (defined DEBUG_SAVE_JPEG) || (defined DEBUG_STREAM_JPEG_UART) || (defined DEBUG_SAVE_YOLO)
#if (INPUT_IN_L3 == 1)
    yolo_buffer_L2 = (unsigned char *)pi_l2_malloc(YOLO_BUFFER_SIZE);

    // Load image from RAM
    pi_ram_read(&DefaultRam, (uint32_t)yolo_buffer, yolo_buffer_L2, YOLO_BUFFER_SIZE);
#else
    yolo_buffer_L2 = yolo_buffer;
#endif
#endif

#if (defined DEBUG_SAVE_JPEG) || (defined DEBUG_STREAM_JPEG_UART)
    jpeg_buffer = (unsigned char *)pi_l2_malloc(JPEG_BUFF_SIZE);
    int bitstream_size;

    LOG_DBG("Start JPEG encoding\n");
    int start_jpeg = pi_time_get_us();
    jpeg_compress(yolo_buffer_L2, jpeg_buffer, &bitstream_size, YOLO_INPUT_HEIGHT, YOLO_INPUT_WIDTH,
                  YOLO_INPUT_CHANNEL);
    int elapsed_jpeg = pi_time_get_us() - start_jpeg;

    LOG_INF("JPEG Compression --> from %d bytes to %d bytes (%.2fx compression) in %d us\n",
            YOLO_INPUT_WIDTH * YOLO_INPUT_HEIGHT * YOLO_INPUT_CHANNEL, bitstream_size,
            ((float)YOLO_INPUT_WIDTH * YOLO_INPUT_HEIGHT * YOLO_INPUT_CHANNEL) / bitstream_size, elapsed_jpeg);
#endif

#if (defined DEBUG_SAVE_JPEG)
    LOG_INF("Saving %d bytes JPEG Image...\n", bitstream_size);
    sprintf(ImageName, "../images/Image_%04d.jpg", iteration);
    WriteToFile(jpeg_buffer, ImageName, bitstream_size);
#endif

#if (defined DEBUG_STREAM_JPEG_UART)
    if (enable_jtag_stream) {
      LOG_INF("Streaming %d bytes JPEG image\n", bitstream_size);
      send_jpeg_to_uart(uart_dev, jpeg_buffer, bitstream_size);
    } else {
      LOG_INF("Streaming %d bytes JPEG image (JTAG disabled)\n", bitstream_size);
    }
#endif

#if (defined DEBUG_SAVE_JPEG) || (defined DEBUG_STREAM_JPEG_UART)
    pi_l2_free(jpeg_buffer, JPEG_BUFF_SIZE);
#endif

#else // DEBUG_INPUT
    t2 = pi_time_get_us();
#if (INPUT_IN_L3 == 1)
    pi_ram_alloc(&DefaultRam, (void **)&yolo_buffer, YOLO_BUFFER_SIZE);
    if (yolo_buffer == 0) {
      LOG_ERR("Failed to allocate %d bytes for yolo_buffer_ram\n", YOLO_BUFFER_SIZE);
      pmsis_exit(-10);
    }
#else
    yolo_buffer = (unsigned char *)pi_l2_malloc(YOLO_BUFFER_SIZE);
#endif

    LOG_INF("Copying Inputs...\n");
    copy_inputs();
#endif // DEBUG_INPUT

#if (defined DEBUG_SAVE_YOLO)
    LOG_INF("Saving YOLO Image...\n");
    sprintf(ImageName, "../images/Image_%04d.ppm", iteration);
    WriteImageToFile(ImageName, YOLO_INPUT_WIDTH, YOLO_INPUT_HEIGHT, YOLO_INPUT_CHANNEL, yolo_buffer_L2, RGB888_IO);
#endif

#if (defined DEBUG_SAVE_JPEG) || (defined DEBUG_STREAM_JPEG_UART) || (defined DEBUG_SAVE_YOLO)
#if (INPUT_IN_L3 == 1)
    pi_l2_free(yolo_buffer_L2, YOLO_BUFFER_SIZE);
#endif
#endif

    ////////////////////////////////////////////////////////////////////////////
    // YOLOv5 Object Detection
    ////////////////////////////////////////////////////////////////////////////
    t3 = pi_time_get_us();
    pi_gpio_pin_toggle(DEBUG_BUTTON_3);
#ifdef ENABLE_WATCHDOG
    pi_watchdog_stop();
    pi_watchdog_timer_rearm();
    pi_watchdog_start();
#endif

    LOG_INF("Allocating Model Buffer\n");
    if (yolo_construct() != 0) {
      LOG_ERR("Failed to allocate model buffer\n");
      pmsis_exit(-11);
    }

    // Allocate Output1
    Output_1 = (unsigned char *)pi_l2_malloc(ROWS * 6);

    // Object detection model inference (Yolo v5)
    LOG_INF("Model Inference\n");
    yolo_inference();

#if (DEBUG_LEVEL >= LOG_LEVEL_TRC)
    LOG_TRC("Input:\n");
    for (int i = 0; i < 10; i++) {
      LOG_TRC("- %d: ", i);
      for (int j = 0; j < 3; j++) {
        PRINTF("%3d ", yolo_buffer[i * 6 + j]);
      }
      PRINTF("\n");
    }

    LOG_TRC("Output:\n");
    for (int i = 0; i < 10; i++) {
      LOG_TRC("- %d: ", i);
      for (int j = 0; j < 6; j++) {
        PRINTF("%3d ", Output_1[i * 6 + j]);
      }
      PRINTF("\n");
    }
#endif
    LOG_INF("Freeing Model Buffer\n");
    yolo_destruct();

    t4 = pi_time_get_us();
    pi_gpio_pin_toggle(DEBUG_BUTTON_3);

    LOG_INF("Running Non-Maximum Suppression\n");
    Output_1_float = (float *)pi_l2_malloc(ROWS * 6 * sizeof(float));
    dequantize_output(Output_1, Output_1_float);
    pi_l2_free(Output_1, ROWS * 6);

    t5 = pi_time_get_us();
    pi_gpio_pin_toggle(DEBUG_BUTTON_3);

    uint32_t final_valid_boxes = yolo_perform_nms_singleclass(Output_1_float, bboxes_out);
    pi_l2_free(Output_1_float, ROWS * 6 * sizeof(float));

#if (DEBUG_LEVEL >= LOG_LEVEL_DBG)
    if (final_valid_boxes > 0) {
      LOG_INF("Boxes:\n");
      for (int i = 0; i < final_valid_boxes; i++) {
        LOG_INF("- Box %d: ", i);
        print_box(LOG_LEVEL_INF, &bboxes_out[i]);
      }
    }
#endif
    send_bboxes_to_uart(uart_dev, bboxes_out, final_valid_boxes);

    //
    // Deallocate buffers
    //
#if (INPUT_IN_L3 == 1)
    pi_ram_free(&DefaultRam, (uint32_t)yolo_buffer, YOLO_BUFFER_SIZE);
#else
    pi_l2_free(yolo_buffer, YOLO_BUFFER_SIZE);
#endif

    iteration++;

    t6 = pi_time_get_us();
    pi_gpio_pin_toggle(DEBUG_BUTTON_3);
    int64_t elapsed_loop = t6 - t1;
    int64_t elapsed_acquisition = t2 - t1;
    int64_t elapsed_preprocess = t3 - t2;
    int64_t elapsed_inference = t4 - t3;
    int64_t elapsed_dequant = t5 - t4;
    int64_t elapsed_nms = t6 - t5;

#ifndef DEBUG_PRINT_TIME
    t1 = pi_time_get_us();
    PRINTF("%.2f\n", 1000000.0 / elapsed_loop);
#else
    PRINTF("[GAP9-INF] Iteration %d Time loop %u us (%.2f FPS)\n", iteration, elapsed_loop, 1000000.0 / elapsed_loop);
    PRINTF("[GAP9-INF]  - [%4d] Image Acquisition:        %u us\n", iteration, elapsed_acquisition);
    PRINTF("[GAP9-INF]  - [%4d] Image Preprocessing:      %u us\n", iteration, elapsed_preprocess);
    PRINTF("[GAP9-INF]  - [%4d] YOLOv5 Inference:         %u us\n", iteration, elapsed_inference);
    PRINTF("[GAP9-INF]  - [%4d] Dequantization:           %u us\n", iteration, elapsed_dequant);
    PRINTF("[GAP9-INF]  - [%4d] Non-Maximum Suppression:  %u us\n", iteration, elapsed_nms);
    PRINTF("[GAP9-INF]  - [%4d] Total Time:               %u us\n", iteration, elapsed_loop);

    t1 = pi_time_get_us();
#endif

    // WIESEP: Only for plotting
    // pi_time_wait_us(200000);
  }

  pmsis_exit(0);
  return 0;
}