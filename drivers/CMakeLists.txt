# Copyright (c) 2026 IAR Systems AB
# SPDX-License-Identifier: Apache-2.0

# Out-of-tree drivers for custom classes
add_subdirectory_ifdef(CONFIG_BLINK blink)
add_subdirectory_ifdef(CONFIG_BUTTON button)
