@defgroup    boards_adafruit-feather-nrf52840-express Adafruit Feather nRF52840 Express
@ingroup     boards
@brief       Support for the Adafruit Feather nRF52840 Express

### General information

The [Feather nRF52840 Express][feather-nrf52840] is a development board
from Adafruits Feather board family. It provides native USB support, Bluetooth
Low Energy and IEEE 802.15.4 support via the nRF52840 MCU.

<img src="https://cdn-learn.adafruit.com/assets/assets/000/068/578/medium800/circuitpython_Screenshot_2019-01-02_at_12.04.27.png"
     alt="top-down view on feather-nrf52840" width="50%"/>

[feather-nrf52840]: https://learn.adafruit.com/introducing-the-adafruit-nrf52840-feather/

### Flash the board

Flashing the Feather nRF52840 is described in the
common [Adafruit nRF52 Bootloader](@ref boards_common_adafruit-nrf52-bootloader) section.

Example with `hello-world` application:
```sh
make BOARD=adafruit-feather-nrf52840-express -C examples/basic/hello-world flash
```

### Terminal
To connect a terminal to the Feather, RIOT chooses `stdio_cdc_acm` per default.
This lets you access the Feather directly over USB.

You have several alternative possibilities to connect to the board.

1. With
   ~~~~~~~~~~~~~~~~~~~~~ {.mk}
   USEMODULE += stdio_uart
   ~~~~~~~~~~~~~~~~~~~~~
   and an FTDI adapter connected to the Feather's RX and TX ports you can use
   UART-based terminals to connect to the feather
2. With
   ~~~~~~~~~~~~~~~~~~~~~ {.mk}
   USEMODULE += stdio_rtt
   ~~~~~~~~~~~~~~~~~~~~~
   you can use the Segger J-Link Programmer as a serial interface to the device.
