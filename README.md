# RC Car

This directory contains the firmware and documentation for the RC car I made during the summer of 2026. It took me ~3 weeks, and gave me experience with electrical circuits, arduino, C++, and CAD/3D printing. I also learned how to use RF transceivers, a multimeter, potentiometers, a L298N motor controller, Arduino Nano/Nano Every, and Onshape.

View the RC-Car 3D model (built from scratch) [here](https://cad.onshape.com/documents/14f4c05381c16e5d3cf9bb65/w/5f351b796ca8465bb66016a6/e/6116eee2b8025bf458342d0c?renderMode=0&uiState=6a2b19d5a9192702fd2c6038)

## Overview

The transmitter sends info about joystick position. The receiver reads radio commands and translates them into motor and steering outputs.

## Hardware

- Arduino Nano, Nano Every
- Power supply: 7.4V battery
- Motor driver: L298N
- RC transceivers: NRF24L01
- Steering servo

## Software

This project uses PlatformIO. There are two environments: one for the receiver, and one for the transmitter.

MIT License.
