# Improved OneWire and ds18b20 'C' libraries for the RPi Pico and Pico 2

An updated version of my libraries for Maxim's popular *OneWire* protocol and the *ds18b20* digital temperature sensor.

The libraries keep the original PIO code but have cleaner packaging that should make them easier to use in a project.

A demonstration program is included to scan the bus for connected devices and display temperature readings.

## connecting devices
Despite the name the OneWire bus generally has three wires: `+3.3v`, `Gnd` and `Data`, with the data line pulled up to +3.3v by a (single) resistor of about 4.7k.

> Note: do not rely on a GPIO pull-up resistor to pull up the bus as the value is much too high resulting in poor noise immunity and limited speed on long lines.

Sensors are simply wired in parallel, with 20 or more devices on the same bus being perfectly possible.

Although the bus can in theory operate with just two wires (phantom power) this is less useful with active sensors like the ds18b20.

Do NOT power the bus at more than 3.3v or you will damage the Pico GPIO.

## using the libraries in your own code
All you need to do is:
1. copy the `lib_onewire` and `lib_ds18b20` folders into your project
2. add `add_subdirectory()` and `target_link_libraries()` lines to your top level `CMakeLists.txt` or equivalent
3. include `onewire.h` and `ds18b20.h` in your source file.

Note that `lib_onewire` can be used standalone if required.