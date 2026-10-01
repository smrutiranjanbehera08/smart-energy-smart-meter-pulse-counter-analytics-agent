# ⚡ Smart Energy Smart-Meter Pulse Counter & Analytics Agent

**🌐 Domain:** IoT, Embedded Systems & Virtual Sensors  
**🖥️ Project Type:** Software-only Linux project  
**👤 Project Format:** Individual project

## 🔍 Project Overview

This project simulates a smart meter entirely in software. A virtual meter generates pulse events, and a Linux device driver passes those events to a C++ application. The application counts the pulses, estimates energy use and power, and displays useful analytics.

## 🎯 Project Goal

To build a Linux-based software system that demonstrates virtual meter pulses, device-driver communication, C++ programming, and energy analytics.

## 🧱 Project Boundary

This project uses software-generated meter pulses only. It does not require a physical meter, sensor, Arduino, or ESP32.

## 💻 Programming Languages

- **C++:** Main user-space application
- **C:** Linux kernel device driver

## 🗺️ Development Stages

1. Project Introduction
2. Requirements & Development Plan
3. System Design & Architecture
4. Initial Implementation & Prototype
5. Testing, Integration & Improvement
6. Final Implementation & Presentation

## System Architecture

```mermaid
flowchart LR
    User([User]) --> App["C++ Analytics Agent"]
    App --> Wrapper["SmartMeterDevice"]
    Wrapper -->|"open and IOCTL"| DevNode["/dev/smart_meter"]
    DevNode --> Driver["Linux Kernel Driver"]
    Driver --> Counter[("Mutex-protected pulse counter")]
    Counter --> Driver
    App --> Analytics["AnalyticsEngine"]
    Analytics --> Results["Energy, power, and cost estimates"]
    Results --> User
    Header["Shared IOCTL definitions"] -.-> Wrapper
    Header -.-> Driver
```

## UML Class Diagram

```mermaid
classDiagram
    class SmartMeterDevice {
        -int file_descriptor_
        +openDevice() bool
        +injectPulses(uint32) bool
        +getPulseCount(uint64&) bool
        +resetCount() bool
        +closeDevice() void
        +isOpen() bool
    }

    class AnalyticsEngine {
        +calculateEnergyKwh(uint64, double) double
        +calculateAveragePowerWatts(uint64, uint64, double, double) double
        +calculateEstimatedCost(double, double) double
    }

    class Main {
        +runApplication() int
    }

    Main --> SmartMeterDevice : communicates with driver
    Main --> AnalyticsEngine : calculates analytics
```

## UML Sequence Diagram

```mermaid
sequenceDiagram
    actor User
    participant App as C++ Application
    participant Device as SmartMeterDevice
    participant Driver as Linux Driver
    participant Counter as Pulse Counter

    User->>App: Select simulate pulses
    App->>Device: injectPulses(value)
    Device->>Driver: IOCTL inject request
    Driver->>Counter: Add pulses
    Counter-->>Driver: Updated count
    Driver-->>Device: Request result
    User->>App: Select show analytics
    App->>Device: getPulseCount()
    Device->>Driver: IOCTL read request
    Driver->>Counter: Read count
    Counter-->>App: Pulse count
    App->>App: Calculate energy, power, and cost
    App-->>User: Display analytics
```

## Build and Run on Ubuntu Linux

Build the kernel module and C++ application:

```bash
make
```

Load the driver and start the application:

```bash
sudo insmod driver/smart_meter_driver.ko
sudo ./smart_meter_agent
```

After exiting the application, unload the driver:

```bash
sudo rmmod smart_meter_driver
```

Run the C++ analytics unit tests:

```bash
make unit-test
```

The kernel module must be built and run in Linux with matching kernel headers. This project was developed in Ubuntu inside a UTM virtual machine.

## Limitations

- Pulse input is simulated; no physical meter or sensor is connected.
- Energy and cost are estimates based on the configured meter constant and sample tariff.
- Average power depends on the time between readings and may vary significantly for short intervals.
- Access to `/dev/smart_meter` currently requires administrator privileges.
