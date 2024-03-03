 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the BUZZER driver
 *
 * Author: Youssef Abuzeid
 *
 *******************************************************************************/
#include "gpio.h"
#include "buzzer.h"


/*
 * Description :
 *  Setup the direction for the buzzer pin as output pin through the
 *  GPIO driver
 *  Turn off the buzzer through the GPIO
 */
void Buzzer_init(void){
	/* Setup the direction for the buzzer pin as output
	 */
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	/*
	 * Turn off the buzzer
	 */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);

}



/*
 * Description :
 *  Turn on the buzzer through the GPIO
 */
void Buzzer_on(void){

	/*
	 * Turn on the buzzer
	 */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

/*
 * Description :
 *  Turn off the buzzer through the GPIO
 */
void Buzzer_off(void){
	/*
	 * Turn off the buzzer
	 */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);

}
