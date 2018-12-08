/*
 * leds.h
 *
 * Created: 2018. 11. 01. 21:37:04
 *  Author: Tomi
 */ 
#pragma once

#include "commons.h"


//extern inline void LED0_ON();


#define LED0_PINH	0
#define LED0_PINL	3
#define LED1_PINH	1
#define LED1_PINL	3
#define LED2_PINH	2
#define LED2_PINL	3
#define LED3_PINH	3
#define LED3_PINL	0
#define LED4_PINH	3
#define LED4_PINL	1
#define LED5_PINH	3
#define LED5_PINL	2
#define LED6_PINH	4
#define LED6_PINL	0
#define LED7_PINH	4
#define LED7_PINL	1
#define LED8_PINH	4
#define LED8_PINL	2
#define LED9_PINH	3
#define LED9_PINL	4
#define LED10_PINH	0
#define LED10_PINL	4
#define LED11_PINH	1
#define LED11_PINL	4
#define LED12_PINH	2
#define LED12_PINL	4


static inline void LED_OFF()
{
	DDRB = 0;
	PORTB = 0;
}

static inline void LED0_ON()
{
	DDRB = bv(LED0_PINH) | bv(LED0_PINL);
	PORTB = bv(LED0_PINH);
}

static inline void LED1_ON()
{
	DDRB = bv(LED1_PINH) | bv(LED1_PINL);
	PORTB = bv(LED1_PINH);
}

static inline void LED2_ON()
{
	DDRB = bv(LED2_PINH) | bv(LED2_PINL);
	PORTB = bv(LED2_PINH);
}

static inline void LED3_ON()
{
	DDRB = bv(LED3_PINH) | bv(LED3_PINL);
	PORTB = bv(LED3_PINH);
}

static inline void LED4_ON()
{
	DDRB = bv(LED4_PINH) | bv(LED4_PINL);
	PORTB = bv(LED4_PINH);
}

static inline void LED5_ON()
{
	DDRB = bv(LED5_PINH) | bv(LED5_PINL);
	PORTB = bv(LED5_PINH);
}

static inline void LED6_ON()
{
	DDRB = bv(LED6_PINH) | bv(LED6_PINL);
	PORTB = bv(LED6_PINH);
}

static inline void LED7_ON()
{
	DDRB = bv(LED7_PINH) | bv(LED7_PINL);
	PORTB = bv(LED7_PINH);
}

static inline void LED8_ON()
{
	DDRB = bv(LED8_PINH) | bv(LED8_PINL);
	PORTB = bv(LED8_PINH);
}

static inline void LED9_ON()
{
	DDRB = bv(LED9_PINH) | bv(LED9_PINL);
	PORTB = bv(LED9_PINH);
}

static inline void LED10_ON()
{
	DDRB = bv(LED10_PINH) | bv(LED10_PINL);
	PORTB = bv(LED10_PINH);
}

static inline void LED11_ON()
{
	DDRB = bv(LED11_PINH) | bv(LED11_PINL);
	PORTB = bv(LED11_PINH);
}

static inline void LED12_ON()
{
	DDRB = bv(LED12_PINH) | bv(LED12_PINL);
	PORTB = bv(LED12_PINH);
}

