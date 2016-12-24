# Project Name
Security System 

# Overview
This system was implemented in the Programming discipline for embedded systems, where I used U-boot, Debian and the generated filesystem and compiler for me. The final grade of the project was 10.

## Demostration
https://www.youtube.com/watch?v=d9hHizWa5LY

## Platform
Beaglebone

## Architecture
Debian 32 bits (Embedded Linux)

## Compilation
- make
- note: The makefile is programmed to compile on the pc (x86) and send the binary to the linux root directory.

## Usage
- Connect the components according to the mapping of the GPIOs that are in the headers (.h) files.
- Run the binary (app.bin)

## Components
- Sensor IR
- LEDs
- Buzzers
- Keyboard 4x3
- BCD 7 segments decoder
- Display 7 segments
