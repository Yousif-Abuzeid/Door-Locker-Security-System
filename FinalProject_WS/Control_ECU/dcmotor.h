 /******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: dcmotor.h
 *
 * Description: Header file for the DC MOTOR driver
 *
 * Author: Youssef Abuzeid
 * ******************************************************************************
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include	"std_types.h"
#include	"common_macros.h"

/******************************************************************************************************************************************************
 * 															DEFINITIONS
 ******************************************************************************************************************************************************/
#define DC_MOTOR_CONTROL_PORT PORTB_ID
#define DC_MOTOR_PIN_1		  PIN0_ID
#define DC_MOTOR_PIN_2		  PIN1_ID


/******************************************************************************************************************************************************
 * 														TYPES DECLARATION
 ******************************************************************************************************************************************************/

typedef enum{
	OFF,CW,A_CW
}DcMotor_State;

/******************************************************************************************************************************************************
 * 														FUNCTIONS PROTOTYPES
 ******************************************************************************************************************************************************/


/*
 * Description :
 * Function responsible for initialization of DC MOTOR.
 */
void DcMotor_Init(void);

/*
 * Description :
 * Function responsible for rotation of DC MOTOR with certain speed.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
