# spark-switch

![spark-switch](Images/3D/Main-View.png)

## What is it

spark-switch is my own open-source 5 port GbE managed Ethernet switch.

## Why i made it

I made this project because I love tinkering and wanted to use my need for an Ethernet switch as a way to teach myself differential pair routing. And it worked! I learned a lot!

## What i learned

I learned:
- How to properly route differential pairs
- How to properly length tune traces
- How to create more readable schematics
- How to properly manage the GND plane 
- How to work with high speed interfaces

# Design decisions

- 100 Ohm differential controlled impedance for Ethernet traces
- 50 Ohm single ended controlled impedance for RMII and SPI
- Solid GND planes as reference
- 2 power planes, one split one solid
- FR4, 1.6mm thickness
- Via-In-Pad using JLCPCB's free Plated-Over Filled Via technology

# Directory overview

- Firmware project is available in `/Firmware`
- 3D case files as well as Fusion360 project files are available in `/3D`
- EasyEda Pro project files are available in `/PCB`
- Images are available in `/Images`
- Schematic PDF is available in `/Schematic`
- BOM is available in `/BOM.csv` and at the end of README
- Gerber files are available in `/Gerbers`

# Parts used

- STM32F469BET6 as management microcontroller
- KSZ9477STXI as switch IC
- Bel Fuse 0826-1G1T-23-F as RJ45 port
- ADP2116AACPZ-R7 as 2.5V and 1.2V Buck voltage converter
- TLV76733DRVR as 3.3V LDO voltage converter

# Tools used

- EasyEda Pro for EDA work
- Fusion360 Educational for 3D work
- STM32CubeMX and STM32CubeIDE for firmware

# Features

- Management via WebUI
- Port parameter reporting to Home Assistant via MQTT
- 5 port Ethernet switching
- GbE speeds
- Powered by USB-C (5V 3A max)
- Open-Source
- RJ45 ports with integrated magnetics

# Images

## 2D

<details>
<summary>Click to expand 2D view images</summary>

Top view

![Top view](Images/2D/Top-View.png)

Bottom view

![Top view](Images/2D/Bottom-View.png)

</details>

## 3D

<details>
<summary>Click to expand 3D view images</summary>

EasyEda Pro 3D viewer

![EasyEda Pro 3D viewer](Images/3D/Main-View.png)

</details>

## Gerber files

<details>
<summary>Click to expand Gerber images</summary>

Top layer view

![Top layer view](Images/Gerbers/Top-Layer-View.png)

Bottom layer view

![Bottom layer view](Images/Gerbers/Bottom-Layer-View.png)

Layer 1 / Top layer / Signal

![Layer 1 / Top layer / Signal](Images/Gerbers/Layer-1.png)

Layer 2 / Inner 1 / Solid GND plane

![Layer 2 / Inner 1 / Solid GND plane](Images/Gerbers/Layer-2.png)

Layer 3 / Inner 2 / 2.5 and 3.3V split power plane

![Layer 3 / Inner 2 / 2.5 and 3.3V split power plane](Images/Gerbers/Layer-3.png)

Layer 4 / Inner 3 / Solid 1.2V power plane

![Layer 4 / Inner 3 / Solid 1.2V power plane](Images/Gerbers/Layer-4.png)

Layer 5 / Inner 4 / Solid GND plane

![Layer 5 / Inner 4 / Solid GND plane](Images/Gerbers/Layer-5.png)

Layer 6 / Bottom layer / Signal

![Layer 6 / Bottom layer / Signal](Images/Gerbers/Layer-6.png)

</details>

# License

## PCB / Schematic License

All files in `/PCB`, `/Schematic` and `/Gerbers` folders are licensed under the CERN Open Hardware License v2 (Weakly Reciprocal).

See `/Licenses/CERN-OHL.txt` for full terms.

## Software License

All files in `/Firmware` folder are licensed under the Apache 2.0 License.

See `/Licenses/Apache-2.0.txt` for full terms.

## 3D files and images

All files in `/3D` and `/Images` folders are licensed under the CC-BY 4.0 License.

See `/Licenses/CC-BY-4.0.txt` for full terms

# BOM

|No.|Quantity|Comment              |Value |Manufacturer Part    |Manufacturer          |Supplier Part     |Supplier|Price                  |Ordered|Why more/less       |Link                                                                                                         |
|---|--------|---------------------|------|---------------------|----------------------|------------------|--------|-----------------------|-------|--------------------|-------------------------------------------------------------------------------------------------------------|
|1  |1       |2.2uH                |2.2uH |APH0530T2R2M         |APV                   |C5349681          |LCSC    |$0.41                  |5      |Minimal order is 5  |https://www.lcsc.com/product-detail/C5349681.html                                                            |
|2  |1       |3.3uH                |3.3uH |FEXL0530A-3R3M       |cjiang                |C5378512          |LCSC    |$1.12                  |1      |N/A                 |https://www.lcsc.com/product-detail/C5378512.html                                                            |
|3  |1       |4.7kΩ                |4.7kΩ |RC0603FR-074K7L      |YAGEO                 |C99782            |LCSC    |$0.13                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C99782.html                                                              |
|4  |1       |4.7uF                |4.7uF |CL10A475KA8NQNC      |SAMSUNG               |C69335            |LCSC    |$0.16                  |10     |Minimal order is 10 |https://www.lcsc.com/product-detail/C69335.html                                                              |
|5  |1       |6.04kΩ               |6.04kΩ|0603WAF6041T5E       |UNI-ROYAL             |C25977            |LCSC    |$0.13                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C25977.html                                                              |
|6  |1       |8.2kΩ                |8.2kΩ |RC0603FR-078K2L      |YAGEO                 |C114637           |LCSC    |$0.15                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C114637.html                                                             |
|7  |1       |10uF                 |10uF  |CL10A106MA8NRNC      |SAMSUNG               |C96446            |LCSC    |$0.34                  |20     |Minimal order is 20 |https://www.lcsc.com/product-detail/C96446.html                                                              |
|8  |1       |10Ω                  |10Ω   |FRC0603J100 TS       |FOJAN                 |C2907091          |LCSC    |$0.10                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C2907091.html                                                            |
|9  |1       |22uF                 |22uF  |CL32B226KAJNNNE      |SAMSUNG               |C309062           |LCSC    |$0.13                  |1      |N/A                 |https://www.lcsc.com/product-detail/C309062.html                                                             |
|10 |1       |27kΩ                 |27kΩ  |RC0603FR-0727KL      |YAGEO                 |C114614           |LCSC    |$0.15                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C114614.html                                                             |
|11 |1       |100nF                |100nF |C3225C0G1H104JT000N  |TDK                   |C338021           |LCSC    |$0.56                  |1      |N/A                 |https://www.lcsc.com/product-detail/C338021.html                                                             |
|12 |1       |191Ω                 |191Ω  |RMC06031911%N        |Tyohm                 |C269413           |LCSC    |$0.31                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C269413.html                                                             |
|13 |1       |ADP2116ACPZ-R7       |      |ADP2116ACPZ-R7       |ADI                   |C659049           |LCSC    |$3.36                  |1      |N/A                 |https://www.lcsc.com/product-detail/C659049.html                                                             |
|14 |1       |KSZ9477STXI-TR       |      |KSZ9477STXI-TR       |MICROCHIP             |C631685           |LCSC    |$20.08                 |1      |N/A                 |https://www.lcsc.com/product-detail/C631685.html                                                             |
|15 |1       |RCLAMP0502BATCT      |      |RCLAMP0502BATCT      |SEMTECH               |C117553           |LCSC    |$1.13                  |5      |Minimal order is 5  |https://www.lcsc.com/product-detail/C117553.html                                                             |
|16 |1       |SMA6L5.0A            |      |SMA6L5.0A            |Littelfuse            |C1974860          |LCSC    |$0.79                  |1      |N/A                 |https://www.lcsc.com/product-detail/C1974860.html                                                            |
|17 |1       |STM32F469BET6        |      |STM32F469BET6        |ST                    |C1342980          |LCSC    |$18.73                 |1      |N/A                 |https://www.lcsc.com/product-detail/C1342980.html                                                            |
|18 |1       |TLV76733DRVR         |      |TLV76733DRVR         |TI                    |C2848334          |LCSC    |$0.98                  |5      |Minimal order is 5  |https://www.lcsc.com/product-detail/C2848334.html                                                            |
|19 |1       |TS6643TP 250gf 009   |      |TS6643TP 250gf 009   |SHOU HAN              |C5342967          |LCSC    |N/A                    |0      |I already have them |https://www.lcsc.com/product-detail/C5342967.html                                                            |
|20 |1       |TYPE-C 16PIN 2MD(073)|      |TYPE-C 16PIN 2MD(073)|SHOU HAN              |C2765186          |LCSC    |N/A                    |0      |I already have them |https://www.lcsc.com/product-detail/C2765186.html                                                            |
|21 |2       |1kΩ                  |1kΩ   |FRC0603F1001TS       |FOJAN                 |C2907002          |LCSC    |$0.12                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C2907002.html                                                            |
|22 |2       |1nF                  |1nF   |1808B102K302NT       |FH                    |C967608           |LCSC    |$0.70                  |10     |Minimal order is 10 |https://www.lcsc.com/product-detail/C967608.html                                                             |
|23 |2       |2.2uF                |2.2uF |CGA0603X5R225K250JT  |HRE                   |C6119859          |LCSC    |$0.80                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C6119859.html                                                            |
|24 |2       |5.1kΩ                |5.1kΩ |FRC0603F5101TS       |FOJAN                 |C2907044          |LCSC    |$0.12                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C2907044.html                                                            |
|25 |2       |25MHz                |25MHz |SX1M25.000M10F30TNN  |SCTF                  |C2901612          |LCSC    |$0.57                  |1      |N/A                 |https://www.lcsc.com/product-detail/C2901612.html                                                            |
|26 |2       |30kΩ                 |30kΩ  |FRC0603F3002TS       |FOJAN                 |C2907025          |LCSC    |$0.12                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C2907025.html                                                            |
|27 |2       |47uF                 |47uF  |CS3225X7R476K100NRL  |SAMWHA                |C5189825          |LCSC    |$0.45                  |5      |Minimal order is 5  |https://www.lcsc.com/product-detail/C5189825.html                                                            |
|28 |2       |820pF                |820pF |CC0603JRNPO8BN821    |YAGEO                 |C519398           |LCSC    |$0.42                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C519398.html                                                             |
|29 |3       |22uF                 |22uF  |GRM188C61E226ME01D   |muRata                |C29519229         |LCSC    |$0.92                  |5      |Minimal order is 5  |https://www.lcsc.com/product-detail/C29519229.html                                                           |
|30 |4       |10nF                 |10nF  |CC0603JRNPO8BN103    |YAGEO                 |C723749           |LCSC    |$0.81                  |50     |Minimal order is 50 |https://www.lcsc.com/product-detail/C723749.html                                                             |
|31 |5       |0826-1G1T-23-F       |      |0826-1G1T-23-F       |Bel Magnetic Solutions|530-0826-1G1T-23-F|Mouser  |$36.75                 |5      |N/A                 |https://www.mouser.pl/ProductDetail/Bel-Magnetic-Solutions/0826-1G1T-23-F?qs=SRYZG9HaIQ0yqJ%252BCqOsSRg%3D%3D|
|32 |6       |1uF                  |1uF   |CL10B105KB8NQNC      |SAMSUNG               |C5199872          |LCSC    |$0.42                  |50     |Minimal order is 50 |https://www.lcsc.com/product-detail/C5199872.html                                                            |
|33 |10      |33Ω                  |33Ω   |FRC0603F33R0TS       |FOJAN                 |C2909394          |LCSC    |$0.12                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C2909394.html                                                            |
|34 |16      |10kΩ                 |10kΩ  |RC0603FR-0710KL      |YAGEO                 |C98220            |LCSC    |$0.13                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C98220.html                                                              |
|35 |73      |100nF                |100nF |CL10B104KA8NNNC      |SAMSUNG               |C1590             |LCSC    |$0.36                  |100    |Minimal order is 100|https://www.lcsc.com/product-detail/C1590.html                                                               |
|36 |        |PCB                  |      |                     |                      |                  |JLCPCB  |$45.90 + $7.90 shipping|5      |Minimal order is 5  |https://www.jlcpcb.com                                                                                       |
|   |        |                     |      |                     |                      |                  |Total   |$145.37                |       |                    |                                                                                                             |




© 2026 emb3rcia

Firmware: Apache 2.0
Hardware: CERN OHL v2
3D & Images: CC BY 4.0
