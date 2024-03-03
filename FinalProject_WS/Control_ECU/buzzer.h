 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the BUZZER driver
 *
 * Author: Youssef Abuzeid
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
#include "common_macros.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID			PORTC_ID
#define BUZZER_PIN_ID			PIN2_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 *  Setup the direction for the buzzer pin as output pin through the
 *  GPIO driver
 *  Turn off the buzzer through the GPIO
 */
void Buzzer_init(void);



/*
 * Description :
 *  Turn on the buzzer through the GPIO
 */
void Buzzer_on(void);

/*
 * Description :
 *  Turn off the buzzer through the GPIO
 */
void Buzzer_off(void);



#endif /* BUZZER_H_ */
