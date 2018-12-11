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


#define chargedVoltage 3.3
#define dischargedVoltage 2.5

#define fullValue 1.1*255/chargedVoltage	//ADin voltage * Resolution / +Rref 
#define emptyValue 1.1*255/dischargedVoltage
#define dispRes 7

void initAD()
{	
	
	ADMUX = 0b00100001;  //[7:6]=select Vcc to ADref, [5:0] select ADchannel to Internal reference channel
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1); //Enable ADC, Select 64 prescaller
	ADCSRB = (1<<ADLAR); //left adjust result
	
	_delay_ms(5);
	//ide be kell tenni 1-2 msec késleltetést a referenca beállás miatt!!
}

void batteryMeasure()
{
	byte ADresult;
	byte batteryLevel;
	
	//adconversion
	bit_set(&ADCSRA, ADSC); //start AD conversion
	_nop();
	while(!bit_get(&ADCSRA, ADIF));	//wait for conversion ending
	//calc charge% 
	ADresult = ADCH;
	batteryLevel = (ADresult-emptyValue) * dispRes / (fullValue-emptyValue); //calculate how many LED-s lighting
	
	//create display data
	set_oldal_bal();
	PORTA = ADresult;
	//PORTA = 0;
	//if(batteryLevel >= 1){
		//bit_set(&PORTA, LINE0_PIN);
	//}
	//if(batteryLevel >= 2){
		//bit_set(&PORTA, LINE1_PIN);
	//}
	//if(batteryLevel >= 3){
		//bit_set(&PORTA, LINE2_PIN);
	//}
	//if(batteryLevel >= 4){
		//bit_set(&PORTA, LINE3_PIN);
	//}
	//if(batteryLevel >= 5){
		//bit_set(&PORTA, LINE4_PIN);
	//}
	//if(batteryLevel >= 6){
		//bit_set(&PORTA, LINE5_PIN);
	//}
	//if(batteryLevel >= 7){
		//bit_set(&PORTA, LINE6_PIN);
	//}
}