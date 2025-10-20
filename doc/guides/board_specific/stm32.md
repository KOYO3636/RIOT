---
title: STM32 Flashing
description: Guide on how to flash STM32 boards
---

## General

The Nucleos often ship with very old ST-Link Firmware.
If the flash operation fails for some reason, it is possible that
the embedded ST-Link firmware is either too old or has bugs that have been
fixed in the meantime. You can find updates for the ST-Link on
[this STM webpage](https://www.st.com/en/development-tools/stsw-link007.html).
You can also use the `STM32CubeProgrammer` software to update the firmware.

## Flashing the Board Using OpenOCD

The ST Nucleo32, 64 and 144 boards include an on-board ST-LINK programmer
and can be flashed using OpenOCD (use version 0.11.0 at least).
OpenOCD is the standard programmer for all Nucleo boards, so no explicit
`PROGRAMMER` environment variable has to be set.

To flash this board, just use the following command (replace the `xxxxx`
with your Nucleo variant):

```shell
make BOARD=nucleo-xxxxx flash -C examples/basic/hello-world
```

If your board does not have OpenOCD set as the default programmer, you can
select it by explicitly setting the `PROGRAMMER` variable:

```shell
make BOARD=xxxxx PROGARMMER=openocd flash
```

:::note
The OpenOCD release cycle is quite slow and newly released chips might not be
supported by the latest release. For example the STM32C0 series is not yet
supported by OpenOCD 0.12.0, resulting in the following error message:
`Warn : Cannot identify target as an STM32G0/G4/L4/L4+/L5/U5/WB/WL family device.`.

Furthermore, some distributions ship even older versions, which might not have
support for new devices or for the ST-Link V3 that is built-in on new
generation Nucleos, resulting in a diffuse LibUSB error message such as this:
`Error: libusb_open() failed with LIBUSB_ERROR_ACCESS`.
If you have a recent OpenOCD version, you can check if your user is
in the `dialout` and/or `plugdev` group and therefore has the appropriate
access rights.

In either of the first two cases you have to compile the latest OpenOCD
sources for your system and manually update the
`/etc/udev/rules.d/60-openocd.rules` file with the
file provided in the `contrib` subfolder of the OpenOCD repository.
Please refer to the OpenOCD documentation for further information.
:::

## Flashing the Board Using the ST-LINK Mass Storage Device

:::note
This method does not (easily) work with WSL, as the standard kernel provided
does not support Mass Storage Devices. While you can access the MSD through
e.g. `/mnt/d/` if the ST-Link is mounted under Windows, you can not use the
VCP (Virtual COM Port) via `usbipd` inside of WSL at the same time.
:::

The on-board ST-Link programmer found on all Nucleo32, 64 and 144 boards
will show up as a mass storage device when plugged in via USB.
Copying a HEX file to the mass storage device will trigger the flashing
sequence of the ST-Link. This can either be done manually or with the
`cpy2remed` (copy to removable media) PROGRAMMER script. To use this programmer,
you can use the following command:

```shell
make BOARD=nucleo-xxxx PROGRAMMER=cpy2remed flash
```

## Flashing the Board using stm32flash

It is possible to automatically boot the STM32 board into the in-ROM bootloader
that `stm32flash` communicates with for flashing by connecting the RST pin to
DTR and the BOOT pin (or BOOT0 for STM32 MCU families with BOOT0 and BOOT1 pins)
to RTS of the TTL adapter. In addition, set `STM32FLASH_RESET` to `1` via
environment or command line to actually issue a reset with BOOT (or BOOT0)
pulled high prior flashing to enter the bootloader, and a second reset with BOOT
(or BOOT0) pulled low to reboot into the application. `STM32FLASH_RESET`
defaults to `0` as of know, as with `PROGRAMMER=stm32flash STM32FLASH_RESET=1`
additional terminal flags are set, so that `make term` doesn't accidentally
keep the reset signal pulled low or boots the board into the bootloader.

```shell
make BOARD=xxxx PROGRAMMER=stm32flash STM32FLASH_RESET=1 flash
```

The TTL adapter this was tested with had inverted RTS and DTR signal. By setting
`STM32FLASH_RESET_INVERT` to `1` RIOT will assume RTS and DTR signals to be
inverted, by setting it to `0` non-inverted signals will be generated. As of
now, `STM32FLASH_RESET_INVERT` is by default `1`. This may change if it
becomes evident that non-inverted TTL adapters are in fact more common than
inverted adapters.
