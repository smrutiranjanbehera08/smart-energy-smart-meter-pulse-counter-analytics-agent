# 🎓 Stage 6 – Final Project Report

## ⚡ Project Title

**Smart Energy Smart-Meter Pulse Counter & Analytics Agent**

## 📌 Project Summary

This individual capstone is a software-only Linux smart-meter prototype. A C Linux kernel module exposes a virtual pulse-counting device. A C++ application sends simulated pulses to the driver, reads the pulse count, and estimates energy use, average power, and cost.

No physical meter or sensor is connected. The project demonstrates Linux device-driver concepts, system programming, C++, software architecture, testing, and Git-based development.

## 🎯 Objectives

- Build and load an external Linux kernel module.
- Expose a device interface at `/dev/smart_meter`.
- Communicate between user space and the driver using IOCTL requests.
- Implement the command-line application and analytics in C++.
- Document the architecture, requirements, implementation, and test results.
- Maintain the source code and documentation in GitHub.

## 🏗️ Architecture

The C++ application uses `SmartMeterDevice` to communicate with `/dev/smart_meter`. The device file is handled by the Linux kernel module. The driver protects the pulse counter with a mutex and supports pulse injection, count reading, and reset operations through the shared IOCTL definitions.

The `AnalyticsEngine` calculates energy, average power, and estimated cost from the pulse count, meter constant, tariff, and elapsed time. Architecture and UML diagrams are included in `README.md`.

## 🧩 Implementation

- **Kernel driver (C):** Registers a miscellaneous character device and handles the pulse-count IOCTL operations.
- **Device wrapper (C++):** Opens the device and sends the driver requests.
- **Analytics engine (C++):** Calculates energy, average power, and sample cost.
- **Command-line application (C++):** Simulates pulses and displays readings.
- **Build system:** The root `Makefile` builds the driver and application and runs the analytics unit tests.
- **Documentation:** Project stages, architecture, and test results are recorded in `docs/`.

## 🖥️ Build and Demonstration

The project was developed and demonstrated in Ubuntu Linux 24.04 ARM64 running in UTM on an Apple Silicon Mac.

Build:

```bash
make
