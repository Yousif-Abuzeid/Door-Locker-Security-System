 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Description: header file for the TIMER1 AVR driver
 *
 * Author: Youssef Abuzeid
 *
 *******************************************************************************/
#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"
#include "common_macros.h"



/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	CLOCK_OFF,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,
	EXTERNAL_CLOCK_FALLING,EXTERNAL_CLOCK_RISING
}Timer1_Prescaler;

typedef enum{
	NORMAL,COMPARE=4
}Timer1_Mode;

typedef struct{
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description :
 * Function to disable the Timer1 driver
 */
void Timer1_deInit(void);


/*
 * Description :
 * Function to set the Call Back function address
 */
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
