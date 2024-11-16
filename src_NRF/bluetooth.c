/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 * Copyright (c) 2020 Prevas A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>

#include <bluetooth/services/nsms.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main_bluetooth);

#include <zephyr/settings/settings.h>

static struct k_work advertise_work;

static uint8_t device_name[] = {'U', 'T', '0', '0', '0', '0', '0', '1'};

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, device_name, sizeof(device_name)),
};

static const struct bt_data sd[] = {
    BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_NSMS_VAL),
};

static void advertise(struct k_work *work) {
  int rc;

  bt_le_adv_stop();

  if (IS_ENABLED(CONFIG_SETTINGS)) {
    settings_load();
  }

  rc = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
  if (rc) {
    LOG_ERR("Advertising failed to start (rc %d)", rc);
    return;
  }

  LOG_INF("Advertising successfully started");
}

static void connected(struct bt_conn *conn, uint8_t err) {
  char addr[BT_ADDR_LE_STR_LEN] = {0};

  if (err) {
    LOG_ERR("Connection failed (err 0x%02x)", err);
  } else {
    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, ARRAY_SIZE(addr));
    LOG_INF("Connected to %s", addr);
  }
}

static void disconnected(struct bt_conn *conn, uint8_t reason) {
  char addr[BT_ADDR_LE_STR_LEN] = {0};
  bt_addr_le_to_str(bt_conn_get_dst(conn), addr, ARRAY_SIZE(addr));

  LOG_INF("Disconnected from %s (reason 0x%02x)", addr, reason);
  k_work_submit(&advertise_work);
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
};

static void bt_ready(int err) {
  if (err != 0) {
    LOG_ERR("Bluetooth failed to initialise: %d", err);
  } else {
    k_work_submit(&advertise_work);
  }
}

int start_bluetooth_adverts(void) {
  k_work_init(&advertise_work, advertise);
  return bt_enable(bt_ready);
}