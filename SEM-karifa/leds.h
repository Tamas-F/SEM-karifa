/*
 * leds.h
 *
 * Created: 2018. 11. 01. 21:37:04
 *  Author: Tomi
 */ 
#pragma once

#include "commons.h"


//extern inline void LED0_ON();


#define LINE0_PIN	0
#define LINE1_PIN	1
#define LINE2_PIN	2
#define LINE3_PIN	3
#define LINE4_PIN	3
#define LINE5_PIN	3
#define LINE6_PIN	4

static inline void set_oldal_jobb()
{
	bit_set(&PORTB, 0);
	bit_clr(&PORTB, 1);
}

static inline void set_oldal_bal()
{
	bit_clr(&PORTB, 0);
	bit_set(&PORTB, 1);
}

