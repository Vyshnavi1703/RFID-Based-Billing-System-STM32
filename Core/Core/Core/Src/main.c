

/* Include STM32 and peripheral header files */

#include "stm32f401rbt6.h"
#include "gpio.h"
#include "LCD.h"
#include "rfid.h"
#include "systicktimer.h"


/* Variables to store scanned RFID UID and Tag type */

unsigned char Scanned_UID[5],TagType[2];


/* Welcome message displayed on LCD */

char str[50] = "WELCOME TO KERNEL MASTERS";


/* General variables */

int i, j, p, match, status;


/* Product structure
   Each product contains:
   - UID (RFID card unique ID)
   - Name
   - Price
*/

typedef struct
{
    unsigned char uid[4];
    char name[10];
    int price;
}Product;


/* Product Database
   Here we store 5 RFID cards with their UID and price */

Product products[5] =
{
    {{0x77,0x0F,0x86,0x25},"A",50},
    {{0x22,0x3E,0xC3,0xE9},"B",70},
    {{0x3A,0xF0,0x28,0x03},"C",90},
    {{0xA2,0x34,0xB7,0xE9},"D",40},
    {{0xF7,0xF3,0x7E,0xA2},"E",60}
};


/* Variables used for cart calculation */

int total_bill = 0;     // total bill amount
int item_count = 0;     // number of items scanned
int product_index = -1; // index of product matched


/* ----------------------------------------------------
   Function to print UID bytes in HEX format on LCD
   Example: A2 34 B7 E9
---------------------------------------------------- */

void LCD_PrintHex(unsigned char num)
{
    char hex[3];

    hex[0] = "0123456789ABCDEF"[num >> 4];   // extract upper 4 bits
    hex[1] = "0123456789ABCDEF"[num & 0x0F]; // extract lower 4 bits
    hex[2] = '\0';

    KM_Lcd_Write_Str(hex);   // print hex string
}


/* ----------------------------------------------------
   Function to print integer number on LCD
---------------------------------------------------- */

void LCD_PrintNumber(int num)
{
    char buf[6];
    int k = 0;

    if(num == 0)
    {
        KM_Lcd_Write_Data('0');
        return;
    }

    /* Convert integer into characters */

    while(num > 0)
    {
        buf[k++] = (num % 10) + '0';
        num /= 10;
    }

    /* Print digits in reverse order */

    for(j = k-1; j >= 0; j--)
    {
        KM_Lcd_Write_Data(buf[j]);
    }
}



/* ----------------------------------------------------
   MAIN FUNCTION
---------------------------------------------------- */

int main(void)
{

    /* Hardware Initialization */

    KM_Systick_Init();   // initialize system timer

    KM_GPIO_Init(PORTA);
    KM_GPIO_Init(PORTB);
    KM_GPIO_Init(PORTC);

    /* LCD GPIO configuration */

    GPIOB_MODER &= ~(0x00030FFF);
    GPIOB_MODER |= 0x00010555;
    GPIOB_ODR &= ~(0x13F);

    /* LED and Buzzer pin configuration */

    KM_GPIO_Pin_Mode(PORTB, RED_LED, OUT);
    KM_GPIO_Pin_Mode(PORTB, GREEN_LED, OUT);
    KM_GPIO_Pin_Mode(PORTB, BUZZER, OUT);

    KM_GPIO_Pin_Mode(PORTC, SW_ENT, IN);

    /* Initialize LCD and RFID module */

    KM_Lcd_Init();
    RC522_Init();

    /* Turn OFF LEDs initially */

    KM_GPIO_Write_Pin(PORTB, GREEN_LED, SET);
    KM_GPIO_Write_Pin(PORTB, RED_LED, SET);


    /* Welcome Display */

    KM_Lcd_Write_Cmd(0x01);   // clear LCD

    for(i=0; str[i] != '\0'; i++)
    {
        if(i == 0)
            KM_Lcd_Write_Cmd(0x83);

        if(i == 10)
            KM_Lcd_Write_Cmd(0xC0);

        KM_Lcd_Write_Data(str[i]);
    }

    KM_Mdelay(1500);


    KM_Lcd_Write_Cmd(0x01);
    KM_Lcd_Write_Str("SMART TROLLEY");

    KM_Mdelay(1500);

    KM_Lcd_Write_Cmd(0x01);
    KM_Lcd_Write_Str("READY TO SCAN");



/* ----------------------------------------------------
   Main Loop
---------------------------------------------------- */

    while(1)
    {

        match = 0;

        /* Detect if RFID card is present */

        status = RC522_Request(0x26, TagType);

        if(status == MI_OK)
        {

            /* Read UID of card */

            status = RC522_Anticoll(Scanned_UID);

            if(status == MI_OK)
            {

                /* Display scanned UID */

                KM_Lcd_Write_Cmd(0x01);
                KM_Lcd_Write_Str("UID:");
                KM_Lcd_Write_Cmd(0xC0);

                for(i=0;i<4;i++)
                {
                    LCD_PrintHex(Scanned_UID[i]);
                    KM_Lcd_Write_Str(" ");
                }

                KM_Mdelay(2000);


                /* Identify product by matching UID */

                product_index = -1;

                for(p=0; p<5; p++)
                {
                    match = 1;

                    for(i=0;i<4;i++)
                    {
                        if(Scanned_UID[i] != products[p].uid[i])
                        {
                            match = 0;
                            break;
                        }
                    }

                    if(match)
                    {
                        product_index = p;
                        break;
                    }
                }


                KM_Lcd_Write_Cmd(0x01);

                /* If product found */

                if(product_index != -1)
                {

                    total_bill += products[product_index].price; // add price
                    item_count++;                                // increase item count

                    KM_Lcd_Write_Str("Item:");
                    KM_Lcd_Write_Str(products[product_index].name);

                    KM_Lcd_Write_Cmd(0xC0);
                    KM_Lcd_Write_Str("Price:");
                    LCD_PrintNumber(products[product_index].price);


                    /* Green LED and buzzer indicate valid scan */

                    KM_GPIO_Write_Pin(PORTB, GREEN_LED, RESET);
                    KM_GPIO_Write_Pin(PORTB, BUZZER, SET);

                    KM_Mdelay(1000);

                    KM_GPIO_Write_Pin(PORTB, GREEN_LED, SET);
                    KM_GPIO_Write_Pin(PORTB, BUZZER, RESET);

                    KM_Mdelay(1500);


                    /* Show cart details */

                    KM_Lcd_Write_Cmd(0x01);
                    KM_Lcd_Write_Str("Items:");
                    LCD_PrintNumber(item_count);

                    KM_Lcd_Write_Cmd(0xC0);
                    KM_Lcd_Write_Str("Total:");
                    LCD_PrintNumber(total_bill);

                    KM_Mdelay(1500);

                }

                /* If card is not in product database */

                else
                {

                    KM_Lcd_Write_Str("INVALID CARD");

                    KM_GPIO_Write_Pin(PORTB, RED_LED, RESET);
                    KM_GPIO_Write_Pin(PORTB, BUZZER, SET);

                    KM_Mdelay(1500);

                    KM_GPIO_Write_Pin(PORTB, RED_LED, SET);
                    KM_GPIO_Write_Pin(PORTB, BUZZER, RESET);
                }


                /* Wait until card removed */

                while(RC522_Request(0x26, TagType) == MI_OK);
                KM_Lcd_Write_Cmd(0x01);
                KM_Lcd_Write_Str("READY TO SCAN");

            }
        }

    }

}