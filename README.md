# RC Car

This directory contains the firmware and documentation for the RC car I made during the summer of 2026. It took me ~3 weeks, and gave me experience with electrical circuits, arduino, C++, and CAD/3D printing. I also learned how to use RF transceivers, a multimeter, potentiometers, a L298N motor controller, Arduino Nano/Nano Every, and Fusion.

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
