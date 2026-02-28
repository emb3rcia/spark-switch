# Hardware

## Parts

- STM32F469BET6 as management microcontroller
- KSZ9477STXI as switch IC
- Bel Fuse 0826-1G1T-23-F as RJ45 ports
- ADP2116AACPZ-R7 as 2.5V and 1.2V Buck voltage converter
- TLV76733DRVR as 3.3V LDO voltage converter

## Generic parts

There are many parts that wasn't listed above because they are too general to give specific part number. These parts include but are not limited to capacitors, inductors or resistors. For full part list needed, look into Basket of Materials either at the end of [main README.md](../README.md) or in [BOM.csv](../BOM.csv) and match individual part parameters to part of your choice.

## PCB

spark-switch uses standard 6 layer 1.6mm FR4 PCB. Stackup is JLCPCB's JLC06161H-3313.

## Hand-soldering possibility

Although most parts are chosen with hand soldering in mind (eg most passives being 0603 size), there are components with exposed pads that are impossible to solder with only soldering iron. If you want to chose hand soldering while replicating this project, consider using hot air or reflow oven for these components, or if you are unable to, consider choosing PCB Assembly for them.