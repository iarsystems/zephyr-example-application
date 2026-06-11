/*
 * Copyright (c) 2026 IAR Systems AB
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

/* size of stack area */
#define STACKSIZE 1024

/* scheduling priority */
#define PRIORITY 11

/* Define semaphores for synchronization */
K_SEM_DEFINE(led1_sem, 0, 1);
extern struct k_sem led2_sem;

void blink1(void)
{
  const struct device *blink;

  blink = DEVICE_DT_GET(DT_NODELABEL(blink1_led));
  if (!device_is_ready(blink)) {
    printk("Blink 1 LED not ready\n");
    return;
  }

  while (1) {
    k_sem_take(&led1_sem, K_FOREVER);
    
    blink_set_period_ms(blink, 200);
    
    k_sem_give(&led2_sem);
    
    k_msleep(400);
    
    blink_off(blink);
  }
}

/* Define thread at compile-time */
K_THREAD_DEFINE(blink1_id, STACKSIZE, blink1, NULL, NULL, NULL,	PRIORITY, 0, 0);
