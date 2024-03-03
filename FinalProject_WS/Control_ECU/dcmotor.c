 /******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: dcmotor.c
 *
 * Description: Source file for the DC MOTOR driver
 *
 * Author: Youssef Abuzeid
 *
 *******************************************************************************/

#include "gpio.h"
#include "pwm.h"
#include "dcmotor.h"


/*
 * Description :
 * Function responsible initialization of DC MOTOR.
 */
void DcMotor_Init(void){
	/*
	 * Set motor pins directions
	 * */
	GPIO_setupPinDirection(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_1,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_2,PIN_OUTPUT);
	/*
	 * Turn motor off
	 */
	GPIO_writePin(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_1,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_2,LOGIC_LOW);


}


/*
 * Description :
 * Function responsible for rotation of DC MOTOR with certain speed.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	switch (state){
	case OFF:
		/*
		 * Stop the rotation of DC MOTOR
		 */
		GPIO_writePin(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_2,LOGIC_LOW);
		break;
	case CW:
		/*
		 * Rotate the DC MOTOR Clock Wise
		 */
		GPIO_writePin(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_1,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_2,LOGIC_LOW);
		break;
	case A_CW:
		/*
		 * Rotate the DC MOTOR Anti Clock Wise
		 */
		GPIO_writePin(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_1,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_CONTROL_PORT,DC_MOTOR_PIN_2,LOGIC_HIGH);
		break;
	}
	/*
	 * Generate PWM Related to the input speed
	 */
	Timer0_PWM_Init(((uint16)255*speed)/100);

}



