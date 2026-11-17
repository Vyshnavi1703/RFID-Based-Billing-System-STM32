/***************************************************
Name : R.VYSHNAVI
KMID : KM62BEAI09
File : gpio.c
***************************************************/


#include "stm32f401rbt6.h"
#include "gpio.h"
#include "systicktimer.h"

/********************************** INITIALIZATION ************************************/

void KM_GPIO_Init(int port)
{
	switch(port)
	{
		case PORTA : RCC_AHB1ENR|=(0x1<<port);break;
		case PORTB : RCC_AHB1ENR|=(0x1<<port);break;
		case PORTC : RCC_AHB1ENR|=(0x1<<port);break;
	}
}

/************************************* MODES ******************************************/

void KM_GPIO_Pin_Mode(int port, int pin, int mode)
{
	if(mode==OUT)                              
	{
		switch(port)                              
		{
			case PORTA: GPIOA_MODER &= ~(0X03<<(pin * 2));    
									GPIOA_MODER |=  (0X01<<(pin * 2));   
									break;
			case PORTB: GPIOB_MODER &= ~(0X03<<(pin * 2));    
									GPIOB_MODER |=  (0X01<<(pin * 2));    
									break;
			case PORTC: GPIOC_MODER &= ~(0X03<<(pin * 2));    
									GPIOC_MODER |=  (0X01<<(pin * 2));   
									break;
		}
	}
	else if(mode==IN)														
	{
		switch(port)															
		{
			case PORTA:	GPIOA_PUPDR &= ~(0X3<<(pin * 2));    
									GPIOA_PUPDR |=  (0X1<<(pin * 2));   
									break;
			case PORTB:	GPIOB_PUPDR &= ~(0X3<<(pin * 2));			
									GPIOB_PUPDR |=  (0X1<<(pin * 2));     
									break;
			case PORTC: GPIOC_PUPDR &= ~(0X3<<(pin * 2));			
									GPIOC_PUPDR |=  (0X1<<(pin * 2));			
									break;
		}
	}
	else if(mode==ANA)
	{
		switch(port)
		{
			case PORTA: GPIOA_MODER &= ~(0X3<<pin*2); //CLEARING THE BITS AT REQUIRED PIN
			            GPIOA_MODER |=  (0X3<<pin*2); //CONGIGURATING THE MODE AS OUTPUT FOR THE GIVEN PINS 
			            break;
			
			case PORTB: GPIOB_MODER &= ~(0X3<<pin*2);//CLEARING THE BITS AT REQUIRED PIN
			            GPIOB_MODER |=  (0X3<<pin*2);//CONGIGURATING THE MODE AS OUTPUT FOR THE GIVEN PINS 
			            break;
			
			case PORTC: GPIOC_MODER &= ~(0X3<<pin*2); //CLEARING THE BITS AT REQUIRED PIN
						      GPIOC_MODER |=  (0X3<<pin*2);  //CONGIGURATING THE MODE AS OUTPUT FOR THE GIVEN PINS 
			            break;
		}
	}
	else if(mode==ALT)													
	{
		switch(port)													
		{
			case PORTA: GPIOA_MODER &= ~(0X3<<(pin * 2));    
  			          GPIOA_MODER |=  (0X2<<(pin * 2));     
			            break;
			case PORTB: GPIOB_MODER &= ~(0X3<<(pin * 2));			
									GPIOB_MODER |=  (0X2<<(pin * 2));     
									break;																	
			case PORTC:	GPIOC_MODER &= ~(0X3<<(pin * 2));			
									GPIOC_MODER |=  (0X2<<(pin * 2));			
									break;
		}
	}
}

/****************************************** OUTPUT *********************************************/

void KM_GPIO_Write_Pin(int port, int pin, int data)
{
	if(data==0)
	{
		switch(port)
		{
			case PORTA: GPIOA_ODR &= ~(0x1<<pin);break;
			case PORTB: GPIOB_ODR &= ~(0x1<<pin);break;
			case PORTC: GPIOC_ODR &= ~(0x1<<pin);break;
		}
	}
	else if(data==1)
	{
		switch(port)
		{
			case PORTA: GPIOA_ODR |= (0x1<<pin);break;
			case PORTB: GPIOB_ODR |= (0x1<<pin);break;
			case PORTC: GPIOC_ODR |= (0x1<<pin);break;
		}
	}
}

/************************************** TOGGLE *********************************************/

void KM_GPIO_Toggle(int port, int pin)
{
	switch(port)
	{
		case PORTA: GPIOA_ODR ^= (0x1<<pin);break;
		case PORTB: GPIOB_ODR ^= (0x1<<pin);break;
		case PORTC: GPIOC_ODR ^= (0x1<<pin);break;
	}
}

/**************************************** INPUT *******************************************/

int KM_GPIO_Read_Pin(int port, int pin)
{
	switch(port)
	{
		case PORTA : return (GPIOA_IDR & (0X1<<pin)); break;  
		case PORTB : return (GPIOB_IDR & (0X1<<pin)); break;  
		case PORTC : return (GPIOC_IDR & (0X1<<pin)); break;
	}
	return 0;
}
