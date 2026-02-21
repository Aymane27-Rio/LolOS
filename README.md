# LolOS 💻

A custom, bare-metal 32-bit operating system built from scratch, currently featuring a bootable VGA text-mode terminal.

## Features
* Multiboot compliant
* Custom VGA text driver
* Automated CI/CD build pipeline
* (Coming soon: Keyboard input and a basic shell!)

## Prerequisites
To build and run LolOs locally, you need the following installed on a Linux environment (Ubuntu recommended):
* `build-essential` (GCC, Make)
* `nasm` (Assembler)
* `qemu-system-x86` (Emulator for testing)

## Build and Run
Clone the repository and use the included Makefile:

1. Compile the OS and launch it in QEMU:
   ```bash
   make run
   ```
2. Clean up build artifacts:
   ```bash
   make clean
   ```