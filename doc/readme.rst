.. _Zephyr Semaphores:
  https://docs.zephyrproject.org/latest/kernel/services/synchronization/semaphores.html

.. _IAR STM32F429II-ACA:
  https://docs.zephyrproject.org/latest/boards/iar/stm32f429ii_aca/doc/index.html


Overview
========

This example demonstrates spawning multiple threads using
:c:func:`K_THREAD_DEFINE`. It spawns up to five threads.
Each thread is then defined at compile time using K_THREAD_DEFINE.

The first four threads control an LED using a custom driver named blink.

- ``blink0()`` controls ``blink0_led`` and has a 100ms sleep cycle
- ``blink1()`` controls ``blink1_led`` and has a 200ms sleep cycle
- ``blink2()`` controls ``blink2_led`` and has a 300ms sleep cycle
- ``blink3()`` controls ``blink3_led`` and has a 400ms sleep cycle

Each thread relies on the use of `Zephyr Semaphores`_ for proper thread synichronization.

Note that a multi-threaded application does not strictly require a ``main()`` function.

The last thread controls a button using a custom driver named custom_button.

- ``button()`` controls ``custom_button_0``

The button thread uses :c:func:`printk()` to print a message when the button is pushed.

.. code-block:: none

  Button was pressed


Requirements
============

The IAR Zephyr application example was designed to run with the `IAR STM32F429II-ACA`_ board
using a custom Device Tree specification, hence the default board is named ``custom_aca``.

Alternatively, a overlay can be created for supported Zephyr boards
under ``app/boards``. The board must have two or more LEDs and
one button connected via GPIO pins.

