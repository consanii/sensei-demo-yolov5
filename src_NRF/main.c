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

#include <stdio.h>
#include <string.h>

#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/led.h>
#include <zephyr/drivers/uart.h>

#include <zephyr/logging/log.h>
#include <zephyr/logging/log_ctrl.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gatt.h>

#include <bluetooth/services/nus.h>

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/usbd.h>

#include "ubxlib.h"

#include "u_cfg_app_platform_specific.h"
#include "u_gnss.h"

#include "bluetooth.h"

#include "bsp/pwr_bsp.h"
#include "i2c_helpers.h"
#include "pwr/pwr.h"

#include "bh1730fvc_reg.h"
#include "bme688_reg.h"
#include "ilps28qsw_reg.h"
#include "ism330dhcx_reg.h"

// To remove logging errors in IntelliSense
#ifdef __INTELLISENSE__
#ifdef LOG_ERR
#undef LOG_ERR
#endif
#ifdef LOG_WRN
#undef LOG_WRN
#endif
#ifdef LOG_INF
#undef LOG_INF
#endif
#ifdef LOG_DBG
#undef LOG_DBG
#endif
#define LOG_ERR(...) ((void)0)
#define LOG_WRN(...) ((void)0)
#define LOG_INF(...) ((void)0)
#define LOG_DBG(...) ((void)0)
#endif

// Required to allow overwriting the boot mode of GAP9 via the debug PCB
#define LED_NODE DT_NODELABEL(led_0)
#define UART_GAP_NODE DT_NODELABEL(uart_gap)
#define GPIO_NODE_debug_green DT_NODELABEL(gpio_debug_led_green)
#define GPIO_NODE_debug_yellow DT_NODELABEL(gpio_debug_led_yellow)

static void bt_receive_cb(struct bt_conn *conn, const uint8_t *const data, uint16_t len);

static const struct device *const i2c_a = DEVICE_DT_GET(DT_ALIAS(i2ca));
static const struct device *const i2c_b = DEVICE_DT_GET(DT_ALIAS(i2cb));
static const struct device *const uart_dev = DEVICE_DT_GET_ONE(zephyr_cdc_acm_uart);
static const struct device *const uart_gap = DEVICE_DT_GET(UART_GAP_NODE);
static const struct device *const led = DEVICE_DT_GET(LED_NODE);

// static const struct gpio_dt_spec gpio_led_debug_green = GPIO_DT_SPEC_GET(GPIO_NODE_debug_green, gpios);
// static const struct gpio_dt_spec gpio_led_debug_yellow = GPIO_DT_SPEC_GET(GPIO_NODE_debug_yellow, gpios);

/* Structure describing a color by its component values and name */
struct color_data {
  uint8_t r, g, b;
  const char *name;
};

/* The sequence of colors the RGB LED will display */
static const struct color_data color_sequence[] = {
    {0xFF, 0x00, 0x00, "Red"},   {0x00, 0xFF, 0x00, "Green"},  {0x00, 0x00, 0xFF, "Blue"},
    {0xFF, 0xFF, 0xFF, "White"}, {0xFF, 0xFF, 0x00, "Yellow"}, {0xFF, 0x00, 0xFF, "Purple"},
    {0x00, 0xFF, 0xFF, "Cyan"},  {0xF4, 0x79, 0x20, "Orange"},
};
// static const struct color_data color_green = {0x00, 0x55, 0x00, "Green"};
// static const struct color_data color_black = {0x00, 0x00, 0x00, "Black"};

static struct bt_nus_cb nus_cb = {
    .received = bt_receive_cb,
    .sent = NULL,
    .send_enabled = NULL,
};

static const uDeviceCfg_t gDeviceCfg = {.deviceType = U_DEVICE_TYPE_GNSS,
                                        .transportType = U_DEVICE_TRANSPORT_TYPE_I2C,
                                        .deviceCfg = {.cfgGnss =
                                                          {
                                                              .powerOffToBackup = true,
                                                              .moduleType = U_GNSS_MODULE_TYPE_M10,
                                                              .i2cAddress = U_GNSS_I2C_ADDRESS,
                                                          }},
                                        .transportCfg = {.cfgI2c = {
                                                             .i2c = 1,     // I2C B
                                                             .pinSda = -1, // Use -1 if on Zephyr or Linux
                                                             .pinScl = -1  // Use -1 if on Zephyr or Linux
                                                         }}};

#define UART_BUF_SIZE 128
#define UART_WAIT_FOR_RX 50000
#define UART_WAIT_FOR_BUF_DELAY K_MSEC(50)

// UART RX primary buffers
static struct k_work_delayable uart_gap_work;

static K_FIFO_DEFINE(fifo_uart_gap_rx_data);
static K_FIFO_DEFINE(fifo_uart_gap_tx_data);
static K_FIFO_DEFINE(fifo_uart_dev_rx_data);
static K_FIFO_DEFINE(fifo_uart_dev_tx_data);

static K_SEM_DEFINE(ble_init_ok, 0, 1);
struct uart_data_t {
  void *fifo_reserved;
  uint8_t data[UART_BUF_SIZE];
  uint16_t len;
};

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 500

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

static void show_led_pattern(const struct device *dev, const struct color_data *color, size_t size) {
  int ret = 0;
  for (size_t i = 0; i < size; i++) {
    ret = led_set_color(dev, 0, 3, &(color[i].r));
    if (ret) {
      LOG_ERR("Failed to set color on LED");
      return;
    }
    k_msleep(333);
  }
  led_set_color(dev, 0, 3, (uint8_t[]){0, 0, 0});
}

static void uart_dev_cb(const struct device *dev, void *user_data) {
  struct uart_data_t *buf = k_fifo_get(&fifo_uart_dev_tx_data, K_NO_WAIT);

  LOG_DBG("UART_DEV_CB");
  if (!uart_irq_update(dev)) {
    LOG_ERR("UART IRQ update failed");
    k_free(buf);
    return;
  }

  if (uart_irq_tx_ready(dev)) {
    uart_fifo_fill(dev, buf->data, buf->len);
    uart_irq_tx_disable(dev);
  }

  k_free(buf);
}

// WIESEP: Based on https://github.com/too1/ncs-uart-async-count-rx/blob/master/src%2Fmain.c
static void uart_gap_cb(const struct device *dev, struct uart_event *evt, void *user_data) {
  ARG_UNUSED(dev);
  ARG_UNUSED(user_data);

  static size_t aborted_len;
  struct uart_data_t *buf;
  static uint8_t *aborted_buf;
  static bool disable_req;

  switch (evt->type) {
  case UART_TX_DONE:
    LOG_DBG("[GAP] UART_TX_DONE");
    if ((evt->data.tx.len == 0) || (!evt->data.tx.buf)) {
      return;
    }

    if (aborted_buf) {
      buf = CONTAINER_OF(aborted_buf, struct uart_data_t, data[0]);
      aborted_buf = NULL;
      aborted_len = 0;
    } else {
      buf = CONTAINER_OF(evt->data.tx.buf, struct uart_data_t, data[0]);
    }

    k_free(buf);

    buf = k_fifo_get(&fifo_uart_gap_tx_data, K_NO_WAIT);
    if (!buf) {
      return;
    }

    if (uart_tx(uart_gap, buf->data, buf->len, SYS_FOREVER_MS)) {
      LOG_WRN("[GAP] UART_TX_DONE: Failed to send data over UART");
    }

    break;

  case UART_RX_RDY:
    LOG_DBG("[GAP] UART_RX_RDY");
    buf = CONTAINER_OF(evt->data.rx.buf, struct uart_data_t, data[0]);
    buf->len += evt->data.rx.len;

    if (disable_req) {
      LOG_DBG("[GAP] UART_RX_RDY: UART RX already disabled");
      return;
    }

    if ((evt->data.rx.buf[buf->len - 1] == '\n') || (evt->data.rx.buf[buf->len - 1] == '\r')) {
      LOG_DBG("[GAP] UART_RX_RDY: Disable UART RX");
      disable_req = true;
      uart_rx_disable(uart_gap);
    }

    break;

  case UART_RX_DISABLED:
    LOG_DBG("[GAP] UART_RX_DISABLED");
    disable_req = false;

    buf = k_malloc(sizeof(*buf));
    if (buf) {
      buf->len = 0;
    } else {
      LOG_WRN("[GAP] UART_RX_DISABLED: Not able to allocate UART receive buffer after disable");
      k_work_reschedule(&uart_gap_work, UART_WAIT_FOR_BUF_DELAY);
      return;
    }

    uart_rx_enable(uart_gap, buf->data, sizeof(buf->data), UART_WAIT_FOR_RX);

    break;

  case UART_RX_BUF_REQUEST:
    LOG_DBG("[GAP] UART_RX_BUF_REQUEST");
    buf = k_malloc(sizeof(*buf));
    if (buf) {
      buf->len = 0;
      uart_rx_buf_rsp(uart_gap, buf->data, sizeof(buf->data));
    } else {
      LOG_WRN("[GAP] UART_RX_BUF_REQUEST: Not able to allocate UART receive buffer for request");
    }

    break;

  case UART_RX_BUF_RELEASED:
    LOG_DBG("[GAP] UART_RX_BUF_RELEASED");
    buf = CONTAINER_OF(evt->data.rx_buf.buf, struct uart_data_t, data[0]);

    if (buf->len > 0) {
      k_fifo_put(&fifo_uart_gap_rx_data, buf);
    } else {
      LOG_DBG("[GAP] UART_RX_BUF_RELEASED: No data received");
      k_free(buf);
    }

    break;

  case UART_TX_ABORTED:
    LOG_DBG("[GAP] UART_TX_ABORTED");
    if (!aborted_buf) {
      aborted_buf = (uint8_t *)evt->data.tx.buf;
    }

    aborted_len += evt->data.tx.len;
    buf = CONTAINER_OF((void *)aborted_buf, struct uart_data_t, data);

    uart_tx(uart_gap, &buf->data[aborted_len], buf->len - aborted_len, SYS_FOREVER_MS);

    break;

  default:
    break;
  }
}

static bool is_usb_connected(void) {
  uint32_t dtr = 0;

  if (uart_line_ctrl_get(uart_dev, UART_LINE_CTRL_DTR, &dtr) == 0) {
    return dtr != 0; // Returns true if terminal is connected
  }

  return false; // If unable to get DTR, assume disconnected
}

static void uart_gap_work_handler(struct k_work *item) {
  struct uart_data_t *buf;

  LOG_DBG("[GAP] UART_GAP_WORK_HANDLER");

  buf = k_malloc(sizeof(*buf));
  if (buf) {
    buf->len = 0;
  } else {
    LOG_WRN("[GAP] Not able to allocate UART receive buffer in handler");
    k_work_reschedule(&uart_gap_work, UART_WAIT_FOR_BUF_DELAY);
    return;
  }

  uart_rx_enable(uart_gap, buf->data, sizeof(buf->data), UART_WAIT_FOR_RX);
}

void data_write_thread(void) {
  /* Don't go any further until BLE is initialized */
  k_sem_take(&ble_init_ok, K_FOREVER);

  for (;;) {
    /* Wait indefinitely for data to be sent over bluetooth */
    struct uart_data_t *buf = k_fifo_get(&fifo_uart_gap_rx_data, K_FOREVER);

    bt_nus_send(NULL, buf->data, buf->len);

    /* Check if the USB UART is connected */
    if (is_usb_connected()) {
      k_fifo_put(&fifo_uart_dev_tx_data, buf);
      uart_irq_tx_enable(uart_dev);
    } else {
      /* If not connected, free the buffer */
      k_free(buf);
    }
  }
}

static void bt_receive_cb(struct bt_conn *conn, const uint8_t *const data, uint16_t len) {
  char addr[BT_ADDR_LE_STR_LEN] = {0};

  bt_addr_le_to_str(bt_conn_get_dst(conn), addr, ARRAY_SIZE(addr));

  LOG_INF("Received data from: %s", addr);

  // Printf the received data
  LOG_INF("%.*s\n", len, data);
}

int main(void) {

  LOG_INIT();

  LOG_INF("YOLOv5 demo on %s", CONFIG_BOARD);
  LOG_DBG("Debug log level");

  /**************************************************************************/
  /*    Power Management                                                    */
  /**************************************************************************/
  // Initialize and start power management
  if (pwr_init()) {
    LOG_ERR("PWR Init failed!");
  }

  /**************************************************************************/
  /*    Waiting for devices to be ready                                     */
  /**************************************************************************/
  // Debug LED
  if (!device_is_ready(led)) {
    LOG_ERR("LED device not ready");
    return 0;
  }

  // nRF <-> USB UART
  if (!device_is_ready(uart_dev)) {
    LOG_ERR("CDC ACM device not ready");
    return 0;
  }

  // nRF <-> GAP UART
  if (!device_is_ready(uart_gap)) {
    LOG_ERR("GAP UART device not ready");
    return 0;
  }

  /**************************************************************************/
  /*    Communication Interfaces                                            */
  /**************************************************************************/
  if (usb_enable(NULL)) {
    LOG_ERR("USB enable failed");
    return 0;
  }
  LOG_INF("USB enabled");

  if (bt_nus_init(&nus_cb)) {
    LOG_ERR("Failed to initialize UART service");
    return 0;
  }
  LOG_INF("Bluetooth UART service initialized");

  k_msleep(100);

  if (start_bluetooth_adverts()) {
    LOG_ERR("Failed to start Bluetooth adverts");
    return 0;
  }
  LOG_INF("Bluetooth adverts started");

  k_sem_give(&ble_init_ok);

  k_work_init_delayable(&uart_gap_work, uart_gap_work_handler);

  if (uart_callback_set(uart_gap, uart_gap_cb, NULL)) {
    LOG_ERR("GAP UART callback configuration failed");
    return 0;
  }
  LOG_INF("GAP UART configured");

  if (uart_irq_callback_set(uart_dev, uart_dev_cb)) {
    LOG_ERR("CDC ACM UART callback configuration failed");
    return 0;
  }
  LOG_INF("CDC ACM UART configured");
  k_msleep(100);

  /**************************************************************************/
  /*    Initiate GNSS Module                                                */
  /**************************************************************************/

  int32_t errorCode = uPortInit();
  if (errorCode != 0) {
    LOG_ERR("Failed to initiate U-Blox library: %d", errorCode);
  } else {
    LOG_INF("Initalized U-Blox library");
  }

  errorCode = uPortI2cInit(); // You only need this if an I2C interface is used
  if (errorCode != 0) {
    LOG_ERR("Failed to initiate U-Blox I2C library: %d", errorCode);
  } else {
    LOG_INF("Initalized U-Blox I2C library");
  }

  errorCode = uDeviceInit();
  if (errorCode != 0) {
    LOG_ERR("Failed to initiate U-Blox library: %d", errorCode);
  } else {
    LOG_INF("Initalized U-Blox library");
  }

  /**************************************************************************/
  /*    Main Application Loop                                               */
  /**************************************************************************/

  // Start receiving data on the GAP UART
  struct uart_data_t *rx;
  rx = k_malloc(sizeof(*rx));
  uart_rx_enable(uart_gap, rx->data, sizeof(rx->data), UART_WAIT_FOR_RX);

  // Start the power management thread (also starts GAP9)
  pwr_start();

  show_led_pattern(led, color_sequence, ARRAY_SIZE(color_sequence));

  // Power down all the other non-power-gated sensors
  uint8_t error = 0;

  // BME688
  i2c_ctx_t bme688_i2c_ctx;
  bme688_i2c_ctx.i2c_handle = i2c_a;
  bme688_i2c_ctx.i2c_addr = 0x76;

  struct bme68x_dev bme688_ctx;
  bme688_ctx.write = bosch_i2c_write_reg;
  bme688_ctx.read = bosch_i2c_read_reg;
  bme688_ctx.delay_us = bosch_i2c_sleep_usec;
  bme688_ctx.intf_ptr = &bme688_i2c_ctx;

  error = bme68x_set_op_mode(BME68X_SLEEP_MODE, &bme688_ctx);
  if (error) {
    LOG_ERR("Error powering down BME688");
  }

  // ISM330DHCX
  i2c_ctx_t ism330dhcx_i2c_a;
  ism330dhcx_i2c_a.i2c_handle = i2c_a;
  ism330dhcx_i2c_a.i2c_addr = 0x6A;

  stmdev_ctx_t ism330dhcx_ctx;
  ism330dhcx_ctx.write_reg = st_i2c_write_reg;
  ism330dhcx_ctx.read_reg = st_i2c_read_reg;
  ism330dhcx_ctx.handle = &ism330dhcx_i2c_a;

  error = ism330dhcx_gy_data_rate_set(&ism330dhcx_ctx, ISM330DHCX_GY_ODR_OFF);
  if (error) {
    LOG_ERR("Error powering down ISM330DHCX gyroscope");
  }

  error = ism330dhcx_xl_data_rate_set(&ism330dhcx_ctx, ISM330DHCX_XL_ODR_OFF);
  if (error) {
    LOG_ERR("Error powering down ISM330DHCX accelerometer");
  }

  // ILPS28QSW
  i2c_ctx_t ilps28qsw_i2c_ctx;
  ilps28qsw_i2c_ctx.i2c_handle = i2c_b;
  ilps28qsw_i2c_ctx.i2c_addr = 0x5C;

  stmdev_ctx_t ilps28qsw_ctx;
  ilps28qsw_ctx.write_reg = st_i2c_write_reg;
  ilps28qsw_ctx.read_reg = st_i2c_read_reg;
  ilps28qsw_ctx.handle = &ilps28qsw_i2c_ctx;

  ilps28qsw_md_t md;
  md.odr = ILPS28QSW_ONE_SHOT;
  md.avg = ILPS28QSW_4_AVG;
  md.lpf = ILPS28QSW_LPF_DISABLE;
  md.fs = ILPS28QSW_1260hPa;
  error = ilps28qsw_mode_set(&ilps28qsw_ctx, &md);
  if (error) {
    LOG_ERR(" * Error powering down ILPS28QSW");
  }

  // BH1730FVC
  i2c_ctx_t i2c_ctx;
  i2c_ctx.i2c_handle = i2c_b;
  i2c_ctx.i2c_addr = BH1730_I2C_ADD;

  bh1730_t bh1730_ctx;
  bh1730_ctx.ctx.read_reg = st_i2c_read_reg;
  bh1730_ctx.ctx.write_reg = st_i2c_write_reg;
  bh1730_ctx.ctx.handle = &i2c_ctx;

  error = bh1730_power_down(&bh1730_ctx);
  if (error) {
    LOG_ERR(" * Error powering down BH1730FVC");
  }

  // MAX-M10S
  uDeviceHandle_t deviceHandle;
  LOG_INF("Initiating the module...");
  errorCode = uDeviceOpen(&gDeviceCfg, &deviceHandle);
  if (errorCode == 0) {

    // Init the GNSS module
    errorCode = uGnssInit(deviceHandle);
    if (errorCode == 0) {
      LOG_INF("GNSS module initiated successfully");
    } else {
      LOG_ERR("* Failed to initiate the module: %d", errorCode);
    }

    // Power off the GNSS module
    errorCode = uGnssPwrOff(deviceHandle);
    if (errorCode == 0) {
      LOG_INF("GNSS module powered off successfully");
    } else {
      LOG_ERR("* Failed to power off the module: %d", errorCode);
    }

    uDeviceClose(deviceHandle, true);
  } else {
    LOG_ERR("* Failed to initiate the module: %d", errorCode);
  }

  errorCode = uDeviceDeinit();
  if (errorCode != 0) {
    LOG_ERR("Failed to deinit U-Blox library: %d", errorCode);
  } else {
    LOG_INF("Deinitialized U-Blox library");
  }

  uPortI2cDeinit();
  uPortDeinit();

  while (1) {
    k_msleep(SLEEP_TIME_MS);
  }
  return 0;
}

K_THREAD_DEFINE(ble_write_thread_id, 512, data_write_thread, NULL, NULL, NULL, 7, 0, 0);
