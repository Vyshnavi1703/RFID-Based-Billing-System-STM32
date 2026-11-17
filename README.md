
# RFID-Based Automated Billing System Using STM32F401RBT6

## Project Overview

Designed and developed an RFID-based automated billing system using the STM32F401RBT6 ARM Cortex-M4 microcontroller. The system enables automated product identification and billing by reading RFID tags through the RC522 module. The microcontroller processes the scanned information, calculates the corresponding product cost, and displays billing details on a 16x2 LCD.

## Key Features

- RFID-based product identification using the RC522 module.
- SPI communication between the RFID reader and STM32 microcontroller.
- Automated product price identification and billing calculation.
- Real-time billing information display using a 16x2 LCD.
- LED and buzzer-based status indications.

## Hardware Components

| Component | Description |
|---|---|
| STM32F401RBT6 | ARM Cortex-M4 Microcontroller |
| RC522 | RFID Reader Module |
| 16x2 LCD | Billing Information Display |
| LED | Visual Status Indication |
| Buzzer | Audio Status Indication |

## Technologies and Tools

- **Programming Language:** Embedded C
- **Microcontroller:** STM32F401RBT6
- **Communication Protocol:** SPI
- **Peripheral Interfaces:** GPIO, SPI
- **Development Environment:** Keil µVision5

## System Implementation

1. The RC522 RFID reader scans the RFID tag.
2. The STM32F401RBT6 receives the tag information through SPI communication.
3. The microcontroller processes the scanned RFID data.
4. The corresponding product information and predefined price are identified.
5. The product price is added to the total billing amount.
6. The 16x2 LCD displays the billing information.
7. LED and buzzer provide status indications.

## Project Directory

- **Core:** Application source and header files.
- **Drivers/RFID:** RFID reader driver files.
- **Drivers/LCD:** LCD interface driver files.
- **Documentation:** Project-related technical documentation.
- **Images:** Project implementation photographs.

## Applications

- Automated retail billing systems
- RFID-enabled smart shopping carts
- Automated checkout systems
- Smart product identification systems

## Future Enhancements

- Support for additional product categories.
- Transaction history and billing record management.
- Wireless connectivity for remote monitoring.
- Enhanced product and inventory management.

## Author

**Vyshnavi Rachaputi**

B.Tech – Electronics and Communication Engineering

GitHub: [Vyshnavi1703](https://github.com/Vyshnavi1703)
