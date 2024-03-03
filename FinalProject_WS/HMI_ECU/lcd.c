 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Youssef Abuzeid
 *
 *******************************************************************************/

#include "gpio.h"
#include "lcd.h"
#include "util\delay.h"
#include "common_macros.h"
#include <stdlib.h>


/*
 * Description :
 * Function responsible for sending a command for the LCD
 */
void LCD_sendCommand(uint8 a_Command){
	/*
	 * Write 0 to RS
	 * */
	GPIO_writePin(LCD_PORT_CONTROL,LCD_RS,LOGIC_LOW);
	/*
	 * Delay 1 us as tas=50ns
	 * */
	_delay_ms(1);
	/*
	 * Enable
	 * */
	GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_HIGH);
	_delay_ms(1);
	/*
	 *
	 *  Send The command
	 * */
#if(NUMBER_OF_BITS==8)
	GPIO_writePort(LCD_PORT_DATA,a_Command);
	/*
	 * Delay 1 us as tdsw=100ns
	 */
	_delay_ms(1);
	/*
	 * Disable
	 */
	GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_LOW);
	/*
	 * Delay 1 us as th=13ns
	 */
	_delay_ms(1);
#elif(NUMBER_OF_BITS==4)
	GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_1,GET_BIT(a_Command,4));
	GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_2,GET_BIT(a_Command,5));
	GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_3,GET_BIT(a_Command,6));
	GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_4,GET_BIT(a_Command,7));

	_delay_ms(1);

	GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_LOW);

	_delay_ms(1);
	GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_HIGH);

	_delay_ms(1);

	GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_1,GET_BIT(a_Command,0));
	GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_2,GET_BIT(a_Command,1));
	GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_3,GET_BIT(a_Command,2));
	GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_4,GET_BIT(a_Command,3));

	_delay_ms(1);

	GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_LOW);

	_delay_ms(1);
#endif



}

/*
 * Description :
 * Function responsible for displaying a character on the LCD
 */
void LCD_displayCharacter(uint8 a_Char){
	/*
		 * Write 0 to RS
		 * */
		GPIO_writePin(LCD_PORT_CONTROL,LCD_RS,LOGIC_HIGH);
		/*
		 * Delay 1 us as tas=50ns
		 * */
		_delay_ms(1);
		/*
		 * Enable
		 * */
		GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_HIGH);
		_delay_ms(1);
		/*
		 *
		 *  Send The command
		 * */
	#if(NUMBER_OF_BITS==8)
		GPIO_writePort(LCD_PORT_DATA,a_Char);
		/*
		 * Delay 1 us as tdsw=100ns
		 */
		_delay_ms(1);
		/*
		 * Disable
		 */
		GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_LOW);
		/*
		 * Delay 1 us as th=13ns
		 */
		_delay_ms(1);
	#elif(NUMBER_OF_BITS==4)
		GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_1,GET_BIT(a_Char,4));
		GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_2,GET_BIT(a_Char,5));
		GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_3,GET_BIT(a_Char,6));
		GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_4,GET_BIT(a_Char,7));

		_delay_ms(1);

		GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_LOW);

		_delay_ms(1);
		GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_HIGH);

		_delay_ms(1);

		GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_1,GET_BIT(a_Char,0));
		GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_2,GET_BIT(a_Char,1));
		GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_3,GET_BIT(a_Char,2));
		GPIO_writePin(LCD_PORT_DATA,LCD_DATA_PIN_4,GET_BIT(a_Char,3));

		_delay_ms(1);

		GPIO_writePin(LCD_PORT_CONTROL,LCD_EN,LOGIC_LOW);

		_delay_ms(1);
	#endif



}

/*
 * Description :
 * Function responsible for initialization of the LCD
 */

void LCD_init(void){
	/*
	 *  Setup RS & EN as output PINS
	 */
	GPIO_setupPinDirection(LCD_PORT_CONTROL,LCD_RS,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_PORT_CONTROL,LCD_EN,PIN_OUTPUT);
	/*
	 *  Setup the data port as output port
	 */
#if(NUMBER_OF_BITS==8)
	GPIO_setupPortDirection(LCD_PORT_DATA,PORT_OUTPUT);


#elif(NUMBER_OF_BITS==4)
	GPIO_setupPinDirection(LCD_PORT_DATA,LCD_DATA_PIN_1,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_PORT_DATA,LCD_DATA_PIN_2,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_PORT_DATA,LCD_DATA_PIN_3,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_PORT_DATA,LCD_DATA_PIN_4,PIN_OUTPUT);
#endif
	/*
	 * 20 ms delay so that the lcd have the time to power on
	 */
	_delay_ms(20);
	/*
	 * set it up as Two line 8 bit mode or 4 bit mode
	 */
#if(NUMBER_OF_BITS==8)
	LCD_sendCommand(LCD_COMMAND_TWO_LINE_8_BIT);

#elif(NUMBER_OF_BITS==4)
	LCD_sendCommand(LCD_COMMAND_4_BIT_INIT_1);
	LCD_sendCommand(LCD_COMMAND_4_BIT_INIT_2);
	LCD_sendCommand(LCD_COMMAND_TWO_LINE_4_BIT);
#endif


	/*
	 * close the cursor
	 */
	LCD_sendCommand(LCD_COMMAND_CURSOR_OFF);
	/*
	 * clear the screen
	 */
	LCD_sendCommand(LCD_COMMAND_CLEAR_SCREEN);
}

/*
 * Description :
 * Function responsible for displaying a String on the LCD
 */
void LCD_displayString(const char * a_str){
	uint8 counter=0;
	while(a_str[counter]!='\0'){
		LCD_displayCharacter(a_str[counter]);
		counter++;
	}
}


/*
 * Description :
 * Function responsible for moving the cursor to a certain position
 */
void LCD_moveCursor(uint8 a_row,uint8 a_col){
	uint8 Address=0;
	switch(a_row){
	case 0:
		Address=0x80|a_col;
		break;
	case 1:
		Address=(a_col+0x40)|0x80;
		break;
	case 2:
		Address=(a_col+0x10)|0x80;
		break;
	case 3:
		Address=(a_col+0x50)|0x80;
		break;

	}
	LCD_sendCommand(Address);
}

/*
 * Description :
 * Function responsible for displaying a String on the LCD in a certain position
 */
void LCD_displayStringRowCol(const char * a_str,uint8 a_row,uint8 a_col){
	LCD_moveCursor(a_row,a_col);
	LCD_displayString(a_str);
}
/*
 * Description :
 * Function responsible for clearing the LCD
 */
void LCD_clearScreen(void){
	LCD_sendCommand(LCD_COMMAND_CLEAR_SCREEN);
}

/*
 * Description :
 * Function responsible for displaying an integer on the LCD
 */
void LCD_intgerToString(uint16 a_num){
	char buff[16];
	itoa(a_num,buff,10);
	LCD_displayString(buff);
}
/*
 * Description :
 * Function responsible for creating a custom character on the LCD
 */
void LCD_CreateCustomCharacter(uint8 *pucPattern,const uint8 cLocation)
{
    uint8 iLoop=0;
    LCD_sendCommand(0x40+(cLocation*8)); //Send the Address of CGRAM
    for(iLoop=0; iLoop<8; iLoop++)
        LCD_displayCharacter(pucPattern[iLoop]); //Pass the bytes of pattern on LCD
}
