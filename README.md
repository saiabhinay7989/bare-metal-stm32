# Bare-Metal Programming on STM32F446RE

## Overview

This project demonstrates bare-metal programming on an ARM Cortex-M4 microcontroller without using any HAL libraries, SDKs, or auto-generated code.
All configurations, including startup code, linker script, interrupt handling, and peripheral control, are implemented manually using low-level C.

---

## Hardware Used

* STM32 Nucleo-F446RE

---

## Tools and Environment

* ARM GCC Toolchain (arm-none-eabi-gcc)
* OpenOCD
* GDB
* Git and GitHub

---

## Project Structure

```
stm32_baremetal/
├── task_1/
├── task_2/
├── task_3/
├── README.md
```

* task_1: LED blinking using software delay
* task_2: SysTick interrupt-based LED control
* task_3: Button interrupt with state machine

---

## Task 1: System Liveness Verification

* Configured GPIOA Pin 5 as output
* Implemented LED blinking using a software delay loop

Result:
The LED blinking confirms correct startup code, linker configuration, and GPIO setup.

---

## Task 2: Interrupt-Driven Timing

* Configured SysTick timer
* Generated periodic interrupts (500 ms)
* Implemented an interrupt service routine to toggle the LED

Result:
The LED blinks without using blocking delay loops, demonstrating interrupt-based timing.

---

## Task 3: Interactive State Machine

* Configured external interrupt on PC13 (user button)
* Implemented a state machine with two modes:

  * Slow mode: LED toggles every 1 second
  * Fast mode: LED toggles every 200 milliseconds
* Implemented software debounce to handle button bounce

Result:
Button input dynamically changes the LED blinking rate, demonstrating interrupt-driven interaction and state control.

---

## Key Concepts Implemented

* Bare-metal programming without HAL or SDK
* Custom startup code and vector table
* Linker script and memory mapping (FLASH and SRAM)
* SysTick timer and external interrupts (EXTI)
* NVIC configuration
* Memory-mapped register access
* Interrupt service routines
* State machine design

---

## Build Instructions

```bash
make clean
make
```

---

## Flash and Debug

```bash
openocd -f board/st_nucleo_f4.cfg
```

```bash
arm-none-eabi-gdb final.elf
```

```gdb
target remote localhost:3333
monitor reset halt
load
monitor reset init
continue
```

---

## Notes

* No external libraries or HAL are used
* All configurations are done manually
* The project is fully platform-independent at the bare-metal level

---

## Author

Sai Abhinay
