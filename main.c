/*
 * door_locker.c
 *
 * Created: 30/09/2023 17:44:04
 * Author : emada
 */ 

#include "lcd.h"
#include "keypad.h"
#include <string.h>
#include <util/delay.h>


int main(void)
{
	lcd_init();
	KEYPAD_INIT();
	
	
	
	uint8 pressed_value ;
	//uint8 pressed_index = 0 ;
	uint8 pass_counter=0;//the counter of the characters of the password



	lcd_write_string("set admin pass");
	lcd_clear();
	uint8 buffer1[5]={0,0,0,0,0};//the array where it stored the password
	uint8 buffer2[5]={0,0,0,0,0} ;
	while (pass_counter<4)//loop till the user finish inserting the pass
	{
		pressed_value = 0;//return the variable that holds the pressed key from keypad to its initial value
		while (pressed_value == 0)//repeat till the user press any key
		{
			pressed_value = keypad_get_pressed_buttom();//if the user pressed any button in keypad save the value in key_pressed
		}

		buffer1[pass_counter]=pressed_value;//add the entered character to the pass array
		lcd_write_data(pressed_value);//print the entered character
		pass_counter++;//increase the characters count
		if (pass_counter == 4)
		{
			buffer1[pass_counter] ='\0';
		}
	}
	lcd_clear();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row
	lcd_write_string("Pass Saved");// show pass saved message
	_delay_ms(500);//Halt the system for the given time in (ms)
	lcd_clear();//remove all previously printed characters on the LCD and move the cursor to the first column of the first row

	/********************************* setting guest password **********************************************/
	pass_counter=0;//reset password counter which count the characters of the pass
	lcd_write_string("Set Guest Pass");//printing the set admin password menu
	lcd_go_to(1,0);
	//lcd_write_string("Guest Pass:");
	//lcd_clear();
	while (pass_counter<4)//loop till the user finish inserting the pass
	{
		
		pressed_value = 0;//return the variable that holds the pressed key from keypad to its initial value
		while (pressed_value == 0)//repeat till the user press any key
		{
			pressed_value = keypad_get_pressed_buttom();//if the user pressed any button in keypad save the value in key_pressed
		}

		buffer2[pass_counter]=pressed_value;//add the entered character to the pass array
		lcd_write_data(pressed_value);//print the entered character
		pass_counter++;//increase the characters count
		if (pass_counter == 4)
		{
			buffer2[pass_counter] ='\0';
		}
	}
	if (strcmp(buffer1,buffer2) == 0)
	{
		lcd_clear();
		lcd_write_string("right password");
	}else
	{
		lcd_clear();
		lcd_write_string("wrong password");
	}
	
	while (1)
	{
		
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	lcd_write_string("ins. first pass");
	lcd_go_to(1,0);
	//pressed_value = keypad_scan();
	//lcd_write_data(pressed_value);
    while (1) 
    {
		pressed_value = keypad_get_pressed_buttom(); // Get the pressed key
		if (pressed_value != '='  && pressed_value != '+') {
			// && pressed_value != '+'
			// Handle numeric keys and operators
			if (pressed_value >= '*' && pressed_value <= '9') {
				//buffer_1[counter] = '=';
				buffer1[pressed_index] = pressed_value;
				lcd_write_data(pressed_value);
				pressed_index++;
				if (pressed_index == 4)
					{
						buffer1[4] = '\0';
						lcd_clear();
						pressed_index = 0 ;
					}
		}
			}
			else if(pressed_value == '+')
			{	
			lcd_write_string("insert password");
			lcd_go_to(1,0);
			//lcd_write_data(pressed_value);
			//lcd_clear();
			//lcd_write_string("ins. sec pass");
			//lcd_go_to(1,0);
			//if (pressed_value != '=' && pressed_value != '+') {
				// Handle numeric keys and operators
				if (pressed_value >= '*' && pressed_value <= '9') {
					buffer2[pressed_index] = pressed_value;
					//lcd_go_to(1,pressed_index-1);
					lcd_write_data(pressed_value);
					pressed_index++;
					if (pressed_index == 4)
					{
						buffer2[4] = '\0';
						lcd_clear();
						pressed_index = 0 ;
					}
			
			
			}
	}else  if(pressed_value == '=')
	{
		if (strcmp(buffer1, buffer2) == 0)
		{
			lcd_write_string("right password");
		}else
		{
			lcd_write_string("wrong password");
		}
	}
		/*
		if (pressed_value >= '*' && pressed_value <= '9') {
			//buffer_1[counter] = '=';
			buffer2[pressed_index+1] = pressed_value;
			lcd_write_data(pressed_value);
			pressed_index++;
		}
		else if (pressed_index == '4')
		{
			buffer2[4] = '\0';
			lcd_clear();
		}*/
		/*
		pressed_value = keypad_get_pressed_buttom();
		lcd_write_data(pressed_value);
		while(i != '\0')
		{
			buffer2[i] = pressed_value;
			i++;
		}
		for (i=0 ;i<5 ;i++)
		{
			if (buffer1[i] == buffer2[i] && (i = '\0'))
			{
				lcd_clear();
				lcd_write_string("right password");
			}
		}*
    }
			}
			

*/