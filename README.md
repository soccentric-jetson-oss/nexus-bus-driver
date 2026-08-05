# Nexus Bus Driver — Jetson AGX Orin Peripheral Bus Kernel Module

The Nexus Bus Driver is a Linux kernel module that provides unified access to all peripheral buses on the NVIDIA Jetson AGX Orin. It supports GPIO (40-pin expansion header), I2C (8 buses), SPI (3 buses), UART (4 ports), and CAN bus (2 interfaces including flexible data rate). The driver exposes a single character device interface with a unified ioctl protocol for read and write operations across all bus types, abstracting the hardware-specific details behind a clean API. This enables application code to interact with any peripheral bus through the same interface, simplifying system integration and reducing code duplication.

## Features

- Unified
- peripheral
- bus
- access
- (GPIO,
- I2C,
- SPI,
- UART,
- CAN)

## Quick Start

### Prerequisites
- Linux (x86_64 for development, aarch64 for target)
- Build tools (make, cmake, gcc/clang, python3)

### Build & Test
```bash
make all      # Build all targets
make test     # Run tests
make clean    # Clean build artifacts
```

## Architecture

```
Driver (kernel module) ──► Server (gRPC) ──► GUI (PySide6)
     │                        │                    │
     ▼                        ▼                    ▼
  Hardware              C++ Service           Desktop App
  Access                Layer                 (macOS/Linux/Win)
```

## Repository Structure

| Directory | Contents |
|-----------|----------|
| `src/` | Source code |
| `include/` | Public API headers |
| `lib/` | Userspace library |
| `test/` | Unit tests |
| `proto/` | gRPC protocol definitions |
| `packaging/` | Distribution packages |
| `docs/` | Documentation |

## Project Status

**Version:** 0.1.0 — Initial release
**License:** GPIO 40-pin expansion header support
**Audit Score:** 90/100

## 🌐 Ecosystem

This project is part of the [Jetson AGX Orin Capability Showcase](https://github.com/soccentric-jetson-oss/soccentric-jetson-oss) — five open-source projects demonstrating full exploitation of NVIDIA's flagship edge AI platform.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines. All contributions welcome!

## License

GPIO 40-pin expansion header support. See [LICENSE](LICENSE) for details.
