/***************************************************
Name : R.VYSHNAVI
KMID : KM62BEAI09
File : systicktimer.c
***************************************************/


#include "stm32f401rbt6.h"
#include "gpio.h"
#include "LCD.h"
#include "systicktimer.h"

int count=0;
void KM_Systick_Init(void)
{
	STK_LOAD = 16000;               
	STK_VAL |= (0X1);                
	STK_CTRL = 0X7;                   
}

//Operation Polling and interrupt
void KM_Mdelay(int x)
{
	STK_CTRL &= ~(0X7);            
	STK_CTRL |= (0X5); 
	STK_LOAD = 16000*x;
	STK_VAL |= 0x123;
	while(!(STK_CTRL & 0x1<<16));
}

void KM_udelay(int x)
{
	STK_CTRL &= ~(0X7);            
	STK_CTRL |= (0X5); 
	STK_LOAD = 16*x;
	STK_VAL |= 0x123;
	while(!(STK_CTRL & 0x1<<16));
}

void KM_Mdelay_IT(int n)
{
	int temp = 0;
	temp = n + count;
	STK_CTRL |= (0X7); 
	STK_LOAD = 16000;
	STK_VAL |= 0x455;
	while(temp > count);
}

void KM_udelay_IT(int n)
{
	int temp = 0;
	temp = n + count;
	STK_CTRL |= (0X7); 
	STK_LOAD = 16;
	STK_VAL |= 0x455;
	while(temp > count);
}

void SysTick_Handler(void)
{
	count++;
}
