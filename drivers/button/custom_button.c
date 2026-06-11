/*
 * Copyright (c) 2026 IAR Systems AB
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT custom_button

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#include <app/drivers/custom_button.h>

bool button_is_pressed(const struct device *dev)
{
  const struct button_config *config = dev->config;
  return gpio_pin_get_dt(&config->gpio) > 0;
}

int button_init(const struct device *dev)
{
  int ret;
  const struct button_config *cfg = dev->config;

  if (!device_is_ready(cfg->gpio.port)) {
    printk("GPIO port not ready\n");
    return -ENODEV;
  }

  ret = gpio_pin_configure_dt(&cfg->gpio, GPIO_INPUT);
  if (ret < 0) {
    printk("custom_buttom: gpio_pin_configure_dt() failed: %d (%s)", ret,
           ret == -EINVAL ? "Invalid argument" :
           ret == -ENOTSUP ? "Not supported" :
           ret == -EIO ? "I/O error" : "Unknown");
    return ret;
  }
  
  /* TODO: configure interrupt, etc. */

  return 0;
}

DT_INST_FOREACH_STATUS_OKAY(BUTTON_DEFINE)
