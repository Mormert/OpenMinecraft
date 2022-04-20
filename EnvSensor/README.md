# Sensors with a Raspberry Pi
This program is intended to be compiled to a Raspberry Pi with humidity and light sensors to control the Open MC weather and light conditions in the game.

## I2C Interface

Requires that I2C interface is enabled on the Raspberry Pi. Enable it with:

```shell
sudo raspi-config
```
Then reboot the Pi.

## Building

```shell
mkdir build
cd build
cmake ..
make
```