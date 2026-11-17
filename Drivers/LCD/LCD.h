/***************************************************
Name : R.VYSHNAVI
KMID : KM62BEAI09
File : LCD.h
***************************************************/
#define LCD_D4 0
#define LCD_D5 1
#define LCD_D6 2
#define LCD_D7 3
#define LCD_RS 4
#define LCD_RW 5 
#define LCD_EN 8

void KM_Lcd_Pin_Init(int port, int , int , int , int, int, int, int);  
//initializing Port B pins associated to LCD Example: KM_Lcd_Pin_Init(LCD_PORT, LCD_D4, LCD_D5, LCD_D6, LCD_D7, LCD_RS, LCD_RW, LCD_EN);
void KM_Lcd_Init(void);  //Flow chart
void KM_Lcd_Write_Data(unsigned char );
void KM_Lcd_Write_Cmd(unsigned char );
void write_low_nibble(unsigned char );
void write_high_nibble(unsigned char  );
void KM_Lcd_Write_Str(char *);
