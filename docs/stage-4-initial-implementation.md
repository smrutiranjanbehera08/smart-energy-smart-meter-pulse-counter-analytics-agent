# ⚙️ Stage 4 – Initial Implementation & Prototype

## 🎯 Stage Objective

Build an initial working prototype that connects a Linux kernel module to a C++ command-line analytics application.

## 🧩 Implemented Components

- **Linux kernel module:** Registers `/dev/smart_meter` and tracks a pulse count.
- **IOCTL interface:** Supports adding simulated pulses, reading the count, and resetting it.
- **C++ device wrapper:** Opens the device and sends the IOCTL requests.
- **Analytics engine:** Calculates estimated energy, average power, and sample cost.
- **Command-line application:** Provides options to simulate pulses, view analytics, reset the count, and exit.
- **Build setup:** The root `Makefile` builds the kernel module and C++ application.

## 🖥️ Prototype Environment

- Operating system: Ubuntu Linux 24.04 ARM64 in UTM
- Kernel: `7.0.0-34-generic`
- Application language: C++
- Driver language: C
- Meter constant: 1,000 pulses per kWh
- Sample tariff: INR 8 per kWh

## ▶️ Demonstrated Functionality

The prototype was built successfully. The driver created `/dev/smart_meter`, and the application was run with administrator privileges.

Demonstration:

- Simulated 100 pulses.
- Read a total of 100 pulses, estimated energy of 0.100 kWh, and estimated cost of INR 0.800.
- Simulated 1 additional pulse.
- Read a total of 101 pulses, estimated energy of 0.101 kWh, and estimated cost of INR 0.808.
- The application also displayed an average power estimate based on the time between readings.
- Exited the application successfully.

## 🛠️ Issues and Resolutions

- The installed kernel headers did not provide `no_llseek`; removed that file-operation entry so the module compiled.
- The C++ device header was missing its opening `#ifndef` guard; added it to match the existing `#define` and `#endif`.
- Compiler naming, `pahole`, and BTF messages appeared during the kernel build. They did not prevent the module from building.

## 📌 Current Limitations

- Pulses are simulated through the application; no physical meter is connected.
- Energy and cost are estimates based on the configured meter constant and sample tariff.
- The average power estimate depends on the time between readings.
- The application currently requires administrator privileges to access the device.

## ➡️ Next Stage

Stage 5 will add and document unit, integration, and system testing; resolve issues found; and improve reliability and documentation.
