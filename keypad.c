/*
 * keypad.c
 *
 * Created: 27/05/2023 05:47:15
 *  Author: emada
 */ 
#define F_CPU 16000000
#include "KEYPAD.h"
#include <util/delay.h>

const uint8 keypad[4][4] = { '7','8','9','/',
							 '4','5','6','*',
							 '1','2','3','-',
							 'c','0','=','+' };

#define keypad_coulm_init	0
#define keypad_coulm_final	3
#define keypad_row_init		4
#define keypad_row_final	7


void KEYPAD_INIT()
{
	DIO_Setpindir(KEYPAD_PORT,col_0,DIO_PIN_OUTPUT);
	DIO_Setpindir(KEYPAD_PORT,col_1,DIO_PIN_OUTPUT);
	DIO_Setpindir(KEYPAD_PORT,col_2,DIO_PIN_OUTPUT);
	DIO_Setpindir(KEYPAD_PORT,col_3,DIO_PIN_OUTPUT);
	
	
	
	DIO_Setpindir(KEYPAD_PORT,row_0,DIO_PIN_INPUT);
	DIO_Setpindir(KEYPAD_PORT,row_1,DIO_PIN_INPUT);
	DIO_Setpindir(KEYPAD_PORT,row_2,DIO_PIN_INPUT);
	DIO_Setpindir(KEYPAD_PORT,row_3,DIO_PIN_INPUT);
	
				  
	lcd_pull_up(KEYPAD_PORT,row_0);
	lcd_pull_up(KEYPAD_PORT,row_1);
	lcd_pull_up(KEYPAD_PORT,row_2);
	lcd_pull_up(KEYPAD_PORT,row_3);
	
	
	DIO_Setpinval(KEYPAD_PORT,col_0,DIO_PIN_HIGH);
	DIO_Setpinval(KEYPAD_PORT,col_1,DIO_PIN_HIGH);
	DIO_Setpinval(KEYPAD_PORT,col_2,DIO_PIN_HIGH);
	DIO_Setpinval(KEYPAD_PORT,col_3,DIO_PIN_HIGH);
	
}
uint8 keypad_get_pressed_buttom()
{
	uint8 loc_col = 0;
	uint8 loc_row = 0;
	uint8 pressed_buttom = 0;
	uint8 temp = 0;
	for (loc_col = keypad_coulm_init ;loc_col<= keypad_coulm_final; loc_col++)
	{
		DIO_Setpinval(KEYPAD_PORT,loc_col,DIO_PIN_LOW);
		
		for (loc_row = keypad_row_init ; loc_row <= keypad_row_final ; loc_row++)
		{
			//if(GET_BIT(loc_col,loc_row) == 0)
			//{
				//return keypad[loc_col][loc_row];
			//}
			DIO_Readpin(KEYPAD_PORT,loc_row,&temp);
			
			if (!temp)
			{
				pressed_buttom = keypad[loc_row - keypad_row_init][loc_col - keypad_coulm_init];
				while(!temp)
				{
					DIO_Readpin(KEYPAD_PORT,loc_row,&temp);
				}
				_delay_ms(10);
				
				
			}
			
		}
		DIO_Setpinval(KEYPAD_PORT,loc_col,DIO_PIN_HIGH);
	}
	return pressed_buttom;
}

uint8 keypad_write_intger(uint8 val)
{
	uint8 intger = 0;
	
	if (val <= '9')
	{
		intger = val - 48 ;
	}
	return intger ;
}

uint8 keypad_get_num(uint8 ch)
{
	{
		int num = 0;
		switch(ch)
		{
			case '0':
			num = 0;
			break;
			case '1':
			num = 1;
			break;
			case '2':
			num = 2;
			break;
			case '3':
			num = 3;
			break;
			case '4':
			num = 4;
			break;
			case '5':
			num = 5;
			break;
			case '6':
			num = 6;
			break;
			case '7':
			num = 7;
			break;
			case '8':
			num = 8;
			break;
			case '9':
			num = 9;
			break;
			case 'C':
			lcd_write_cmd(0x01);
			//num = Error;
			break;  //this is used as a clear screen and then reset by setting error
			default:
			//DispError(0);
			//num = Error;
			break;       //it means wrong input
		}
		return num;
	}
}

////////////////////////////////// chat GPT ///////////////////////////////////////////
#define KEYPAD_PORT PORTD
#define KEYPAD_PIN PIND
#define KEYPAD_DDR DDRD

char password[] = "1234";  // Define your desired password
uint8 password_index = 0;

void keypad_init() {
	KEYPAD_DDR = 0xF0;  // Rows are output, columns are input
	KEYPAD_PORT = 0xFF; // Enable pull-up resistors on columns
}

char keypad_scan() {
	uint8 row, col;

	for (col = 0; col < 4; col++) {
		KEYPAD_PORT = ~(1 << (col + 4));
		_delay_ms(2);

		for (row = 0; row < 4; row++) {
			if (!(KEYPAD_PIN & (1 << row))) {
				while (!(KEYPAD_PIN & (1 << row))); // Wait for key release
				return (row * 4 + col + 1);         // Return the key pressed
			}
		}
	}

	return 0;  // No key pressed
}