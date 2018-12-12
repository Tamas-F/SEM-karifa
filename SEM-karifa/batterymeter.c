/*
 * BatteryMeter.c
 *
 * Created: 2018. 12. 10. 18:56:40
 *  Author: Balint
 */ 

#include "buttons.h"
#include "commons.h"
#include "leds.h"

#define	F_CPU 1000000UL
#include "util/delay.h"
#include <avr/io.h>



//#define fullValue		85		//1.1*255/chargedVoltage
//#define dischargedADvalue	112	//1.1*255/dischargedVoltage

#define fullValue			100		//1.1*255/chargedVoltage
#define dischargedADvalue	148	//1.1*255/dischargedVoltage

#define dispRes 7

void initAD()
{	
	
	ADMUX = 0b00100001;  //[7:6]=select Vcc to ADref, [5:0] select ADchannel to Internal reference channel
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1); //Enable ADC, Select 64 prescaller
	ADCSRB = (1<<ADLAR); //left adjust result
	bit_clr(&PRR, PRADC);
	
	_delay_ms(5);
	//ide be kell tenni 1-2 msec késleltetést a referenca beállás miatt!!
}

void disableAD()
{
	bit_clr(&ADCSRA, ADEN);
	bit_set(&PRR, PRADC);
}

byte batteryMeasure()
{
	byte ADresult;
	byte batteryLevel;
	
	//adconversion
	bit_set(&ADCSRA, ADSC); //start AD conversion
	_nop();
	while(!bit_get(&ADCSRA, ADIF));	//wait for conversion ending

	ADresult = ADCH;
	//ADresult = 84;	//Teszt
	
	if(ADresult > dischargedADvalue){	//Biztonsági rész ha túl alacsonya led akkor ne forduljon körbe
		ADresult = dischargedADvalue;
	}
	//batteryLevel = (ADresult-(dischargedADvalue)) * (dispRes / (fullValue-dischargedADvalue)); //calculate how many LED-s lighting
	//batteryLevel = (112-ADresult)/4;	// 27/7 ~= 4
	batteryLevel = ((ADresult - dischargedADvalue) * dispRes) / (fullValue-dischargedADvalue);
	return batteryLevel;

	//TEST AD	
	//PORTA = 0;
	//bit_wrt(bit_get(&ADresult, 7), &PORTA, LINE0_PIN);
	//bit_wrt(bit_get(&ADresult, 6), &PORTA, LINE1_PIN);
	//bit_wrt(bit_get(&ADresult, 5), &PORTA, LINE2_PIN);
	//bit_wrt(bit_get(&ADresult, 4), &PORTA, LINE3_PIN);
	//bit_wrt(bit_get(&ADresult, 3), &PORTA, LINE4_PIN);
	//bit_wrt(bit_get(&ADresult, 2), &PORTA, LINE5_PIN);
	//bit_wrt(bit_get(&ADresult, 1), &PORTA, LINE6_PIN);
	
	//create display data
	//set_oldal_bal();
//
	PORTA = 0;
	if(batteryLevel >= 1){
		bit_set(&PORTA, LINE0_PIN);
	}
	if(batteryLevel >= 2){
		bit_set(&PORTA, LINE1_PIN);
	}
	if(batteryLevel >= 3){
		bit_set(&PORTA, LINE2_PIN);
	}
	if(batteryLevel >= 4){
		bit_set(&PORTA, LINE3_PIN);
	}
	if(batteryLevel >= 5){
		bit_set(&PORTA, LINE4_PIN);
	}
	if(batteryLevel >= 6){
		bit_set(&PORTA, LINE5_PIN);
	}
	if(batteryLevel >= 7){
		bit_set(&PORTA, LINE6_PIN);
	}
}

