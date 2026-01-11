# Reaction Timer

Embedded Linux reaction time measurement application for BeagleY-AI using SPI-based joystick input and LED feedback.

## Overview

Embedded C application for measuring human reaction time using an analog joystick. Demonstrates SPI-based peripheral interaction, timing measurement using Linux system calls, and modular hardware abstraction on an embedded Linux platform.

## Features

- **Timing measurement:** Millisecond-resolution timing using `clock_gettime()`
- **SPI communication:** Polling-based joystick input via external ADC
- **LED feedback:** Visual prompts and results using dual-color LED (red/green)
- **Input validation:** Software filtering to ensure reliable joystick detection
- **Modular HAL:** Separate joystick and LED abstraction layers

## Hardware Requirements

- **Platform:** BeagleY-AI
- **Input:** Analog joystick (via SPI-connected ADC)
  - VRx → Channel 0
  - VRy → Channel 1
- **Output:** Dual-color LED (red/green)

## Game Flow

1. Display welcome message and instructions  
2. Flash LEDs (green/red, 4 cycles)  
3. Verify joystick is released  
4. Wait random delay (0.5s–3.0s)  
5. Prompt direction (up/down)  
6. Measure response time (5s timeout)  
7. Display result:
   - **Correct:** Show reaction time, update best time, flash green
   - **Incorrect:** Flash red
   - **Quit:** Press joystick left or right


## Building

### Cross-Compile for Target

```bash
./buildTarget.sh
```

**Or manually:**

```bash
rm -rf build/
cmake -S . -B build \
  -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc \
  -DCMAKE_CXX_COMPILER=aarch64-linux-gnu-g++
cmake --build build
```

### Host Build (Testing)

```bash
./buildHost.sh
```

## Deployment

```bash
# Copy to target
scp build/app/reaction_timer root@<target-ip>:/root/

# Run on target
ssh root@<target-ip>
cd /root
./reaction_timer
```

## Project Structure

```
.
├── app/              # Main application
├── hal/              # Hardware Abstraction Layer
│   ├── include/      # HAL headers
│   └── src/          # HAL implementations
├── buildHost.sh      # Host build script
└── buildTarget.sh    # Cross-compilation script
```

## Technical Details

- **Language:** C
- **Build System:** CMake
- **Target Architecture:** ARM Cortex-A53 (aarch64)
- **Timing Resolution:** Milliseconds
- **Input Handling:** Polling-based SPI with analog joystick
