/*
 * SEM-karifa.c
 *
 * Created: 2018. 12. 07. 18:02:14
 * Author : Tomi
 */ 

#define F_CPU 1000000UL  // 1 MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay_basic.h>
#include "commons.h"
#include "leds.h"
#include "buttons.h"
#define ido	100

enum Oldal{BAL = 0, JOBB};

#define ANIM_NUM	1
#define ANIM_BYTES	15
const PROGMEM byte anims_start[ANIM_NUM + 1] = {0, 14*ANIM_BYTES};

const PROGMEM byte anims[] = {//120 = 1 sec
	15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 0, /*várakozás*/ 1,
	-1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, 0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,

	0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, 0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, 0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	0, 0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 120/15,
	
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 1
};

word anims_start_idx = 0;
word anim_idx = 0xffff;
byte anim_now[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
byte anim_out[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte repeat_cnt = 0;
byte wait_cnt = 0;

enum Oldal oldal = BAL;

byte animcnt = 0;
byte pwmcnt = 4;
byte pwmshift = 0xFF;

volatile byte system_cnt = 0;

void init_peripherals()
{
	DDRB=0x03;
	PORTB=0x02 | 0x04;
	DDRA=0xFF;
	PORTA=0x00;
	ACSR=0x80; //disable adc
	DIDR0 = 0x06;
	ADCSRA=0x00;
	PRR = 0x0B;

	TCCR0A = 0; //normalest normal mode
	TCCR0B = 0x04; //256 prescaler
	TCNT0 = 250; //Ezt csak random beállítjuk, hogy (majdnem) azonnal lejárjon
	TIMSK0 = 0x01; //TOIE0: Timer/Counter0 Overflow Interrupt Enable
}

void init_main()
{
	anims_start_idx = 0;
	anim_idx = 0xfff0;
	for (int i = 0; i < 13; i++)
	{
		anim_now[i] = 0;
		anim_out[i] = 0;
	}
	anim_now[13] = 1;
	anim_now[14] = 1;
	repeat_cnt = 0;
	wait_cnt = 0;

	oldal = BAL;

	animcnt = 0;
	pwmcnt = 4;
	pwmshift = 0xFF;
	
	system_cnt = 0;
}

void disableINT0_IT()
{
	bit_clr(&GIMSK, INT0_BIT);
}

void enableINT0_IT()
{
	bit_clr(&MCUCR, ISC00);
	bit_clr(&MCUCR, ISC01);
	bit_set(&GIMSK, INT0_BIT);
}

void goto_sleep()
{
	TIMSK0 = 0x00; //TOIE0: Timer/Counter0 Overflow Interrupt Enable
	PRR = 0x0F;
	PORTB &= ~0x03;
	PORTA = 0x00;
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_mode();
	cli();
	DDRB=0x03;
	PORTB=0x02 | 0x04;
	DDRA=0xFF;
	PORTA=0x00;
	disableINT0_IT();
	init_peripherals();
	init_main();
	sei();
}

int main(void)
{
	init_peripherals();
	init_main();
	button0_init();
	
	sei();
	
	/* Replace with your application code */
	while (1)
	{
		if (system_cnt == 0)
		{
			system_cnt = 39; //10 ms
			tmr_dec_byte(&button0_longTimer);
			button0_proc();
			//PORTA = PINB << 0;
			if (button0_status.Pressed)
			{
				button0_status.Pressed = 0;
			}
			if (button0_status.Released)
			{
				button0_status.Released = 0;
			}
			if (button0_status.LongPress)
			{
				button0_status.LongPress = 0;
				goto_sleep();
				continue;
			}
			if (button0_status.Clicked)
			{
				button0_status.Clicked = 0;
			}
		}
		/*if (!(PINB & 0x04))
		{

		}*/
	}
}

void get_next_animation()
{
	for (byte i = 0; i < 13; i++)
	{
		anim_now[i] += pgm_read_byte(&anims[anim_idx + i]);
	}
	anim_now[13] = pgm_read_byte(&anims[anim_idx + 13]);
	anim_now[14] = pgm_read_byte(&anims[anim_idx + 14]);
	if (anim_now[13] == 0) anim_now[13] = 1;
}


ISR(TIM0_OVF_vect)
{
	tmr_dec_byte(&system_cnt);
	
	byte idx_min = 0;
	byte idx_max = 5;
	byte out = 0;
	if (oldal == BAL)
	{
		PORTA = 0;
		oldal = JOBB;
		set_oldal_bal();
		pwmshift <<= 1;
		pwmcnt++;
		if (pwmcnt >= 4)
		{
			pwmcnt = 0;
			pwmshift = 0xFF;
		}
	}
	else
	{
		oldal = BAL;
		PORTA = 0;
		set_oldal_jobb();
		idx_min = 6;
		idx_max = 11;
		out = (anim_out[12] & 0x1) << 1; //top led
		anim_out[12] >>= 1;
	}
	TCNT0 = pwmshift;

	for (byte i = idx_min; i <= idx_max; i++)
	{
		out |= (anim_out[i] & 0x1);
		out <<= 1;
		anim_out[i] >>= 1;
	}
	PORTA = out;
	
	if (pwmcnt == 3 && oldal == BAL) //kövi lépésben új animáció kerül ki
	{
		//most lesz idõnk számolni
		wait_cnt++;
		if (wait_cnt == anim_now[14])
		{
			wait_cnt = 0;
			repeat_cnt++;
			if (repeat_cnt == anim_now[13])
			{
				repeat_cnt = 0;
				anim_idx += 15;
				if (anim_idx >= pgm_read_byte(&anims_start[anims_start_idx + 1]))
				{
					anim_idx = 0;
				}
				if (pgm_read_byte(&anims[anim_idx + 13]) == 0)
				{
					for (byte i = 0; i < 13; i++)
					{
						anim_now[i] = 0;
					}
				}
			}
			get_next_animation();
		}
		anim_out[0] = 0;
		for (byte i = 0; i < 13; i++)
		{
			anim_out[i] = anim_now[i];
		}
	}

}

