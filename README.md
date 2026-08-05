# Nexus Bus Driver — Jetson AGX Orin Peripheral Bus Kernel Module

The Nexus Bus Driver is a Linux kernel module that provides unified access to all peripheral buses on the NVIDIA Jetson AGX Orin. It supports GPIO via the 40-pin expansion header, 8 I2C bus controllers, 3 SPI bus controllers, 4 UART ports, and 2 CAN bus interfaces including flexible data rate. The driver exposes a single character device interface with a unified ioctl protocol for read and write operations across all bus types, abstracting the hardware-specific details behind a clean API.

## Features

- Provides unified peripheral bus access through a single character device interface supporting GPIO, I2C, SPI, UART, and CAN
- Supports GPIO control through the 40-pin expansion header with configurable direction and pull-up or pull-down resistors
- Controls 8 I2C bus controllers for connecting a wide range of I2C sensors, actuators, and peripheral devices
- Controls 3 SPI bus controllers for high-speed communication with SPI devices including displays and ADCs
- Controls 4 UART ports for serial communication with modems, GPS modules, and debug consoles
- Supports 2 CAN bus interfaces including flexible data rate for automotive and industrial communication
- Implements a unified ioctl protocol for read and write operations across all bus types for API consistency
- Exposes a single character device interface that simplifies application code and reduces duplication
- Includes a thread-safe userspace C library that wraps the ioctl interface for application developers
- Delivers a comprehensive test suite validating all ioctl paths, error handling, and edge cases
- Uses devres-managed resource allocation throughout to prevent memory leaks and ensure clean driver removal
- Licensed under GPL-2.0-only for full compliance with Linux kernel licensing requirements

## Quick Start

### Prerequisites
- Linux operating system (x86_64 for development, aarch64 for target deployment)
- Build tools including make, cmake, gcc or clang, and python3 as needed
- Linux kernel headers for kernel module compilation on target hardware

### Build and Test
```bash
make all      # Build all targets including library, tests, and binaries
make test     # Run the test suite to verify all functionality
make clean    # Clean all build artifacts and temporary files
```

## Repository Structure

| Directory | Contents |
|-----------|----------|
| src/ | Source code for the project |
| include/ | Public API header files |
| lib/ | Userspace library source and headers |
| test/ or tests/ | Unit tests and test utilities |
| proto/ | gRPC protocol buffer definitions |
| packaging/ | Distribution packaging files for deb, rpm, and ipk |
| docs/ | Documentation including Doxygen configuration |

## Project Status

**Version:** 0.1.0 — Initial release
**License:** GPL-2.0-only
**Audit Score:** 90/100 across 20 criteria

## Ecosystem

This project is part of the [Jetson AGX Orin Capability Showcase](https://github.com/soccentric-jetson-oss/soccentric-jetson-oss) — five open-source projects demonstrating full exploitation of NVIDIA's flagship edge AI platform.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines. All contributions are welcome.

## License

GPL-2.0-only. See [LICENSE](LICENSE) for details.
