#include "rfid.h"

/* Chip Select pin control macros
   These control the CS pin of the RFID module for SPI communication */
#define CS_LOW()  KM_GPIO_Write_Pin(PORTA,4,0)   // Activate RFID (CS = 0)
#define CS_HIGH() KM_GPIO_Write_Pin(PORTA,4,1)   // Deactivate RFID (CS = 1)

/* ---------------------------------------------------------
   Function: RC522_WriteReg
   Purpose : Write a value into a specific RFID register
   --------------------------------------------------------- */
void RC522_WriteReg(unsigned char addr, unsigned char val)
{
    CS_LOW();                                // Enable RFID communication

    SPI_OutChar((addr<<1) & 0x7E);            // Send register address (write mode)
    SPI_OutChar(val);                         // Send data to write

    CS_HIGH();                                // Disable RFID communication
}

/* ---------------------------------------------------------
   Function: RC522_ReadReg
   Purpose : Read value from a specific RFID register
   --------------------------------------------------------- */
unsigned char RC522_ReadReg(unsigned char addr)
{
    unsigned char val;

    CS_LOW();                                  // Enable RFID communication

    SPI_OutChar(((addr<<1)&0x7E)|0x80);          // Send register address (read mode)
    val = SPI_OutChar(0x00);                     // Send dummy byte and read response

    CS_HIGH();                                  // Disable RFID communication

    return val;                                         // Return read value
}

/* ---------------------------------------------------------
   Function: RC522_SetBitMask
   Purpose : Set specific bits in a register
   --------------------------------------------------------- */
void RC522_SetBitMask(unsigned char reg, unsigned char mask)
{
    unsigned char tmp;

    tmp = RC522_ReadReg(reg);                 // Read current register value
    RC522_WriteReg(reg, tmp | mask);          // Set required bits using OR operation
}

/* ---------------------------------------------------------
   Function: RC522_ClearBitMask
   Purpose : Clear specific bits in a register
   --------------------------------------------------------- */
void RC522_ClearBitMask(unsigned char reg, unsigned char mask)
{
    unsigned char tmp;

    tmp = RC522_ReadReg(reg);                 // Read current register value
    RC522_WriteReg(reg, tmp & (~mask));       // Clear bits using AND with NOT mask
}

/* ---------------------------------------------------------
   Function: RC522_Init
   Purpose : Initialize RFID RC522 module
   --------------------------------------------------------- */
void RC522_Init(void)
{
    KM_GPIO_Pin_Mode(PORTA,4,OUT);             // Configure CS pin as output
    CS_HIGH();                                 // Keep RFID disabled initially

    SPI_Init();                                // Initialize SPI communication
    Master_Config();                           // Configure MCU as SPI master

    RC522_WriteReg(CommandReg, PCD_RESETPHASE); // Reset RFID module

    KM_Mdelay(50);                              // Small delay for stabilization

    RC522_WriteReg(ModeReg, 0x3D);              // Set communication mode
    RC522_WriteReg(TxASKReg, 0x40);             // Enable ASK modulation

    RC522_SetBitMask(TxControlReg, 0x03);       // Turn ON antenna
}

/* ---------------------------------------------------------
   Function: RC522_ToCard
   Purpose : Send command and data to RFID card and receive response
   --------------------------------------------------------- */
unsigned char RC522_ToCard(unsigned char command,unsigned char *sendData,unsigned char sendLen,unsigned char *backData,unsigned int *backLen)
{
    unsigned char status = MI_ERR;   // Default status = Error
    unsigned char irqEn = 0x00;
    unsigned char waitIRq = 0x00;
    unsigned char lastBits;
    unsigned char n;
    unsigned int i;

    /* If command is TRANSCEIVE (send & receive data) */
    if (command == PCD_TRANSCEIVE)
    {
        irqEn = 0x77;      // Enable interrupts
        waitIRq = 0x30;    // Wait for receive interrupt
    }

    RC522_WriteReg(CommIEnReg, irqEn | 0x80);   // Enable interrupts
    RC522_ClearBitMask(CommIrqReg, 0x80);       // Clear interrupt flags
    RC522_SetBitMask(FIFOLevelReg, 0x80);       // Flush FIFO buffer

    RC522_WriteReg(CommandReg, PCD_IDLE);       // Stop any active command

    /* Write data into FIFO buffer */
    for (i=0;i<sendLen;i++)
        RC522_WriteReg(FIFODataReg, sendData[i]);

    RC522_WriteReg(CommandReg, command);        // Execute command

    /* Start transmission */
    if (command == PCD_TRANSCEIVE)
        RC522_SetBitMask(BitFramingReg, 0x80);

    i = 2000;

    /* Wait until operation completes */
    do
    {
        n = RC522_ReadReg(CommIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitIRq));

    RC522_ClearBitMask(BitFramingReg,0x80);

    if (i != 0)
    {
        /* Check for errors */
        if (!(RC522_ReadReg(ErrorReg) & 0x1B))
        {
            status = MI_OK;

            /* If receiving data from card */
            if (command == PCD_TRANSCEIVE)
            {
                n = RC522_ReadReg(FIFOLevelReg);
                lastBits = RC522_ReadReg(ControlReg) & 0x07;

                if (lastBits)
                    *backLen = (n-1)*8 + lastBits;
                else
                    *backLen = n*8;

                /* Read received data */
                for (i=0;i<n;i++)
                    backData[i] = RC522_ReadReg(FIFODataReg);
            }
        }
        else
            status = MI_ERR;
    }

    return status;   // Return success or error
}

/* ---------------------------------------------------------
   Function: RC522_Request
   Purpose : Detect if an RFID card is present
   --------------------------------------------------------- */
unsigned char RC522_Request(unsigned char reqMode, unsigned char *TagType)
{
    unsigned char status;
    unsigned int backBits;

    RC522_WriteReg(BitFramingReg, 0x07);      // Set bit framing

    TagType[0] = reqMode;                     // Send request mode

    status = RC522_ToCard(PCD_TRANSCEIVE,TagType,1,TagType,&backBits);

    /* Validate response */
    if ((status != MI_OK) || (backBits != 0x10))
    {
        status = MI_ERR;
    }

    return status;
}

/* ---------------------------------------------------------
   Function: RC522_Anticoll
   Purpose : Anti-collision function to read UID of card
   --------------------------------------------------------- */
unsigned char RC522_Anticoll(unsigned char *serNum)
{
    unsigned char status;
    unsigned char i;
    unsigned char serNumCheck = 0;
    unsigned int unLen;

    RC522_WriteReg(BitFramingReg, 0x00);

    serNum[0] = PICC_ANTICOLL;   // Anti-collision command
    serNum[1] = 0x20;

    status = RC522_ToCard(PCD_TRANSCEIVE,serNum,2,serNum,&unLen);

    if (status == MI_OK)
    {
        /* Calculate checksum */
        for (i=0;i<4;i++)
            serNumCheck ^= serNum[i];

        /* Verify UID checksum */
        if (serNumCheck != serNum[4])
            status = MI_ERR;
    }

    return status;
}