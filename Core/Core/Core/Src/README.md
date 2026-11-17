# Core Source Files

## Overview

This directory contains the C source files responsible for implementing the core firmware functionality of the RFID-Based Billing System based on the STM32F401RBT6 microcontroller.

## File Structure

| Source File | Description |
|---|---|
| `main.c` | Contains the main application entry point and coordinates the firmware execution flow. |
| `gpio.c` | Implements GPIO configuration and control functionality. |
| `SPI.c` | Implements SPI communication functionality for peripheral interfacing. |
| `systicktimer.c` | Implements SysTick timer-related functionality. |

## Purpose

The source files contain the implementation of the firmware functions declared in their corresponding header files. The modular structure improves code organisation, readability, and maintainability.
