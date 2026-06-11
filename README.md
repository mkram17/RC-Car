# RC Car — Receiver

This directory contains the firmware and documentation for the RC car receiver module.
## Overview

The receiver reads radio (or other transport) commands and translates them into motor and steering outputs. It's implemented for an embedded board using PlatformIO.

## Hardware

- Arduino Nano, Nano Every
- Power supply: 7.4V battery
- Motor driver: L298N
- RC transceivers: NRF24L01
- Steering servo

## Software

This project uses PlatformIO. There are two environments: one for the receiver, and one for the transmitter.

MIT License.