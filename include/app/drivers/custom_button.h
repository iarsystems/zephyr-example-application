/*
 * Copyright (c) 2026 IAR Systems AB
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
  
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

struct button_config {
  struct gpio_dt_spec gpio;
};

int button_init(const struct device *dev);

bool button_is_pressed(const struct device *dev);

#define BUTTON_DEFINE(inst)                                                    \
  static const struct button_config button_cfg_##inst = {                      \
    .gpio = GPIO_DT_SPEC_GET(DT_INST(inst, custom_button), gpios),             \
  };                                                                           \
                                                                               \
  DEVICE_DT_INST_DEFINE(inst,                                                  \
                        button_init,                                           \
                        NULL,                                                  \
                        NULL,                                                  \
                        &button_cfg_##inst,                                    \
                        POST_KERNEL,                                           \
                        CONFIG_BUTTON_INIT_PRIORITY,                           \
                        NULL);

#define DT_DRV_COMPAT custom_button
