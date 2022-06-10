
#include <avr/delay.h>
#include "../../uitils/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "LCD.h"
#define F_CPU 8000000UL
/***************************************************************************************/
/********************************** Macros *********************************************/
/***************************************************************************************/



#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* return cursor to first position on first line                   */
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0x80          // set cursor position

/***************************************************************************************/
/********************************** Constant Variables *********************************/
/***************************************************************************************/

/* LCD MAPPING PINS */
#define LCD_GROUP_DATA GROUPA
#define LCD_GROUP_CONTROL GROUPB
#define LCD_RS_PIN PIN_0
#define LCD_E_PIN PIN_1

void LCD_vInit(void)
{
   DIO_SetGroupDirection(LCD_GROUP_DATA,0xFF);
   DIO_SetPinDirection(LCD_GROUP_CONTROL,LCD_RS_PIN,OUTPUT);
   DIO_SetPinDirection(LCD_GROUP_CONTROL,LCD_E_PIN,OUTPUT);

    // wait for 30 ms
    _delay_ms(30);

    LCD_Send_Command(lcd_Home);
    _delay_ms(15);

    LCD_Send_Command(lcd_FunctionSet8bit);
    _delay_ms(1);

    LCD_Send_Command(lcd_DisplayOn);
    _delay_ms(1);

    LCD_Send_Command(lcd_Clear);
    _delay_ms(2);

    LCD_Send_Command(lcd_EntryMode);
    _delay_ms(15);


}



void LCD_Send_Command(u8 CommandID)
{
    DIO_SetPinValue(LCD_GROUP_CONTROL,LCD_RS_PIN,LOW);
    _delay_us(1);
    DIO_SetPinValue(LCD_GROUP_CONTROL,LCD_E_PIN,HIGH);
    _delay_us(1);
     DIO_SetGroupValue(LCD_GROUP_DATA,CommandID);
     _delay_us(1);
     DIO_SetPinValue(LCD_GROUP_CONTROL,LCD_E_PIN,LOW);
     _delay_ms(5);
     DIO_SetPinValue(LCD_GROUP_CONTROL,LCD_E_PIN,HIGH);
     _delay_ms(10);

}


void LCD_Send_Data(char dataID)
{
    DIO_SetPinValue(LCD_GROUP_CONTROL,LCD_RS_PIN,HIGH);
    _delay_us(1);
    DIO_SetPinValue(LCD_GROUP_CONTROL,LCD_E_PIN,HIGH);
    _delay_us(1);
     DIO_SetGroupValue(LCD_GROUP_DATA,dataID);
     _delay_us(1);
     DIO_SetPinValue(LCD_GROUP_CONTROL,LCD_E_PIN,LOW);
     _delay_ms(5);
     DIO_SetPinValue(LCD_GROUP_CONTROL,LCD_E_PIN,HIGH);
     _delay_ms(10);

}

void LCD_Send_String(char * ptr)
{

    while (*ptr != '\0')
    {
        LCD_Send_Data(*ptr);
        ptr++;
    }
}

void LCD_Clear()
{
    LCD_Send_Command(lcd_Clear);
}
void LCD_Gotoxy (unsigned char ROWS , unsigned char COL){
	if (COL>=0 && COL<=15 && ROWS>=1 && ROWS<=2){
		switch (ROWS){
	case 1 :
		LCD_Send_Command(((COL+ 0x00)|(0x80)));
		break ;
	case  2:
			LCD_Send_Command(((COL+ 0x40)|(0x80)));
			break ;
	default :
		break;

	}
	}}
	void LCD_voidWriteNumber(long  int Copy_u32Number)
	{
		char Local_u8DisplayNumber;
		char Local_Au8Array[16];
		signed char Local_s8Counter = 0 ;

		while(Copy_u32Number != 0)
		{
			Local_u8DisplayNumber = Copy_u32Number % 10 ;
			Local_Au8Array[Local_s8Counter] = Local_u8DisplayNumber;
			Local_s8Counter++;
			Copy_u32Number/=10;
		}
		Local_s8Counter = Local_s8Counter-1;
		while(Local_s8Counter >= 0)
		{
			LCD_Send_Data(Local_Au8Array[Local_s8Counter]+0x30);
			Local_s8Counter--;
		}
	}



	void LCD_Send_Num(int num)
	{
		int txt[10] = {0};					// Array holds the number in digits
		int i = 0;						// Iterator
		if(num == 0)
		{
			LCD_Send_Data('0');
			return;
		}
		for(i = 0; num != 0; i++)
		{
			txt[i] = num%10 +48;				// Get the ASCII code of the rightmost digit
			num = num/ 10;					// Remove the rightmost digit
		}
		i--;
		while(i >= 0 )
		{
			LCD_Send_Data(txt[i]);				// Display the digits in reverse order
			i--;
		}
	}
	void LCD_Send_Float(float num)
	{
		f32 num2ndPart;
		s32 num1stPart = (u32) num;
		LCD_Send_Num(num1stPart);

		num2ndPart = (f32) num-num1stPart;
		if (num < 0) {
			num2ndPart = (f32) (-1) * (num2ndPart);
		}
		if(((f32)num-num1stPart)>0)
		{
				LCD_Send_Data('.');
				u8 zero_flag=0,temp;
				for (u8 i = 1; i <= 4; i++) {
					num2ndPart = num2ndPart * 10;
					 temp = (u8) num2ndPart;
					if((temp==0)&&zero_flag&&i<=3)
					{
						LCD_Send_Data('0');
						break;
					}
					else if(zero_flag&&(temp>0))
					{
						if(temp>=4)
						LCD_Send_Data('1');
						else
						LCD_Send_Data('0');
						break;
					}
					else if(temp==0)
					{
						zero_flag=1;
					}
					else
					{
						LCD_Send_Data(temp + '0');
					}
					num2ndPart = (f32) (num2ndPart - temp);
				}
		}
	}



