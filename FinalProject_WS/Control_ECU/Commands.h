/*
 * Commands.h
 *
 *		Contains Defines of Commands Used by UART
 *      Author: Youssef Abuzeid
 */


#ifndef COMMANDS_H_
#define COMMANDS_H_


#define ASK_FOR_PASS		0x01
#define SENDING_FIRST_PASS	0x02
#define SENDING_SECOND_PASS	0x03
#define PASS_SET			0x04

#define	PASS_NOT_SET		0x05
#define CHANGE_PASS			0x08

#define OPEN_DOOR			0x06
#define CLOSE_DOOR			0x07

#define CHECK_PASS			0x09
#define PASS_MATCH			0x0A

#define BUZZER_ON			0x0B

#define MC2_READY			0x99




#endif /* COMMANDS_H_ */
