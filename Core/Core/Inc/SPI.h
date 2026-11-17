void SPI_Init(void);
//void SPI_OutChar(unsigned char ch);
unsigned char SPI_OutChar(unsigned char ch);
unsigned char SPI_InChar_Block(void);
unsigned char SPI_InChar_NonBlock(void);
void Slave_Config(void);
void Master_Config(void);