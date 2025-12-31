# Gemini Project Summary: coffee-scale

This document provides a summary of the `coffee-scale` project for easy onboarding and understanding.

## Project Overview

The `coffee-scale` project is a C++ application designed to run on a Raspberry Pi Pico. It implements a digital coffee scale using an HX711 Analog-to-Digital Converter (ADC) to interface with a load cell.

## Key Information

- **Project Name:** coffee-scale
- **Target Platform:** Raspberry Pi Pico
- **Core Functionality:** Digital scale for weighing coffee.
- **Hardware Dependencies:**
    - Raspberry Pi Pico
    - HX711 ADC
    - Load Cell

## Software Dependencies

- **Raspberry Pi Pico SDK:** The project relies on the official Pico SDK. The path to the SDK must be provided during the build process for the Pico target.

## Building the Project

The project uses CMake for building. There are two primary build targets:

### 1. Host Build (for Testing)

This build is intended for running unit tests on the host machine (not the Pico).

To build for the host, run the following script:
```bash
./build-host.sh
```
This will configure CMake to build in the `build-host/` directory and enable the tests.

### 2. Pico Build (for Deployment)

This build is for compiling the application to run on the Raspberry Pi Pico.

To build for the Pico, run the following script:
```bash
./build-pico.sh
```
This script configures CMake with the path to the Pico SDK and builds the project in the `build-pico/` directory. **Note:** You may need to edit `build-pico.sh` to set the correct `PICO_SDK_PATH` for your environment.

## Code Structure

- `src/`: Contains the main source code for the application.
  - `app/`: High-level application logic, including `main.cpp`.
  - `core/`: Core components like the ADC interface.
  - `hal/`: Hardware Abstraction Layer for components like the HX711.
  - `bsp/`: Board Support Package files, including the PIO program for the HX711.
- `test/`: Contains unit tests for the project.
- `CMakeLists.txt`: The main CMake script for the project.
- `pico_sdk_import.cmake`: Handles importing the Pico SDK into the CMake project.
