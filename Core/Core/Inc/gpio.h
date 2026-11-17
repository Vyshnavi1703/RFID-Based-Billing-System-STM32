/***************************************************
Name : R.VYSHNAVI
KMID : KM62BEAI09
File : gpio.h
***************************************************/
#define RED_LED 13 
#define GREEN_LED 14
#define BUZZER 12

#define SW_ENT 10
#define SW_DN 9
#define SW_UP 8

#define PORTA 0
#define PORTB 1
#define PORTC 2

#define IN 0 //PUPDR
#define OUT 1 //MODER
#define ANA 2
#define ALT 3

#define SET 1
#define RESET 0

void KM_GPIO_Init(int port);
void KM_GPIO_Pin_Mode(int port, int pin, int mode);
void KM_GPIO_Write_Pin(int port, int pin, int data);
void KM_GPIO_Toggle(int port, int pin);
int KM_GPIO_Read_Pin(int port, int pin);
