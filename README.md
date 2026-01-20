# DS18B20 1-Wire example for RPi Pico and Pico 2

A simple example using my [pico_lib_onewire](https://github.com/mjcross/pico_lib_onewire) and [pico_lib_ds18b20](https://github.com/mjcross/pico_lib_ds18b20) libraries.

Creates a 1-Wire bus on gpio 15 (by default), scans for connected devices and displays the temperature readings.

## connecting devices
Despite the name a 1-Wire device generally needs three wires: `+3.3v`, `Gnd` and `Data`. On a cabled sensor these are normally respectively coloured red, black and yellow.

Multiple devices can share the bus by simply wiring them in parallel. Each device has a unique 64-bit ID that lets the master address it individually.

Note that the bus needs to be pulled up to +3.3v with an external resistor of about 4.7k. Don't rely on a GPIO pull-up to do this or you'll get poor noise immunity and limited speed on long lines.

Do not power the devices at more than 3.3v or you will damage the Pico gpio.

## building the example
The code is structured as a CMake project under VSCode. It's configured to build with the CMake Tools and RPi extensions, and to talk to a target device using a spare Pico as a SWD probe (see [PicoProbe](https://www.raspberrypi.com/documentation/microcontrollers/debug-probe.html)) which I'd highly recommend.