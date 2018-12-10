/*
 * buttons.c
 *
 * Created: 2017. 05. 18. 20:47:45
 *  Author: Tomi
 */ 
#include "buttons.h"
#include "commons.h"

byte	button0_longTimer;	//decrement every 10 ms
byte	button0_timer;
byte	button0_phase;
button_status button0_status;


void button0_init()
{
	button0_status.State = 0;
	button0_status.Pressed = 0;
	button0_status.Released = 0;
	button0_status.LongPress = 0;
	button0_status.Clicked = 0;
	button0_longTimer = INIT_BUTTON0_LONG1;
	button0_timer = INIT_BUTTON0_PRELL;
	button0_phase = 0;
	bit_clr(&button0_DDR, button0_BIT);
	bit_set(&button0_PORT, button0_BIT);
}

void button0_proc()
{
	tmr_dec_byte(&button0_timer);
	switch (button0_phase)
	{
		case 0: //Stable, unpressed
		if (button0_input())
		{
			button0_timer = INIT_BUTTON0_PRELL;
			button0_phase++;
		}
		break;
		
		case 1: //About to be pressed (prell)
		if (!button0_input())
		{
			button0_phase--;
		}
		else if (!button0_timer)
		{
			button0_status.State = 1;
			button0_status.Pressed = 1;
			button0_status.CanClick = 1;
			button0_phase++;
			button0_longTimer = INIT_BUTTON0_LONG1;
		}
		break;
		
		case 2:	//Stable, pressed
		if (!button0_input())
		{
			button0_timer = INIT_BUTTON0_PRELL;
			button0_phase++;
		}
		else if (!button0_longTimer)
		{
			button0_longTimer = INIT_BUTTON0_LONG2;
			button0_status.CanClick = 0;
			button0_status.LongPress = 1;
		}
		break;
		
		case 3://About to be unpressed (prell)
		if (button0_input())
		{
			button0_phase--;
		}
		else if (!button0_timer)
		{
			button0_status.State = 0;
			button0_status.Released = 1;
			button0_status.Clicked = button0_status.CanClick;
			button0_status.CanClick = 0;
			button0_phase = 0;
		}
		break;
		default:
		button0_phase = 0;
		break;
	}
}


