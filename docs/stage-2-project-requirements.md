# 📋 Stage 2 – Project Requirements & Development Plan

## 🧾 Project Requirements Document (PRD)

### 🏷️ Project Title

**Linux-Based Virtual Smart-Meter Pulse Counter and Energy Analytics Agent**

### 🎯 Project Objective

Build a software-only smart-meter prototype for Linux. A C Linux kernel module will expose a virtual meter device. A C++ application will send simulated pulse events to the device, read the accumulated count, and calculate estimated energy use, power, and cost.

### ❓ Problem Statement

A physical smart meter counts electrical energy pulses and provides readings for monitoring and analysis. This project models that flow in software so that Linux device-driver concepts and C/C++ system programming can be learned without connecting physical meter hardware.

### 👥 Intended Users

- Students learning Linux device drivers and system programming.
- Evaluators who need to run and observe the prototype in a Linux environment.

## 📦 Project Scope

### ✅ Included

- A Linux kernel module written in **C**.
- A virtual character device named `/dev/smart_meter`.
- A C-compatible header defining the driver’s control interface.
- A C++ command-line application that simulates meter pulses and requests readings.
- Energy, estimated power, and estimated cost calculations.
- Build and run instructions for Ubuntu Linux.
- Documentation, diagrams, test records, and GitHub source code.

### 🚫 Excluded

- Physical meters, sensors, microcontrollers, and external hardware.
- Python, Java, or other programming languages for project implementation.
- Utility billing, legally valid meter readings, or production deployment.
- A graphical user interface or cloud service.

## ⚙️ Functional Requirements

- **FR-01:** The C kernel module shall register a virtual character device named `/dev/smart_meter`.
- **FR-02:** The driver shall maintain a non-negative 64-bit cumulative pulse count.
- **FR-03:** The driver shall provide an ioctl operation to add a specified number of simulated pulses.
- **FR-04:** The driver shall provide an ioctl operation to read the current pulse count.
- **FR-05:** The driver shall provide an ioctl operation to reset the count for a new demonstration.
- **FR-06:** The driver shall protect shared counter data against concurrent access.
- **FR-07:** The C++ application shall open and communicate with `/dev/smart_meter`.
- **FR-08:** The application shall let the user generate simulated pulse events and display the total pulse count.
- **FR-09:** The application shall convert pulses into estimated energy using a configurable meter constant, initially **1000 pulses per kWh**.
- **FR-10:** The application shall estimate power from pulse changes over a measured time interval.
- **FR-11:** The application shall estimate cost using a configurable sample tariff.
- **FR-12:** The application shall report clear errors when the device is unavailable or an operation fails.

## 🛡️ Non-Functional Requirements

- **NFR-01 – Language:** Project implementation source code shall use only C and C++.
- **NFR-02 – Operating system:** Build and run the project on Linux, using the Ubuntu virtual machine.
- **NFR-03 – Reliability:** Reject invalid pulse values and report failed system calls clearly.
- **NFR-04 – Safety:** Loading and unloading the kernel module require administrator privileges. Do not use this prototype for real billing or electrical control.
- **NFR-05 – Maintainability:** Keep driver, shared interface definitions, C++ application, and documentation in separate, clearly named files or folders.
- **NFR-06 – Usability:** Provide simple commands for building, loading, running, and unloading the prototype.
- **NFR-07 – Version control:** Commit each completed stage and push it to the project’s GitHub repository.

## 🧩 Planned Modules

1. **Virtual Meter Driver (C):** Registers `/dev/smart_meter`, stores the pulse count, and handles ioctl requests.
2. **Driver Interface Header (C-compatible):** Defines ioctl commands and shared data types for both kernel and user space.
3. **Pulse Simulator (C++):** Generates pulse events and sends them to the driver.
4. **Analytics Agent (C++):** Reads the count and calculates estimated kWh, power, and cost.
5. **Build and Documentation:** Makefiles, README updates, execution instructions, diagrams, and stage reports.

## 📦 Stage 2 Deliverables

- This Project Requirements Document.
- A documented project scope and module list.
- A development timeline through the **5 October 2026** deadline.
- Git history showing the Stage 2 work.

## 🗓️ Development Timeline

| Date | Planned work | Evidence |
|---|---|---|
| **1 October 2026** | Complete requirements and development plan; prepare Linux build tools. | Stage 2 PRD and Git commit |
| **2 October 2026** | Complete architecture, interface design, and UML diagrams. | Stage 3 design documents and Git commit |
| **3 October 2026** | Build the first driver and C++ prototype; demonstrate simulated pulse counting. | Prototype demonstration and Git commit |
| **4 October 2026** | Integrate, test, fix issues, and complete run instructions. | Test records, updated documentation, Git commit |
| **5 October 2026** | Final review, GitHub push, and project presentation preparation. Contact the trainer to arrange the 5–10 minute evaluation. | Final repository and presentation |

## ✅ Acceptance Criteria

- The driver builds and loads on the target Ubuntu Linux VM.
- `/dev/smart_meter` is created while the module is loaded and removed when it is unloaded.
- The C++ application can add simulated pulses and read the resulting count.
- The displayed energy and cost values match the documented formulas and configuration.
- Invalid input and unavailable-device errors are handled clearly.
- The README explains dependencies and how to build, run, and stop the project.
- Source code, documentation, and progress evidence are committed and pushed to GitHub.

## ⚠️ Assumptions and Risks

- The Ubuntu VM kernel must have matching Linux kernel headers available.
- Driver development and module loading require administrator access.
- Kernel API differences may require small code adjustments for the installed Ubuntu kernel.
- Pulse input, power, energy, and cost are simulated estimates; they are not physical measurements.
- The project must be kept small enough to complete and demonstrate by the deadline.

## ➡️ Next Stage

**Stage 3 – System Design & Architecture:** define the architecture, ioctl data structures, device interactions, UML diagrams, Linux build environment, and implementation plan.
