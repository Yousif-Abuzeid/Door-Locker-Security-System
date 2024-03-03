/******************************************************************************
 *
 *
 *
 * File Name: HMI.c
 *
 * Description: Source file for the Human interface MicroController
 *
 * Author: Youssef Abuzeid
 *
 *******************************************************************************/
#include	"lcd.h"
#include	"keypad.h"
#include	"uart.h"
#include	"timer1.h"
#include	"util\delay.h"
#include 	"Commands.h"


uint8 g_ticks=0;
uint8 g_Password_Set=0;
uint8 g_MistakeCount=0;
uint8 g_CommandReceived;
uint16 g_Pass_1;
uint16 g_Pass_2;
uint8 i;

UART_ConfigType UART_Configuration;
void HMI_CallbackError(void){
	g_ticks++;
	LCD_moveCursor(0,0);
	LCD_displayString("ERROR");
}
void HMI_CallbackDoor(void){
	g_ticks++;

	if(g_ticks==5){

		LCD_clearScreen();
		LCD_displayString("Door is");
		LCD_moveCursor(1,0);
		LCD_displayString("Unlocked");
	}else if(g_ticks==6){

		LCD_clearScreen();
		LCD_displayString("Door is");
		LCD_moveCursor(1,0);
		LCD_displayString("Locking");
	}else if(g_ticks==11){

		LCD_clearScreen();
		LCD_displayString("Door is Locked");


	}
}

/*
 * Description: Function Sends the Password to Control Unit
 */
void APP_sendPassword(uint8* a_PassPtr){
	for(uint8 j=0; j<2; j++){
		UART_sendByte(a_PassPtr[j]);
	}
}


/*
 * Description: Function that sets the password of the system
 */
void HMI_setPassword(void){

	do{
		g_Pass_1=0;
		g_Pass_2=0;
		LCD_displayString("Plz enter pass:");

		LCD_moveCursor(1,0);
		for(i=0; i<5; i++){
			uint8 key=0xFF;
			while (key == 0xFF) {
				key = KEYPAD_getPressedKey();
				_delay_ms(500);
			}
			/*
			 * To get a number
			 */
			if(	key<=9 && key>=0){

				LCD_displayCharacter('*');
				g_Pass_1=g_Pass_1*10+key;
			}else{
				/*
				 * To repeat until i get 5 numbers
				 */
				i--;
			}


		}
		/*
		 * Wait till Enter is Pressed
		 */
		while(KEYPAD_getPressedKey()!='=');
		/*
		 * Tell the Control unit im sending the first
		 * Password
		 */
		UART_sendByte(SENDING_FIRST_PASS);
		APP_sendPassword((uint8*)&g_Pass_1);

		LCD_clearScreen();
		LCD_displayString("Plz re-enter the");
		LCD_moveCursor(1,0);
		LCD_displayString("same pass:");
		for(i=0; i<5; i++){
			uint8 key=0xFF;
			while (key == 0xFF) {
				key = KEYPAD_getPressedKey();
				_delay_ms(500);
			}
			/*
			 * To get a number
			 */
			if(	key<=9 && key>=0){

				LCD_displayCharacter('*');
				g_Pass_2=g_Pass_2*10+key;
			}else{
				/*
				 * To repeat until i get 5 numbers
				 */
				i--;
			}


		}
		/*
		 * Wait till the Enter is pressed
		 */
		while(KEYPAD_getPressedKey()!='=');

		/*
		 * Tell the Control unit im sending the second
		 * Password
		 */
		UART_sendByte(SENDING_SECOND_PASS);
		/*
		 * Send the Second password
		 */
		APP_sendPassword((uint8*)&g_Pass_2);
		uint8 command=UART_recieveByte();
		/*
		 * Wait for the control unit to tell u if
		 * the Passwords match
		 */
		if(command!=PASS_MATCH){
			g_MistakeCount++;
			LCD_clearScreen();
			LCD_displayString("Wrong Password");
			_delay_ms(2000);
		}else{
			LCD_clearScreen();
			g_MistakeCount=0;
		}
		LCD_clearScreen();
	}
	/*
	 * Repeat until two matched passwords are entered
	 */
	while(g_MistakeCount!=0);

}

/*
 * Function that displays and do the main options of the system
 */
void HMI_Menu(){
	uint8 key;
	LCD_displayString("+ : Open Door");
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Pass");
	key = KEYPAD_getPressedKey();
	_delay_ms(50);
	while(key!='+' && key!='-'){
		key = KEYPAD_getPressedKey();
		_delay_ms(500);
	}
	switch(key){
	/*
	 * Open Door case
	 */
	case '+':

		do{
			LCD_clearScreen();
			LCD_displayString("Plz enter pass:");
			LCD_moveCursor(1,0);
			g_Pass_1=0;
			g_Pass_2=0;
			for(i=0; i<5; i++){

				uint8 key=0xFF;
				while (key == 0xFF) {
					key = KEYPAD_getPressedKey();
					_delay_ms(500);
				}
				if(	key<=9 && key>=0){

					LCD_displayCharacter('*');
					g_Pass_1=g_Pass_1*10+key;
				}else{
					i--;
				}




			}while(KEYPAD_getPressedKey()!='=');
			UART_sendByte(CHECK_PASS);
			APP_sendPassword((uint8*)&g_Pass_1);

			if(UART_recieveByte()==PASS_MATCH){
				/*
				 * Configure the timer for 3 seconds Compare mode
				 */
				Timer1_ConfigType Timer_Configuration={0,23437,F_CPU_1024,COMPARE};
				g_MistakeCount=0;
				LCD_clearScreen();
				LCD_displayString("Door is ");
				LCD_moveCursor(1,0);
				LCD_displayString("Unlocking");
				/*
				 * Tell the control unit to open the door
				 */
				UART_sendByte(OPEN_DOOR);
				/*
				 * Set the callback function
				 */
				Timer1_setCallBack(HMI_CallbackDoor);
				Timer1_init(&Timer_Configuration);
				while(g_ticks!=12);
				LCD_clearScreen();
				/*
				 * Deinit the timer
				 */
				g_ticks=0;
				Timer1_deInit();
			}else{
				LCD_clearScreen();
				LCD_displayString("Wrong Password");
				_delay_ms(2000);
				g_MistakeCount++;
			}

		}while(g_MistakeCount<3 && g_MistakeCount!=0);
		if(g_MistakeCount==3){
			/*
			 * Enter Failure Mode
			 */

			Timer1_ConfigType Timer_Configuration_ERROR={0,0,F_CPU_1024,NORMAL};
			Timer1_setCallBack(HMI_CallbackError);
			Timer1_init(&Timer_Configuration_ERROR);
			UART_sendByte(BUZZER_ON);
			LCD_displayString("ERROR");

			while(g_ticks!=7);
			Timer1_deInit();
			LCD_clearScreen();
			g_ticks=0;
			g_MistakeCount=0;

		}
		break;

		/*
		 * Change Password Case
		 */
	case '-':
		do{
			g_Pass_1=0;
			g_Pass_2=0;
			LCD_clearScreen();
			LCD_displayString("Plz enter old");
			LCD_moveCursor(1,0);
			LCD_displayString("pass: ");

			for(i=0; i<5; i++){
				uint8 key=0xFF;
				while (key == 0xFF) {
					key = KEYPAD_getPressedKey();
					_delay_ms(500);
				}
				if(	key<=9 && key>=0){

					LCD_displayCharacter('*');
					g_Pass_1=g_Pass_1*10+key;
				}else{
					i--;
				}




			}while(KEYPAD_getPressedKey()!='=');
			UART_sendByte(CHECK_PASS);
			APP_sendPassword((uint8*)&g_Pass_1);
			if(UART_recieveByte()==PASS_MATCH){
				/*
				 * Set a new password
				 */
				g_MistakeCount=0;
				LCD_clearScreen();
				HMI_setPassword();
				break;

			}else{

				g_MistakeCount++;
				LCD_clearScreen();
				LCD_displayString("Wrong Password");
				_delay_ms(2000);
			}

		}while(g_MistakeCount<3 && g_MistakeCount!=0);
		if(g_MistakeCount==3){
			/*
			 * Configure the timer NORMAL Mode
			 */
			Timer1_ConfigType Timer_Configuration_ERROR={0,0,F_CPU_1024,NORMAL};
			Timer1_setCallBack(HMI_CallbackError);
			Timer1_init(&Timer_Configuration_ERROR);
			UART_sendByte(BUZZER_ON);
			LCD_displayString("ERROR");
			/*
			 * wait for 60 seconds
			 */
			while(g_ticks!=7);
			Timer1_deInit();
			LCD_clearScreen();
			g_ticks=0;
			g_MistakeCount=0;

		}

		//HMI_setPassword();
		break;

	}
}

int main(){
	UART_Configuration.baud_rate=BuadRate_9600;
	UART_Configuration.bit_data=Eight_bit_Mode;
	UART_Configuration.parity=Parity_Disabled;
	UART_Configuration.stop_bit=One_Bit;

	LCD_init();
	UART_init(&UART_Configuration);
	/*
	 * Enable global interrupt
	 */
	asm("SEI");

	while(1){

		/*
		 * Ask the control unit if there is password saved
		 */
		UART_sendByte(ASK_FOR_PASS);

		g_CommandReceived=UART_recieveByte();

		if(g_CommandReceived==PASS_SET){
			/*
			 * if the password is set show the options
			 */
			HMI_Menu();
			LCD_clearScreen();

		}else{
			/*
			 * if the password is not set
			 * set a new password
			 */
			HMI_setPassword();
			LCD_clearScreen();

		}



	}
}

