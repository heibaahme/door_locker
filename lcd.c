/*
 * lcd.c
 *
 * Created: 26/05/2023 06:40:19
 *  Author: emada
 */ 
#define F_CPU 16000000
#include <util/delay.h>

#include "lcd.h"

void lcd_init(void)
{
	#if (LCD_MOOD == 8)
	{
		DIO_Setpindir(lcd_8_bit_CMD_mood,LCD_RS,DIO_PIN_OUTPUT);
		DIO_Setpindir(lcd_8_bit_CMD_mood,LCD_Rw,DIO_PIN_OUTPUT);
		DIO_Setpindir(lcd_8_bit_CMD_mood,LCD_E,DIO_PIN_OUTPUT);
		
		DIO_Setportdir(lcd_8_bit_DATA_mood,DIO_PORT_OUTPUT);
		_delay_ms(100);
		
		lcd_write_cmd(0x38);
		lcd_write_cmd(0x0E);
		lcd_write_cmd(0x01);
		
	}
	#elif (LCD_MOOD == 4)
	{
		DIO_Setpindir(lcd_4_bit_CMD_mood,LCD_RS,DIO_PIN_OUTPUT);
		DIO_Setpindir(lcd_4_bit_CMD_mood,LCD_Rw,DIO_PIN_OUTPUT);
		DIO_Setpindir(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_OUTPUT);
	
		DIO_Setpindir(lcd_4_bit_DATA_mood,DIO_PIN4,DIO_PIN_OUTPUT);
		DIO_Setpindir(lcd_4_bit_DATA_mood,DIO_PIN5,DIO_PIN_OUTPUT);
		DIO_Setpindir(lcd_4_bit_DATA_mood,DIO_PIN6,DIO_PIN_OUTPUT);
		DIO_Setpindir(lcd_4_bit_DATA_mood,DIO_PIN7,DIO_PIN_OUTPUT);
		_delay_ms(100);
		
		lcd_write_cmd(0x33);
		lcd_write_cmd(0x32);
		lcd_write_cmd(0x28);
		
		lcd_write_cmd(0x0C);
		lcd_write_cmd(0x01);
		lcd_write_cmd(0x06);
		lcd_write_cmd(0x02);
		
	}
	
	
	#endif	
}
void lcd_write_string(uint8* string)
{
	uint8 i =0;
	while(string[i] != '\0')
	{
		lcd_write_data(string[i]);
		i++;
	}
}
void lcd_write_cmd(uint8 cmd)
{
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_RS,DIO_PIN_LOW);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_Rw,DIO_PIN_LOW);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_LOW);
	
	PORTA = (cmd & 0xF0) | (PORTA & 0x0F);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_LOW);
	
	PORTA = (cmd << 4) | (PORTA & 0x0F);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_LOW);
	_delay_ms(5);
	
}
void lcd_write_data(uint8 data)
{
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_RS,DIO_PIN_HIGH);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_Rw,DIO_PIN_LOW); 
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_LOW);
	
	PORTA = (data & 0xF0) | (PORTA & 0x0F);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_LOW);
	
	PORTA = (data << 4) | (PORTA & 0x0F);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_Setpinval(lcd_4_bit_CMD_mood,LCD_E,DIO_PIN_LOW);
	_delay_ms(5);
}
void lcd_goto(uint8 row,uint8 col)
{
	uint8 pos[2]= {0x80,0xc0};
	lcd_write_cmd(pos[row+col]);	
}
void lcd_clear(void)
{
	lcd_write_cmd(0x01); 
}
void lcd_pull_up(uint8 port,uint8 pin)
{
	switch(port)
	{
		case DIO_PORTA :
			SET_BIT(PORTA,pin);
			break;
		case DIO_PORTB :
			SET_BIT(PORTB,pin);
			break;
		case DIO_PORTC :
			SET_BIT(PORTC,pin);
			break;
		case DIO_PORTD :
			SET_BIT(PORTD,pin);
			break;
		default :
		break;
	}
}


uint8 str_to_int(uint8 *str)
{
	uint8 res = 0;
	for(uint8 i =0 ;str[i]!='\0';++i)
	{
		res = res*10 +str[i]-'0' ;
	}
	return res;
}

void lcd_send_spical_char(uint8* ch_arr, uint8 bloca_num, uint8 x_position, uint8 y_position)
{
	uint8 counter ;
	/* calculate the starting address in cgram for the reqiured patterns number */
	uint8 CGRAM_ADRESS = bloca_num *8 ;
	/*set bit 6 and clear bit 7*/
	SET_BIT(CGRAM_ADRESS,6);
	/*set cgram address command*/
	lcd_write_cmd(CGRAM_ADRESS);
	/*Draw the pattern inside cgram*/
	for (counter =0;counter<8;counter++)
	{
		lcd_write_data(ch_arr[counter]);
	}
	/*back to ddram*/
	lcd_go_to(x_position,y_position);
	/*display the drawn pattern*/
	lcd_write_data(bloca_num);
	
}

void lcd_go_to(uint8 row, uint8 col) {
	// Define the starting DDRAM addresses for each line of a 2x16 LCD
	static uint8 ddram_address[] = {0x00, 0x40, 0x10, 0x50};

	// Calculate the DDRAM address based on row and col
	uint8 address = col + ddram_address[row];

	// Set the cursor position
	lcd_write_cmd(0x80 | address);
}

void lcd_write_intger(sint32 num)
{
	if (num<0)
	{
		lcd_write_data('-');
		num *= -1;
	}
	while(num>0)
	{
		sint32 y = (y*10) + (num % 10) ;
		num /= 10;
		while(y>1)
		{
			lcd_write_data((y%10) + 48);
			y /= 10;
		}
	}
	
}