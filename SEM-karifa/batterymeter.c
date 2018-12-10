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

void initAD(){	
	
	
	//ide be kell tenni 1-2 msec késleltetést a referenca beállás miatt!!
}

void batteryMeasure(){
	
	ADMUX = 0b00100001;  //[7:6]=select Vcc to ADref, [5:0] select ADchannel to Internal reference channel
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1); //Enable ADC, Select 64 prescaller
	ADCSRB = (1<<ADLAR); //left adjust result
	
	
	byte ADresult;
	byte batteryLevel;
	
	//init AD
	initAD();
	
	//adconversion
	bit_set(&ADCSRA, ADSC); //start AD conversion
	while(bit_get(&ADCSRA, ADSC));	//wait for conversion ending
		
	//calc charge% 
	ADresult = ADCH;
	batteryLevel = (ADresult-emptyValue) * dispRes / (fullValue-emptyValue); //calculate how many LED-s lighting
	
	//create display data
	set_oldal_bal();
	
	if(batteryLevel > 1){
		bit_set(&PORTB, LINE0_PIN);		
	}
	if(batteryLevel > 2){
		bit_set(&PORTB, LINE1_PIN);
	}
	if(batteryLevel > 3){
		bit_set(&PORTB, LINE2_PIN);
	}
	if(batteryLevel > 4){
		bit_set(&PORTB, LINE3_PIN);
	}
	if(batteryLevel > 5){
		bit_set(&PORTB, LINE4_PIN);
	}
	if(batteryLevel > 6){
		bit_set(&PORTB, LINE5_PIN);
	}
	if(batteryLevel > 7){
		bit_set(&PORTB, LINE6_PIN);
	}
		
	_delay_ms(2000);
	
}