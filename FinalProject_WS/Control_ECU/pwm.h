 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the AVR PWM driver
 *
 * Author: Youssef Abuzeid
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"
#include "common_macros.h"

/******************************************************************************************************************************************************
 * 														FUNCTIONS PROTOTYPES
 ******************************************************************************************************************************************************/


void Timer0_disableClock(void);

void Timer0_PWM_Init(uint8 set_duty_cycle);


#endif /* PWM_H_ */
