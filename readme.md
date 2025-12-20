# Reaction Timer

Bare-metal reaction time measurement application for BeagleY-AI with hardware timer and SPI-based input handling.

## Overview

Embedded C application for measuring human reaction time using joystick input. Demonstrates low-level hardware control, timing precision, and resource-constrained programming on ARM Cortex-A53.

## Features

- **Hardware timer integration:** Millisecond-precision timing using `clock_gettime()`
- **SPI communication:** Polling-based joystick input via ADC
- **LED feedback:** Visual cues with dual-color LED (red/green)
- **Input validation:** Software filtering for reliable joystick input
- **Modular HAL:** Abstracted joystick and LED interfaces

## Hardware Requirements

- **Platform:** BeagleY-AI
- **Input:** Analog joystick (connected via SPI/ADC)
  - VRx → Channel 0
  - VRy → Channel 1
- **Output:** Dual-color LED (red/green)

## Game Flow

1. Welcome message and instructions
2. LED flash sequence (green/red, 4 cycles)
3. Joystick release verification
4. Random delay (0.5s - 3.0s)
5. Direction prompt (up/down)
6. User response timing (5s timeout)
7. Result display: 
   - Correct: show time, update best score, flash green
   - Incorrect: flash red
   - Quit: press left/right

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
