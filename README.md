# Project Name

The T25 Emulator Piggy backs on the T25 i2c bus shared between
the temp/humidity sensor and the terminal board. The emulator is 
test and development tool to mock and simulate different sensor
and HVAC configurations. 

---

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Usage](#usage)

---

## Features

- Emulates SHT4x sensor for temperature and humidity control
- Emulates IO Expander for wire detection  
- Remote control of on/off wall through relay  
- Remote control of C-Wire power through relay
- Command console over serial
- Serial API for scripted control

---

## Getting Started

### Prerequisites

- CMake (version X.X or newer)  
- GCC
- Platform toolchain

### Building

---

## Usage
Flash the firwmare onto the device using the preferred method based on target. If using a serial 
connection to communicate with the emulator, you can power it from USB. Connect a USB-C cable to apply power and start the command console. The emulator will always boot into the Command Console. 

The board defaults to "On Wall" with C-Wire Power "Off"

### Command Console
The emulator will always boot into the command console. Use a terminal emulator like PuTTY or SmarTTY to send the commands below. The serial configuration is baud 115200, 8N1

#### Commands
|Command |Description|
|-------|------------|
|reset |Reset the emulator with a soft reset |
|version| Print the emulator firmware version |
|status |Print a status message |
|quiet |Turn off Host event printing |
|log | Turn on Host event printing |
|temp set <value> |Set the emulated temperature sensor value - Fahrenheith 1/10th degree |
|hum set <value> |Set the emulated humidity sensor value RH 1/10th Percent|
|cwire <value> |Set the C-Wire connect relay on (1) or off (0) |
|wall <value> |Set the On Wall status relay on (1) or off (0) |
|serial | Set the command mode to serial and close the console to use Serial API |

**status** - Status message will return the emulator parameters
```
$ status
Emulator - v1.0
Host: Connected | Disconnected
Temp: 72.0F
Hum: 40.0%
C-Wire: 0 | 1
Wall: 0 | 1
```