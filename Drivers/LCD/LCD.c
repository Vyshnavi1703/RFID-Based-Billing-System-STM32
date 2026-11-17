/***********************************
Name : R.VYSHNAVI
KMID : KM62BEAI09
File : lcd.c
***********************************/
#include"stm32f401rbt6.h"   
#include"lcd.h"
#include"gpio.h"
#include"systicktimer.h"


/****************************
     LCD_INITIALIZATION
****************************/

/*******************************************************************
                void KM_Lcd_Init(void)
********************************************************************
@begin: THIS FUNCTION IS USED TO INTIALIZE THE LCD 
@Params: UNSINGED CHAR CH
@Ret_value: VOID
@Note: FOLLOWING THE COMMANDS FROM THE DATASHEET
********************************************************************/

void KM_Lcd_Init(void)
{
	KM_Mdelay(20);
	KM_Lcd_Write_Cmd(0x33);
	KM_Mdelay(1);
	KM_Lcd_Write_Cmd(0x32);
	KM_Lcd_Write_Cmd(0x0C);
	KM_Lcd_Write_Cmd(0x01);
}


/*******************************
      WRITE_DATA_FUNCTIONS
*******************************/

/*******************************************************************
                void KM_Lcd_Write_Data(unsigned char ch)
********************************************************************
@begin: THIS FUNCTION IS USED TO SEND THE DATA TO THE LCD BY SENDING 4BITS AT A TIME(2TIMES FOR 8BIT)
@Params: UNSINGED CHAR CH
@Ret_value: VOID
@Note: SENDING DATA BY HIGHER AND LOWER NIBBLES SENDING SEPERATLY
********************************************************************/

void KM_Lcd_Write_Data(unsigned char ch)
{	
	KM_GPIO_Write_Pin(PORTB,LCD_RW,0);
	//GPIOB_ODR &= ~(0x1<<5);
	KM_GPIO_Write_Pin(PORTB,LCD_RS,1);
	//GPIOB_ODR |= (0x1<<4);
	write_high_nibble(ch);
	write_low_nibble(ch);
}

/*********************************
       WRITE_CMD_FUNCTIONS
*********************************/

/*******************************************************************
                void KM_Lcd_Write_Cmd(unsigned char ch)
********************************************************************
@begin: THIS FUNCTION IS USED TO SEND THE CMD TO THE LCD BY SENDING 4BITS AT A TIME(2TIMES FOR 8BIT) 
@Params: UNSINGED CHAR CH
@Ret_value: VOID
@Note: SENDING DATA BY HIGHER AND LOWER NIBBLES SENDING SEPERATLY
********************************************************************/


void KM_Lcd_Write_Cmd(unsigned char ch)
{
	KM_GPIO_Write_Pin(PORTB,LCD_RW,0);
	//GPIOB_ODR &=~(0x3<<4);
	KM_GPIO_Write_Pin(PORTB,LCD_RS,0);
	write_high_nibble(ch);
	write_low_nibble(ch);
}

/*******************************************************************
                void write_low_nibble(unsigned char ch)
********************************************************************
@begin: THIS FUNCTION IS USED TO SEND THE LOWER NIBBLE TO THE LCD BY SENDING 4BITS AT A TIME
@Params: UNSINGED CHAR CH
@Ret_value: VOID
@Note: SENDING 4BIT LOWER NIBBLES TO THE LCD BY ACTIVATING THE ENABLE PIN FOR 10MS AND AGAIN TURNING OFF
********************************************************************/

void write_low_nibble(unsigned char ch)
{
	GPIOB_ODR &= ~(0xf);
	GPIOB_ODR |=(ch& (~(0xf<<4)));
	GPIOB_ODR |=(0x1<<8);
	KM_Mdelay(10);
	GPIOB_ODR &= ~(0x1<<8);
}


/*******************************************************************
                void write_high_nibble(unsigned char ch)
********************************************************************
@begin: THIS FUNCTION IS USED TO SEND THE HIGHER NIBBLE TO THE LCD BY SENDING 4BITS AT A TIME
@Params: UNSINGED CHAR CH
@Ret_value: VOID
@Note: SENDING 4BIT NIBBL HIGHER NIBBLES TO THE LCD BY ACTIVATING THE ENABLE PIN FOR 10MS AND AGAIN TURNING OFF
********************************************************************/

void write_high_nibble(unsigned char ch)
{
	GPIOB_ODR &= ~(0xf);
	GPIOB_ODR |=(ch>>4);
	GPIOB_ODR |=(0x1<<8);
	KM_Mdelay(10);
	GPIOB_ODR &= ~(0x1<<8);
}


void KM_Lcd_Write_Str(char str[])
{ int i=0;
	while(str[i]!='\0')
	{		
		KM_Lcd_Write_Data(str[i]);
		i++;
	}
}
	