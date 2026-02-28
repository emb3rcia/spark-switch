# Features

Features of spark-switch include:

- Management via WebUI
- Port parameter reporting to Home Assistant via MQTT
- 5 port Ethernet switching
- GbE speeds
- Powered by USB-C (5V 3A max)
- Open-Source
- RJ45 ports with integrated magnetics

## WebUI

As stated in [firmware section of docs](./Firmware.md), any part of it is not final, and docs for them will be provided with first proper firmware commit.

## Home Assistant reporting

See above.

## Power

spark-switch was designed with power via standard USB-C at 5V 2-3A power. It is ensured by using 2 5.1kOhm resistors at CC pins of USB-C port connected to ground. USB-C is the only supported and available option to power spark-switch