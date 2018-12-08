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

//ciklus, "LEDS_NUM" db egym�s ut�ni b�jt hat�rozza meg az �ppen kirakand� f�nyer�ket
//val�j�ban double buffered, ha az egyik sort kirakja, a m�sikat lehet �rni
byte cycles[CYCLE_NUM * LEDS_NUM] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	
};

//az aktu�lis ciklus meddig legyen kint (egys�g: PWM frekvencia. Pl. 180 = kb. 1sec)
byte wait[CYCLE_NUM] =
{
	10,
	10
};

byte cycle_idx = 0; //anim�ci� aktu�lis �llapot�t hat�rozza meg ("anim" t�mbben egy sort (LEDS_NUM b�jtot) jel�l ki)
byte buffer_offset = 0; //cycles t�mbben seg�t a c�mz�sben (l�nyeg�ben mindig cycle_idx * 13)
byte led_idx = 0; //a felvillantand� LED-et c�mzi
byte on_off = 0; //�ppen be (1) vagy ki (0) kell kapcsolni az adott LED-et
byte off_time = 0; //ennyi ideig kell majd kikapcsolva tartani (PWM-off time)
byte wait_cnt = 0; //ennyit kell m�g v�rni az aktu�lis k�p befejez�d�s�ig
byte calc_event = 0; //0 - nincs semmi
					 //1 - als� (cycles[0-12]) sort sz�molhatjuk
					 //2 - fels� (cycles[13-25]) sort sz�molhatjuk
byte calc_state = 0; //itt t�roljuk, hogy hol tartunk az anim�ci�ban
byte calc_offset = 0; //a cycles pufferhez egy offszet (hogy hova kell �rni a sz�mol�s eredm�ny�t)

int main(void)
{
	MCUCR |= 0x40; // pullup disable (PUD) -> if pin is configured input, the pin goes High-Z
	LED_OFF();
	TCCR0A = 0; //normalest normal mode
	TCCR0B = 0x04; //256 prescaler
	TCNT0 = 250; //Ezt csak random be�ll�tjuk, hogy (majdnem) azonnal lej�rjon
	TIMSK0 = 0x02; //TOIE0: Timer/Counter0 Overflow Interrupt Enable

	sei();

	//Ezt a r�szt sokszor megszak�thatja (�s meg is fogja) az interrupt -> Igyekezz�nk.
    while (1)
    {
		byte calc_event_tmp = 0;
		cli();		//Itt most nem tesz j�t ha bej�nne egy IT (elronthatja calc_event-et �tk�zben)
		calc_event_tmp = calc_event;
		calc_event = 0;
		sei();
		if (calc_event_tmp > 0)
		{
			if (calc_event_tmp == 1) //als� r�sz szabad
			{
				calc_offset = 0;
			}
			else if (calc_event_tmp == 2) //fels� r�sz szabad
			{
				calc_offset = 0 + CYCLE_NUM/2 * LEDS_NUM;
			}
			//BEGIN Anim�ci� sz�mol�sa (calc_state f�ggv�ny�ben)
			for (byte i = 0; i < LEDS_NUM; i++)
			{
				//csak egym�s ut�n felvillantjuk a ledeket
				cycles[calc_offset + i] = 0;
				if (i == calc_state)
				{
					cycles[calc_offset + i] = 15;
				}
			}
			wait[cycle_idx] = 10;	//1 sec = 180

			calc_state++;
			if (calc_state >= 13) calc_state = 0;  //Itt annyit kell �rni a felt�telbe, ah�ny �llapota van az anim�ci�nak
			//END Anim�ci� sz�mol�sa
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
		on_off = 1;		//K�vi �llapot ON
	}
	else
	{
		//ON
		if (cycles[buffer_offset + led_idx] == 0) //Ha a fenyero min, nem kell semmit bekapcsolni, azonnal off �llapotba megy�nk
		{
			//TIFR0 |= 0x02; //Set TOV0
			TCNT0 = 256 - 16;
			LED_OFF();
		}
		else
		{
			TCNT0 = 256 - cycles[buffer_offset + led_idx];			//ennyi ideig kell bekapcsolni a ledet
			off_time = 256 - (16 - cycles[buffer_offset + led_idx]); //kikapcs id�t is kisz�moljuk
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
			//v�gigment�nk a ledeken
			led_idx = 0;
			if (wait_cnt > 0) wait_cnt--;	//cs�kkentj�k a v�rakoz�si id�t
			if (wait_cnt == 0)
			{
				//v�ge a v�rakoz�snak, mehet a k�vetkez� k�p
				cycle_idx++;
				buffer_offset += 13;
				if (cycle_idx >= CYCLE_NUM)
				{
					//a teljes anim�ci� lement, kezdj�k el�r�l
					cycle_idx = 0;
					buffer_offset = 0;
					//�s jelezz�k, hogy az "anim" puffer fels� fel�t fel lehet t�lteni
					calc_event = 2;
				}
				if (cycle_idx == CYCLE_NUM/2)
				{
					//jelezz�k, hogy az "anim" puffer als� fel�t fel lehet t�lteni
					calc_event = 1;
				}
				
				wait_cnt = wait[cycle_idx]; //ennyit kell majd v�rni
			}
		}
	}
}