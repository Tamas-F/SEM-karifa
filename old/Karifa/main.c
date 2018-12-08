/*
 * Karifa.c
 *
 * Created: 2018. 11. 01. 20:41:20
 * Author : Tomi
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "commons.h"
#include "leds.h"
#include <avr/pgmspace.h>

//9,6 MHz clock: 13 LED, 256 instuction in IT, 4 bit (16) PWM @ 180 Hz
//13*256*16*180 = 9 584 640

#define LEDS_NUM		13
#define CYCLE_NUM		2

//ciklus, "LEDS_NUM" db egymás utáni bájt határozza meg az éppen kirakandó fényerõket
//valójában double buffered, ha az egyik sort kirakja, a másikat lehet írni
byte cycles[CYCLE_NUM * LEDS_NUM] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
};

//az aktuális ciklus meddig legyen kint (egység: PWM frekvencia. Pl. 180 = kb. 1sec)
byte wait[CYCLE_NUM] =
{
	10,
	10
};

byte cycle_idx = 0; //animáció aktuális állapotát határozza meg ("anim" tömbben egy sort (LEDS_NUM bájtot) jelöl ki)
byte buffer_offset = 0; //cycles tömbben segít a címzésben (lényegében mindig cycle_idx * 13)
byte led_idx = 0; //a felvillantandó LED-et címzi
byte on_off = 0; //éppen be (1) vagy ki (0) kell kapcsolni az adott LED-et
byte off_time = 0; //ennyi ideig kell majd kikapcsolva tartani (PWM-off time)
byte wait_cnt = 0; //ennyit kell még várni az aktuális kép befejezõdéséig
byte calc_event = 0; //0 - nincs semmi
					 //1 - alsó (cycles[0-12]) sort számolhatjuk
					 //2 - felsõ (cycles[13-25]) sort számolhatjuk
byte calc_state = 0; //itt tároljuk, hogy hol tartunk az animációban
byte calc_offset = 0; //a cycles pufferhez egy offszet (hogy hova kell írni a számolás eredményét)

int main(void)
{
	MCUCR |= 0x40; // pullup disable (PUD) -> if pin is configured input, the pin goes High-Z
	LED_OFF();
	TCCR0A = 0; //normalest normal mode
	TCCR0B = 0x04; //256 prescaler
	TCNT0 = 250; //Ezt csak random beállítjuk, hogy (majdnem) azonnal lejárjon
	TIMSK0 = 0x02; //TOIE0: Timer/Counter0 Overflow Interrupt Enable

	sei();

	//Ezt a részt sokszor megszakíthatja (és meg is fogja) az interrupt -> Igyekezzünk.
    while (1)
    {
		byte calc_event_tmp = 0;
		cli();		//Itt most nem tesz jót ha bejönne egy IT (elronthatja calc_event-et útközben)
		calc_event_tmp = calc_event;
		calc_event = 0;
		sei();
		if (calc_event_tmp > 0)
		{
			if (calc_event_tmp == 1) //alsó rész szabad
			{
				calc_offset = 0;
			}
			else if (calc_event_tmp == 2) //felsõ rész szabad
			{
				calc_offset = 0 + CYCLE_NUM/2 * LEDS_NUM;
			}
			//BEGIN Animáció számolása (calc_state függvényében)
			for (byte i = 0; i < LEDS_NUM; i++)
			{
				//csak egymás után felvillantjuk a ledeket
				cycles[calc_offset + i] = 0;
				if (i == calc_state)
				{
					cycles[calc_offset + i] = 15;
				}
			}
			wait[cycle_idx] = 10;	//1 sec = 180

			calc_state++;
			if (calc_state >= 13) calc_state = 0;  //Itt annyit kell írni a feltételbe, ahány állapota van az animációnak
			//END Animáció számolása
		}
		_nop();
		_nop();
		_nop();
		_nop();
		_nop();
    }
}

ISR(TIM0_OVF_vect)
{
	if ((on_off & 1) == 0)
	{
		//OFF
		TCNT0 = off_time;
		LED_OFF();
		on_off = 1;		//Kövi állapot ON
	}
	else
	{
		//ON
		if (cycles[buffer_offset + led_idx] == 0) //Ha a fenyero min, nem kell semmit bekapcsolni, azonnal off állapotba megyünk
		{
			//TIFR0 |= 0x02; //Set TOV0
			TCNT0 = 256 - 16;
			LED_OFF();
		}
		else
		{
			TCNT0 = 256 - cycles[buffer_offset + led_idx];			//ennyi ideig kell bekapcsolni a ledet
			off_time = 256 - (16 - cycles[buffer_offset + led_idx]); //kikapcs idõt is kiszámoljuk
			switch (led_idx)
			{
				case(0): LED0_ON(); break;
				case(1): LED1_ON(); break;
				case(2): LED2_ON(); break;
				case(3): LED3_ON(); break;
				case(4): LED4_ON(); break;
				case(5): LED5_ON(); break;
				case(6): LED6_ON(); break;
				case(7): LED7_ON(); break;
				case(8): LED8_ON(); break;
				case(9): LED9_ON(); break;
				case(10): LED10_ON(); break;
				case(11): LED11_ON(); break;
				case(12): LED12_ON(); break;
				default: led_idx = 0; break; //error
			}
		}

		//Ha a fenyero max vagy min, nem kell majd off-ba menni
		if (cycles[buffer_offset + led_idx] < 15 && cycles[buffer_offset + led_idx] > 0)
		{
			on_off = 0;
		}

		led_idx++;
		if (led_idx > LEDS_NUM-1)
		{
			//végigmentünk a ledeken
			led_idx = 0;
			if (wait_cnt > 0) wait_cnt--;	//csökkentjük a várakozási idõt
			if (wait_cnt == 0)
			{
				//vége a várakozásnak, mehet a következõ kép
				cycle_idx++;
				buffer_offset += 13;
				if (cycle_idx >= CYCLE_NUM)
				{
					//a teljes animáció lement, kezdjük elõrõl
					cycle_idx = 0;
					buffer_offset = 0;
					//és jelezzük, hogy az "anim" puffer felsõ felét fel lehet tölteni
					calc_event = 2;
				}
				if (cycle_idx == CYCLE_NUM/2)
				{
					//jelezzük, hogy az "anim" puffer alsó felét fel lehet tölteni
					calc_event = 1;
				}
				
				wait_cnt = wait[cycle_idx]; //ennyit kell majd várni
			}
		}
	}
}