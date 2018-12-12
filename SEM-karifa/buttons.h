/*
 * buttons.h
 *
 * Created: 2017. 05. 18. 20:47:21
 *  Author: Tomi
 */ 

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "commons.h"
#include <avr/io.h>


typedef struct
{
	byte State		: 1;
	byte Pressed	: 1;
	byte Released	: 1;
	byte LongPress	: 1;
	byte Clicked	: 1;
	byte CanClick	: 1;
} button_status;

void button0_init();
void button0_proc();

#define button0_DDR			DDRB
#define button0_PORT		PORTB
#define button0_PIN			PINB
#define	button0_BIT			PORTB2
#define button0_input()		(!bit_get(&button0_PIN, button0_BIT))

extern byte button0_longTimer;		//10ms
extern button_status button0_status;

#define INIT_BUTTON0_PRELL	2		//x10ms
#define INIT_BUTTON0_LONG1	100		//x10ms
#define INIT_BUTTON0_LONG2	30		//x10ms

#endif /* BUTTONS_H_ */