
#include "HAL/KEYPAD/KEYPAD.h"
#include "HAL/LCD/LCD.h"
#include <util/delay.h>
#include "uitils/BIT_MATH.h"

float evaluate (long int operand1, long int operand2, long int sign);


int main ()
{
	/* Initialize LCD*/
	LCD_vInit();
	LCD_Send_String("HEllO");
	_delay_ms(1000);
	LCD_Clear();

	/* Variables to hold the 2 numbers, the applied sign & number of loops to know which kind of char is next */
	long int operand1 = 0, operand2 = 0;
	long int sign = 0, loop = 1;
	while (1)
	{
		/* Get key value from keypad */
		int key = Get_Key_Pressed();
		/* Key is number */
		if ( key >=0 && key <10)
		{
			/* First time to loop is the first number */
			if (loop == 1)
			{
				LCD_Gotoxy(0,0);
				operand1 =10*operand1 + key;

			}
			/* Third time to loop is the second number */
			else if (loop == 2)
			{
				operand2 =10*operand2 + key;
			}
			/* Display equivalent char by adding ASCII of zero */
			LCD_Send_Data(key + '0');
		}

		/* Key is '/' sign */
		else if (key == 10)
		{
			sign = '/';
			LCD_Send_Data('/');
		}

		/* Key is '*' sign */
		else if (key == 11)
		{
			sign = '*';
			LCD_Send_Data('*');
		}

		/* Key is '-' sign */
		else if (key == 12)
		{
			sign = '-';
			LCD_Send_Data('-');
		}

		/* Key is '+' sign */
		else if (key == 13)
		{
			sign = '+';
			LCD_Send_Data('+');
		}

		/* Key is 'ON/C' [Clear] */
		else if (key == 14)
		{
			/* Clear Display & clear values */
			LCD_Clear();
			operand1 = 0;
			operand2 = 0;
			sign = 0;
			loop = 1;
		}

		/* Key is '=' sign */
		else if (key == 15)
		{
			LCD_Gotoxy(2,0);
			LCD_Send_String("= ");
			/* Get result of the 2 numbers & the desired operation */
			float result = evaluate(operand1,operand2, sign);
			/* Indicates error of division by zero */
			if (result == 'E')
			{
				LCD_Send_String("Wrong entry!");

			}
			else
			{
				LCD_Gotoxy(2,2);
				LCD_Send_Float(result);
				loop = 1;

			}
		}
		if(sign != 0)
		{
			loop++;
		}
		_delay_ms(100);
	}

}

float evaluate (long int operand1, long int operand2, long int sign)
{
	/* Division by Zero returns error */
	if (sign == '/' && operand2 == 0)	return 'E';
	switch(sign)
	{
	case '+':	return operand1 + operand2;		// Addition operation
	case '-':	return operand1 - operand2;		// Subtraction operation
	case '*':	return operand1 * operand2;		// Multiplication operation
	case '/':	return (float)operand1 / operand2;		// Division operation
	}
}
