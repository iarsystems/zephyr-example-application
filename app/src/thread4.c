/*
 * Copyright (c) 2026 IAR Systems AB
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include <app/drivers/custom_button.h>

/* size of stack area */
#define STACKSIZE 1024

/* scheduling priority */
#define PRIORITY 10

void button(void)
{
  const struct device *button;
    
  button = DEVICE_DT_GET(DT_NODELABEL(custom_button_0));
  if (!device_is_ready(button)) {
    printk("Button device not ready\n");
    return;
  }

  while(1) {
    if (button_is_pressed(button)) {
      printk("Button was pressed.\n");
    }

    k_msleep(200);
  }
}

/* Define thread at compile-time */
K_THREAD_DEFINE(button_id, STACKSIZE, button, NULL, NULL, NULL,	PRIORITY, 0, 0);
