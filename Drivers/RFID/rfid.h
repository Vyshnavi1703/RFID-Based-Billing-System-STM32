#ifndef __RFID_H
#define __RFID_H

#include "stm32f401rbt6.h"
#include "SPI.h"
#include "gpio.h"
#include "systicktimer.h"

/* MFRC522 Commands */
#define PCD_IDLE              0x00
#define PCD_AUTHENT           0x0E
#define PCD_RECEIVE           0x08
#define PCD_TRANSMIT          0x04
#define PCD_TRANSCEIVE        0x0C
#define PCD_RESETPHASE        0x0F
#define PCD_CALCCRC           0x03

/* PICC Commands */
#define PICC_REQIDL           0x26
#define PICC_ANTICOLL         0x93

/* Registers */
#define CommandReg            0x01
#define CommIEnReg            0x02
#define DivIEnReg             0x03
#define CommIrqReg            0x04
#define DivIrqReg             0x05
#define ErrorReg              0x06
#define Status1Reg            0x07
#define Status2Reg            0x08
#define FIFODataReg           0x09
#define FIFOLevelReg          0x0A
#define ControlReg            0x0C
#define BitFramingReg         0x0D
#define ModeReg               0x11
#define TxControlReg          0x14
#define TxASKReg              0x15
#define CRCResultRegM         0x21
#define CRCResultRegL         0x22

/* Status Codes */
#define MI_OK       0
#define MI_NOT      1
#define MI_ERR      2

void RC522_Init(void);
void RC522_WriteReg(unsigned char addr, unsigned char val);
unsigned char RC522_ReadReg(unsigned char addr);
void RC522_SetBitMask(unsigned char reg, unsigned char mask);
void RC522_ClearBitMask(unsigned char reg, unsigned char mask);

unsigned char RC522_Request(unsigned char reqMode, unsigned char *TagType);
unsigned char RC522_Anticoll(unsigned char *serNum);

unsigned char RC522_ToCard(unsigned char command, unsigned char *sendData, unsigned char sendLen,
                           unsigned char *backData, unsigned int *backLen);

#endif