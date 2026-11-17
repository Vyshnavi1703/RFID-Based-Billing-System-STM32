#include "stm32f401rbt6.h"
#include "LCD.h"
#include "gpio.h"
#include "systicktimer.h"
#include "SPI.h"

#define NO_DATA 0
unsigned char SPI_DATA;

void SPI_Init(void)
{
	KM_GPIO_Init(PORTA);            // ENABLE CLOCK FOR GPIOA
	KM_GPIO_Pin_Mode(PORTA,4,OUT);  // PA4 FOR SPI_NSS   
	KM_GPIO_Pin_Mode(PORTA,5,ALT);  // PA5 FOR SPI_SCK
	KM_GPIO_Pin_Mode(PORTA,6,ALT);  // PA6 FOR SPI_MISO
	KM_GPIO_Pin_Mode(PORTA,7,ALT);  // PA7 FOR SPI_MOSI
	
	GPIOA_AFRL &= ~(0XFFFF0000);    // CLEARING THE AF4,AF5,AF6,AF7 TO CONFIGURE AS SPIO FOUR PINS  
	GPIOA_AFRL |= (0x55550000);     // LOADING '0101' IN AF4,AF5,AF6,AF7 
	
	RCC_APB2ENR |= (0X1<<12);       // ENABLE CLOCK FOR SPI

//	SPI_CR2 |= (0X1<<6);            // RXNEIE INTERRUPT ENABLE
//	NVIC_ISER1 |= (0X1<<3);         // SPI INTERRUPT ENABLE
	
}

/******************SLAVE_CONFIGURATION***********************/

void Master_Config()
{
	//BAUD RATE IS Fpclk/2max  IE,000
	//CPOL AND CPHA IS ALSO IN '00' MODE ie, +VE CLOCK AND RAISING EDGE MODE
	//master
//	SPI_CR2 |= (0X1<<2);            // SLAVE SELECT 
//	SPI_CR1 |= (0X1<<6);            // TO ENABLE THE SPI (SPE)
// 	SPI_CR1 |= (0X1<<2);            // FOR MASTER SELECTION (MSTR)

	  SPI_CR1 |= (1<<9); // SSM
    SPI_CR1 |= (1<<8); // SSI
    SPI_CR1 |= (1<<2); // Master
    SPI_CR1 |= (1<<6); // SPI enable
}

void Slave_Config()
{
  SPI_CR1 |=  (0X1<<9);         // SET SOFWARE SLAVE MANAGEMENT ENABLED(SSM)
	SPI_CR1 &= ~(0X1<<8);         // CLEAR INTERNAL SLAVE SELECT(SSI)
	SPI_CR1 &= ~(0X1<<2);         // CLEAR TO SLAVE SELECTION(MSTR)
	SPI_CR1 |= (0X1<<6);          // SPI ENABLE 
}

/**************SPI_OUTCHAR***************/

unsigned char SPI_OutChar(unsigned char ch)
{
	while(!(SPI_SR & (0x1<<1))); // TXE
	SPI_DR = ch;

	while(!(SPI_SR & (0x1<<0))); // RXNE
	return SPI_DR;
}
//void SPI_OutChar(unsigned char ch)
//{
//	while(!((SPI_SR )& (0x1<<1))); // CHECKING TXE BIT
//	SPI_DR =ch;
//}

/**************SPI_INCHAR_BLOCK***************/

unsigned char SPI_InChar_Block(void)
{
	while(!((SPI_SR) & (0x1))); // CHECKING RXNE BIT
	return SPI_DR;
}

/**************SPI_INCHAR_NONBLOCK***************/

unsigned char SPI_InChar_NonBlock(void)
{
	if((SPI_SR & (0X1<<0)))   // CHECKING RXNE BIT
	{
		return SPI_DR;
	}
	return NO_DATA;
}

/*************SPI_HANDLER***********************/

void SPI1_IRQHandler()
{
	SPI_DATA = SPI_DR;
}
