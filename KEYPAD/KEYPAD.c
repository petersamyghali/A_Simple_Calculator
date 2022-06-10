/*
 * KEYPAD.c
 *
 *  Created on: Sap 24, 2021
 *      Author: Peter
 */
#include <avr/delay.h>
#include "../../uitils/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "KEYPAD.h"
#define KEYPAD_GROUP GROUPC
unsigned char KEYPAD_Arr [4][4]={
		{7,8,9,10},
		{4,5,6,11},
		{1,2,3,12},
		{14,0,15,13}
};

unsigned char Get_Key_Pressed ()
{
while(1){
for (u8 i=0;i<4;i++){//Activate C1 Then C2 ... etc
	DIO_SetGroupDirection(KEYPAD_GROUP,(0b00010000<<i));//define Columns PINs input Pulled UP
	DIO_SetGroupValue(KEYPAD_GROUP,~(0b00010000<<i));
	_delay_ms(100);
	for (u8 y=0 ;y<4 ; y++){//Read R1 to R4(if any Row is low=key is pressed)
		if(DIO_GetPinValue(KEYPAD_GROUP,y)==0)
		{_delay_ms(100);

	return KEYPAD_Arr[y][i];
}}

}}
}
