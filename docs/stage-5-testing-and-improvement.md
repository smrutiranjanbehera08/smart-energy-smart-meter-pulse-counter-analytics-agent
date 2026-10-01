# 🧪 Stage 5 – Testing, Integration & Improvement

## 🎯 Stage Objective

Check that the Linux kernel module and C++ application build and work together correctly. Record test results, fix any issues found, and update the project documentation.

## 🖥️ Test Environment

- Operating system: Ubuntu Linux 24.04 ARM64 in UTM
- Kernel: Record the output of `uname -r` when testing
- Driver language: C
- Application language: C++
- Hardware: Simulated pulse input; no physical meter is connected

## ✅ Planned Tests

| ID | Test | Expected result |
|---|---|---|
| T1 | Build the driver and C++ application with `make` | Both build successfully |
| T2 | Load the kernel module | The module loads and `/dev/smart_meter` exists |
| T3 | Start the application | The menu appears without an error |
| T4 | Add 100 pulses and read analytics | Pulse count is 100; energy is 0.100 kWh; estimated cost is INR 0.800 |
| T5 | Add 1 more pulse and read analytics | Pulse count is 101; energy is 0.101 kWh; estimated cost is INR 0.808 |
| T6 | Reset the count and read it again | Pulse count is reset to 0 |
| T7 | Try an invalid menu choice or pulse input | The application handles invalid input without crashing |
| T8 | Exit and unload the module | The application exits and the module unloads cleanly |

## 📝 Test Result Record

For each test, record:

- Test ID and date
- Command or menu actions used
- Expected result
- Actual result
- Pass or fail
- Any issue found and how it was resolved

Do not mark a test as passed until it has been performed.

## ⚠️ Known Limitations

- Pulse input is simulated by the software; no physical meter is connected.
- Energy and cost are estimates using the configured meter constant and sample tariff.
- Average power depends on the time between readings.
- Device access currently requires administrator privileges.

## ➡️ Next Step

Run the planned tests in Ubuntu, record their actual results, fix any issues, and then update the README and project instructions if needed.

## 📋 Test Results — 2 October 2026

| ID | Result | Observed outcome |
|---|---|---|
| T1 | **Pass** | `make clean && make` rebuilt the kernel module and C++ application successfully. |
| T2 | **Pass** | `smart_meter_driver` was loaded and `/dev/smart_meter` existed. |
| T3 | **Pass** | The application started and displayed its menu. |
| T4 | **Pass** | After reset, 100 pulses produced a count of 100, energy of 0.100 kWh, and estimated cost of INR 0.800. |
| T5 | **Pass** | One additional pulse produced a count of 101, energy of 0.101 kWh, and estimated cost of INR 0.808. |
| T6 | **Pass** | Resetting the count and reading analytics showed 0 pulses, 0.000 kWh, and INR 0.000. |
| T7 | **Pass** | Menu choice `9` was rejected with a helpful message. Pulse input `0` was rejected with the allowed range. The application remained open. |
| T8 | **Pass** | The application exited. The driver unloaded; `lsmod` showed no matching module, and `/dev/smart_meter` no longer existed. |

## 🐞 Issues Observed and Improvement Notes

- The clean build showed compiler-name, `pahole`, and BTF messages. The build still succeeded; BTF generation was skipped because `vmlinux` was unavailable.
- Average power changed substantially between readings (for example, 5517.960 W and 43.199 W). It depends on the elapsed time between readings, so very short intervals can produce high estimates. This remains a limitation to explain during the demonstration.
- The device file is owned by `root` and the application was run with `sudo`. A future improvement could provide a controlled non-root access rule.

## ✅ Stage 5 Progress

The clean build, driver availability, application menu, pulse calculations, reset, invalid-input handling, application exit, and driver unload were checked in the Ubuntu VM. The observed readings matched the configured meter constant and sample tariff.

## 🧮 Analytics Unit Tests — 2 October 2026

Ran `make unit-test`. All eight checks passed:

- Energy calculation for 100 pulses and zero pulses
- Handling a zero meter constant
- Average power for a known one-hour interval
- Handling zero elapsed time and a decreasing pulse count
- Estimated cost for a sample tariff
- Handling negative energy

The test program is written in C++ and checks the analytics functions without loading the kernel driver.
