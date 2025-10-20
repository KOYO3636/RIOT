<!--
SPDX-FileCopyrightText: 2013 Freie Universität Berlin
SPDX-License-Identifier: LGPL-2.1-only
-->

@defgroup   cpu CPU
@brief      CPU specific implementations

This module contains all CPU specific source files. In case of multiple CPUs
sharing the same architecture, the implementation is split into several CPU
specific parts and an architecture part (e.g. arm7_common and lpc23xx).

@defgroup   config_cpu CPU Configurations
@ingroup    config
@brief      Compile time configurations for different kinds of CPU.

@brief  Skip calling `board_init()`

Don't call `board_init()`, leave all pins in their default state.

This is intended to be used with basic riotboot_slot which does not interact
with any external hardware.

@experimental    Only use this if you know what you are doing

    #define DISABLE_BOARD_INIT  0

@brief  Skip calling `cpu_init()`

Don't call `cpu_init()`, leave all CPU configuration in boot-up state.

This is intended to be used with basic riotboot_slot which does not interact
with any CPU peripherals.

@experimental   Only use this if you know what you are doing

    #define DISABLE_CPU_INIT    0
