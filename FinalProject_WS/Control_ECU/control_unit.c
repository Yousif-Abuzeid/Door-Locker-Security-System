 /******************************************************************************
 *
 *
 *
 * File Name: control_unit.c
 *
 * Description: Source file for the Control Unit MicroController
 *
 * Author: Youssef Abuzeid
 *
 *******************************************************************************/
#include "external_eeprom.h"
#include "dcmotor.h"
#include "buzzer.h"
#include "uart.h"
#include "timer1.h"
#include "Commands.h"
#include "twi.h"
#include <util\delay.h>


UART_ConfigType UART_Configuration;
TWI_ConfigType  TWI_Configuration={0x02,Buadrate_400K};
Timer1_ConfigType Timer_Configuration={0,23437,F_CPU_1024,COMPARE};
Timer1_ConfigType Timer_Configuration_ERROR={0,0,F_CPU_1024,NORMAL};

uint8	g_ticks=0;
uint8 	g_commandRecieved;
uint16	g_passRecieved_1;
uint16	g_passRecieved_2;
uint16	g_passBuffer;
uint8*  g_passBufferPtr=(uint8*)&g_passBuffer;
uint8*	g_passPtr=(uint8*)&g_passRecieved_1;
uint8	g_passCheck;

void HMI_CallbackError(void){
g_ticks++;
}

void CallbackDoor(void){
	g_ticks++;
	if(g_ticks==5){
		DcMotor_Rotate(OFF,0);

	}else if(g_ticks==6){
		DcMotor_Rotate(A_CW,100);

	}else if(g_ticks==11){

		DcMotor_Rotate(OFF,0);



	}
}

void RecievePassword(){
	switch(g_commandRecieved){
	case SENDING_FIRST_PASS:
		/*
		 * Receive the first byte of the password
		 */
		g_passRecieved_1=UART_recieveByte();
		/*
		 * Receive the second byte of the password
		 */
		g_passRecieved_1|=(UART_recieveByte()<<8);
		break;
	case SENDING_SECOND_PASS:
		/*
		 * Receive the first byte of the password
		 */
		g_passRecieved_2=UART_recieveByte();
		/*
		 * Receive the second byte of the password
		 */
		g_passRecieved_2|=(UART_recieveByte()<<8);
		break;

	default:
		/*
		 * Receive the first byte of the password
		 */
		g_passRecieved_1=UART_recieveByte();
		/*
		 * Receive the second byte of the password
		 */
		g_passRecieved_1|=(UART_recieveByte()<<8);
		break;


	}

}

int main(void){

	UART_Configuration.baud_rate=BuadRate_9600;
	UART_Configuration.bit_data=Eight_bit_Mode;
	UART_Configuration.parity=Parity_Disabled;
	UART_Configuration.stop_bit=One_Bit;

	Buzzer_init();
	DcMotor_Init();
	TWI_init(&TWI_Configuration);

	UART_init(&UART_Configuration);
	asm("SEI");

	/*
	 * Comment this line after the first run
	 * just to create a password for user
	 */
	EEPROM_writeByte(0x0000,0x00);
	_delay_ms(20);

	while(1){


		g_commandRecieved=UART_recieveByte();

		switch(g_commandRecieved){

		case SENDING_FIRST_PASS:
			RecievePassword();
			break;
		case SENDING_SECOND_PASS:
			RecievePassword();
			if(g_passRecieved_1==g_passRecieved_2){
				UART_sendByte(PASS_MATCH);
				/*
				 * write the password in memory
				 */
				EEPROM_writeByte(0x0311,*(g_passPtr));
				_delay_ms(20);
				EEPROM_writeByte(0x0312,*(g_passPtr+1));
				_delay_ms(20);
				/*
				 * Set that there is a password for check
				 */
				EEPROM_writeByte(0x0000,0x01);
				_delay_ms(20);

			}else{
				/*
				 * send error
				 */
				UART_sendByte(0xFF);
			}

			break;
		case ASK_FOR_PASS:
			/*
			 * check if there is a password
			 */
			EEPROM_readByte(0x0000,&g_passCheck);
			_delay_ms(20);

			if(g_passCheck==0x01){
				UART_sendByte(PASS_SET);
			}else{
				UART_sendByte(PASS_NOT_SET);
			}
			break;
		case CHECK_PASS:
			RecievePassword();
			EEPROM_readByte(0x0311,g_passBufferPtr);
			EEPROM_readByte(0x0312,g_passBufferPtr+1);
			if(g_passRecieved_1==g_passBuffer){
				UART_sendByte(PASS_MATCH);
			}else{
				UART_sendByte(0xFF);
			}
			break;
		case OPEN_DOOR:
			Timer1_setCallBack(CallbackDoor);
			Timer1_init(&Timer_Configuration);
			DcMotor_Rotate(CW,100);
			while(g_ticks!=11);
			g_ticks=0;
			Timer1_deInit();
			break;
		case BUZZER_ON:
			Timer1_setCallBack(HMI_CallbackError);
			Timer1_init(&Timer_Configuration_ERROR);
			Buzzer_on();
			while(g_ticks!=7);
			Buzzer_off();
			g_ticks=0;
			Timer1_deInit();

		}
	}
}
