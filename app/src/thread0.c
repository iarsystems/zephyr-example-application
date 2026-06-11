/*
 * Copyright (c) 2026 IAR Systems AB
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include <app/drivers/blink.h>

#include <app_version.h>

/* size of stack area */
#define STACKSIZE 1024

/* scheduling priority */
#define PRIORITY 11

/* Define semaphores for synchronization */
K_SEM_DEFINE(led0_sem, 1, 1);
extern struct k_sem led1_sem;

void blink0(void)
{
  const struct device *blink;

  printk("*** IAR Zephyr Example Application %s\n", APP_VERSION_STRING);

  blink = DEVICE_DT_GET(DT_NODELABEL(blink0_led));
  if (!device_is_ready(blink)) {
    printk("Blink 0 LED not ready\n");
    return;
  }

  /* Wait for initial token */
  k_sem_take(&led0_sem, K_FOREVER);

  while (1) {
    blink_set_period_ms(blink, 100);
    
    k_sem_give(&led1_sem);
    
    k_msleep(200);
    
    blink_off(blink);

    k_sem_take(&led0_sem, K_FOREVER);
  }
}

/* Define thread at compile-time */
K_THREAD_DEFINE(blink0_id, STACKSIZE, blink0, NULL, NULL, NULL,	PRIORITY, 0, 0);
