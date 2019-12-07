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
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "commons.h"
#include "leds.h"
#include "buttons.h"
#include "batterymeter.h"
#include "anims.h"

enum Oldal{BAL = 0, JOBB};

#define AUTO_TURNOFF_TIME		3600*4		//sec


volatile byte anim_manual[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
volatile byte anim_manual_done = 0;
volatile byte anim_manual_enable = 0;
byte anim_manual_cnt = 0;

byte mode = 0;

volatile word anims_start_idx = 0;
volatile word anim_idx = 0xffff;  //a fix anim�ci�k k�z�l melyik megy
byte anim_now[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
byte anim_out[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte repeat_cnt = 0;
byte wait_cnt = 0;

enum Oldal oldal = BAL;

byte animcnt = 0;
byte pwmcnt = 4;
byte pwmshift = 0xFF;

volatile byte system_cnt = 0;
volatile byte sec_cnt = 0;
volatile word turnoff_cnt = AUTO_TURNOFF_TIME;

void show_battery();
void switch_mode(byte newmode);

void init_timer0()
{
	TCCR0A = 0; //normalest normal mode
	TCCR0B = 0x04; //256 prescaler
	TCNT0 = 250; //Ezt csak random be�ll�tjuk, hogy (majdnem) azonnal lej�rjon
	TIMSK0 = 0x01; //TOIE0: Timer/Counter0 Overflow Interrupt Enable
	bit_clr(&PRR, PRTIM0);
}

void init_timer1()
{
	TCCR1A = 0; //normalest normal mode
	TCCR1B = 0b00000101; //1024 prescaler
	TCNT1H = 0xFF;
	TCNT1L = 0xFF;
	TIMSK1 = 0b00000001;
	bit_clr(&PRR, PRTIM1);
}

void init_peripherals()
{
	DDRB=0x03;
	PORTB=0x02 | 0x04;
	DDRA=0xFF;
	PORTA=0x00;
	//ACSR=0x80; //disable adc
	//DIDR0 = 0x06;
	//ADCSRA=0x00;
	PRR = 0x00;
	
	init_timer0();
	init_timer1();
}

void init_anims()
{
	mode = 0;
	anims_start_idx = 0;
	anim_idx = 0xfff0;
	for (int i = 0; i < 13; i++)
	{
		anim_now[i] = 0;
		anim_out[i] = 0;
	}
	anim_now[13] = 1;
	anim_now[14] = 1;
	anim_manual[13] = 1;
	anim_manual[14] = 1;
	anim_manual_done = 0;
	anim_manual_enable = 0;
	
	repeat_cnt = 0;
	wait_cnt = 0;

	oldal = BAL;

	animcnt = 0;
	pwmcnt = 4;
	pwmshift = 0xFF;
	
	system_cnt = 0;
	
	sec_cnt = 0;
	turnoff_cnt = AUTO_TURNOFF_TIME;
}

void disableINT0_IT()
{
	bit_clr(&GIMSK, INT0);
}

void enableINT0_IT()
{
	bit_clr(&MCUCR, ISC00);
	bit_clr(&MCUCR, ISC01);
	bit_set(&GIMSK, INT0);
}

void goto_sleep()
{
	TIMSK0 = 0x00; //TOIE0: Timer/Counter0 Overflow Interrupt Disable
	PORTA = 0x00;

	while (!button0_status.Released)
	{
		button0_proc();
	}
	button0_status.Released = 0;
	//	while(!bit_get(&button0_PIN, button0_BIT));	//itt meg kell v�rni, hogy elengedj�k a gombot a gombos cuccodat nem siker�lt m�k�d�sre b�rnom, de te biztos v�god hogyan kell
	_delay_ms(1);	//ez a bemenet "felt�lt�d�se"/stabiliz�l�d�sa miatt kell


	button0_init();
	byte exitSleep = 0;
	while (!exitSleep)
	{
		PRR = 0x0F;		//Set the power save
		PORTB &= ~0x03;		//transistors off
		PORTA = 0;
		enableINT0_IT();
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_mode();
		disableINT0_IT();
		button0_proc();
		if (button0_status.Pressed)
		{
			button0_status.Pressed = 0;
			exitSleep = 1;
		}
		_delay_ms(10);
	}
	while(!button0_status.Released)
	{
		button0_proc();
		_delay_ms(10);
	}
	
	cli();
	init_anims();
	switch_mode(0xFF);
	init_peripherals();
	button0_init();
	sei();
	PRR = 0;
	show_battery();
	init_anims();
}

void anim1()
{
	byte done;
	cli();
	done = anim_manual_done; //itt ne csapjon be interrupt
	sei();
	if (!done)
	{
		if (anim_manual_cnt == 0)
		{
			anim_manual_cnt = 1;
			for (byte i = 0; i < 13; i++)
			{
				anim_manual[i] = 15;
			}
			anim_manual[13] = 0;
			anim_manual[14] = 130;
		}
		else
		{
			anim_manual_cnt = 0;
			for (byte i = 0; i < 13; i++)
			{
				anim_manual[i] = 1;
			}
			anim_manual[13] = 0;
			anim_manual[14] = 130;
		}
		cli();
		anim_manual_done = 1;
		sei();
	}
}

void show_battery()
{
	initAD();
	PORTA = 0x0;
	word battery = 0;
	for (byte i = 0; i < 64; i++)
	{
		battery += (word)batteryMeasure();
		_delay_ms(1);
	}
	battery >>= 6;
	disableAD();

	anim_manual_enable = 1;
	if (battery >= 7) battery = 7;
	sei();
	while(anim_manual_done);
	
	anim_manual[13] = 0;
	anim_manual[14] = 1;
	for (byte i = 0; i < 7; i++)
	{
		for (sbyte light = 1; light < 15; light++)
		{
			#if defined(_TYPE_SNOWMAN)
			if (i <= 4)
			{
				anim_manual[i] = light;
				anim_manual[i+6] = light;
			}
			if (i == 5) anim_manual[12] = light;
			anim_manual[5] = i == 6 ? light : 0;
			anim_manual[11] = i == 6 ? light : 0;
			#else
			if (i <= 5)
			{
				anim_manual[i] = light;
				anim_manual[i+6] = light;
			}
			if (i == 6) anim_manual[12] = light;
			#endif
			
			anim_manual_done = 1;
			while(anim_manual_done);
		}
	}
	
	for (sbyte i = 7; i != battery; i--)
	{
		for (sbyte light = 14; light >= 0; light--)
		{
			#if defined(_TYPE_SNOWMAN)
			if (i == 7)
			{
				anim_manual[5] = light;
				anim_manual[11] = light;
			}
			if (i == 6) anim_manual[12] = light;
			if (i <= 5 && i > 1)
			{
				anim_manual[i-1] = light;
				anim_manual[i+6-1] = light;
			}
			#else		
			if (i == 7)
			anim_manual[12] = light;
			if (i <= 6 && i > 1)
			{
				anim_manual[i-1] = light;
				anim_manual[i+6-1] = light;
			}
			#endif

			anim_manual_done = 1;
			while(anim_manual_done);
		}
	}
	for (byte i = 0; i < 3; i++)
	{
		anim_manual[14] = 130;
		anim_manual_done = 1;
		while(anim_manual_done);
	}
}

void switch_mode(byte newmode)
{
	cli();
	init_anims();
	mode = newmode;
	if (newmode < ANIM_NUM)
	{
		anim_manual_enable = 0;
		anims_start_idx = newmode;
	}
	else if (newmode == 0xFF)
	{
		anim_manual_enable = 1;
		for (byte i = 0; i < 13; i++)
		{
			anim_manual[i] = 0;
		}
		anim_manual[13] = 0;
		anim_manual[14] = 1;
	}
	else
	{
		anim_manual_enable = 0;
		anims_start_idx = newmode;
		mode = 0;
	}
	sei();
}

int main(void)
{
	initAD();
	init_peripherals();
	init_anims();
	button0_init();
	//switch_mode(0xFF);
	//anim_manual_enable = 1;
	//anim1();
	switch_mode(0xFF);
	
	show_battery();
	
	init_anims();
	//	switch_mode(0);
	sei();
	while (1)
	{
		if (system_cnt == 0)
		{
			system_cnt = 10; //10 ms
			
			tmr_dec_byte(&button0_longTimer);
			button0_proc();
			//PORTA = PINB << 0;
			tmr_dec_byte(&sec_cnt);
			if (sec_cnt == 0)
			{
				sec_cnt = 100;
				tmr_dec_word(&turnoff_cnt);
				if (turnoff_cnt == 0)
				{
					turnoff_cnt = AUTO_TURNOFF_TIME;
					button0_status.Released = 1;
					goto_sleep();
					continue;
				}
			}


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
				if (mode < ANIM_NUM)
				{
					if (mode == ANIM_NUM - 1)
					switch_mode(0);
					else
					switch_mode(mode + 1);
				}
				else
				{
					switch_mode(0);
				}
				//switch (mode)
				//{
				//case 0:
				//case 1:
				//case 2:
				//if (mode == 2)
				//switch_mode(0);
				//else
				//switch_mode(mode + 1);
				//break;
				//default:
				//switch_mode(0);
				//break;
				//}
			}
		}
		
		//anim1();
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

ISR(EXT_INT0_vect ){
	cli();
}

ISR(TIM1_OVF_vect)
{
	tmr_dec_byte(&system_cnt);
	TCNT1H = 0xFF;
	TCNT1L = 0xFF;
}

ISR(TIM0_OVF_vect)
{
	
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
		#if defined(_TYPE_TREE) || defined(_TYPE_STAR)
		out = (anim_out[12] & 0x1) << 1; //top led
		#endif
		anim_out[12] >>= 1;
	}
	TCNT0 = pwmshift;

	#if defined(_TYPE_TREE) || defined(_TYPE_STAR)
	for (byte i = idx_min; i <= idx_max; i++) //106 �rajelciklus
	{
		out |= (anim_out[i] & 0x1);
		out <<= 1;
		anim_out[i] >>= 1;
	}
	#elif defined(_TYPE_MEZI) || defined(_TYPE_SNOWMAN)
	for (byte i = idx_min; i <= idx_max; i++) //106 �rajelciklus
	{
		out |= (anim_out[i] & 0x1) << 7;
		out >>= 1;
		anim_out[i] >>= 1;
	}
	out |= (anim_out[12] & 0x1) << 7; //top led
	#endif
	PORTA = out;
	
	if (pwmcnt == 3 && oldal == BAL) //k�vi l�p�sben �j anim�ci� ker�l ki
	{
		//most lesz id�nk sz�molni (1900 �rajelciklus)
		wait_cnt++;
		if (wait_cnt == anim_now[14])
		{
			wait_cnt = 0;
			if (anim_manual_enable)
			{
				if (anim_manual_done)
				{
					if (anim_manual[13] == 0)
					{
						for (byte i = 0; i < 13; i++)
						{
							anim_now[i] = 0;
						}
					}
					for (byte i = 0; i < 13; i++)
					{
						anim_now[i] += anim_manual[i];
					}
					anim_now[13] = anim_manual[13];
					anim_now[14] = anim_manual[14];
					if (anim_now[13] == 0) anim_now[13] = 1;
					anim_manual_done = 0;
				}
			}
			else
			{
				repeat_cnt++;
				if (repeat_cnt == anim_now[13])
				{
					repeat_cnt = 0;
					anim_idx += 15;
					if (anim_idx >= pgm_read_word(&anims_start[anims_start_idx + 1]))
					{
						anim_idx = pgm_read_word(&anims_start[anims_start_idx]);
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
		}
		for (byte i = 0; i < 13; i++)
		{
			anim_out[i] = anim_now[i];
		}
	}

}

