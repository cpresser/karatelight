# Karatelight
This repository contains firmware and Hardware design files for the Karatelight 8/16 channel RGB LED Dimmer.

# Firmware
`karate_xc8.X` and `karate_v2.X` contain the firmware for the device
* both are *MPLAB X* projects. I used version 1.41 to work with them, but any newer version should work as well.
* `karate_xc8.X` can be build with microchips XC8 compiler
* `karate_v2.X` requires the MCC18 compiler
* You might want to adjust the USB VID/PID when building this
* The code is based on microchip examples, so for most part of it the microchip licence applies. Those files have a intact microchip header-
* All other files are GPL v2. see gpl-2.0.txt
* Most files are encoded iso8859-1, some might be utf-8

`fsUSB_Bootloader` contains a bootloader for the device. Its software from microchip, just slightly adjusted to the hardware (Fuses, Switch).

# Hardware
* The Hardware is licensed CERN OHL version 1.2
* Both the base-board and the extension-board are included
* The files were created using Cadsoft Eagle 6.3.
* Only the latest revision (v06b) of the board is in this repository. If you need the files for a previous version, please contact me.
* The files `20150310_KarateLight_Haka.zip` and `20150310_KarateLight-Exp_Haka.zip` were used for board production
* The folder `stencil` contains files used to create a stencil and stencil holder with a laser-cutter.
* There is a BOM with links to reichelt, digikey and mouser article numbers. Prices are most likely outdated.

# Software
The device can be used with various software packages. Some of them are
* https://github.com/durchflieger/DFAtmo
* https://github.com/OpenLightingProject/ola/
* https://github.com/einmalacht/enigmalight/
* atmolightd-plugin for Engima2 based set-top boxes
* AtmoWin