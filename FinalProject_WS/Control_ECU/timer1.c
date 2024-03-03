 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.c
 *
 * Description: Source file for the TIMER1 AVR driver
 *
 * Author: Youssef Abuzeid
 *
 *******************************************************************************/
#include "avr\io.h"
#include "avr\interrupt.h"
#include "timer1.h"

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/*
 * Description :
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	switch(Config_Ptr->mode){
	case NORMAL:
		/*
		 * Put the inital value in TCNT1
		 */
		TCNT1 = Config_Ptr->initial_value;
		/*
		 * clear the register for normal mode
		 * set FOC1A=1 to use unit A
		 */
		TCCR1A= (1<<FOC1A);
		/*
		 * Set the prescaler
		 */
		TCCR1B= Config_Ptr->prescaler;

		/*
		 * Enable OverFlow Mode Interrupt
		 */
		SET_BIT(TIMSK,TOIE1);

		break;
	case COMPARE:
		/*
		 * Reset the timer
		 */
		TCNT1 = 0;
		/*
		 * Set the Compare Value
		 */
		OCR1A = Config_Ptr->compare_value;
		/*
		 *  set FOC1A=1 to use unit A
		 */
		TCCR1A = (1<<FOC1A);
		/*
		 * Set the Prescaler
		 * Configure it to compare mode
		 */
		TCCR1B = (1<<WGM12) | Config_Ptr->prescaler;

		/* Enable Timer1 Compare A Interrupt */
		SET_BIT(TIMSK,OCIE1A);


	}

}

/*
 * Description :
 * Function to disable the Timer1 driver
 */
void Timer1_deInit(void){
	TCNT1 = 0;
	OCR1A = 0;
	TCCR1A= 0;
	TCCR1B = 0;
	TIMSK &= ~((1 << TOIE1) | (1 << OCIE1A));
	g_callBackPtr=NULL_PTR;
}


/*
 * Description :
 * Function to set the Call Back function address
 */
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr=a_ptr;
}
ISR(TIMER1_OVF_vect){
	if(g_callBackPtr!=NULL_PTR){
		g_callBackPtr();

	}
}
ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr!=NULL_PTR){
		g_callBackPtr();
	}

}
