/*
 * Copyright (c) 2026 IAR Systems AB
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include <app/drivers/blink.h>

/* size of stack area */
#define STACKSIZE 1024

/* scheduling priority */
#define PRIORITY 11

/* Define semaphores for synchronization */
K_SEM_DEFINE(led2_sem, 0, 1);
extern struct k_sem led3_sem;

void blink2(void)
{
  const struct device *blink;

  blink = DEVICE_DT_GET(DT_NODELABEL(blink2_led));
  if (!device_is_ready(blink)) {
    printk("Blink 2 LED not ready\n");
    return;
  }

  while (1) {
    k_sem_take(&led2_sem, K_FOREVER);
    
    blink_set_period_ms(blink, 400);
    
    k_sem_give(&led3_sem);
    
    k_msleep(800);
    
    blink_off(blink);
  }
}

/* Define thread at compile-time */
K_THREAD_DEFINE(blink2_id, STACKSIZE, blink2, NULL, NULL, NULL,	PRIORITY, 0, 0);
