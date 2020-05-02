/*
 * timer 0.c
 *
 * Created: 18/04/2020 05:57:33 م
 * Author : MAGED
 */ 
#define F_CPU  16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_math.h"
#include <util/delay.h>
#define TOGGLE(var,bit)      var^=(1<<bit)
volatile unsigned int counter=0;
int main(void)
{
	//volatile unsigned int counter=0;
	//prescaler clk/64   CS02=0  CS01=1  CS00=1
	TCCR0=(1<<CS00)|(1<<CS01); // 0000 0011
	//Generate timer 0 Overflow interrupt enable
	TIMSK=(1<<TOIE0);
	//LED 0 output pin pc2
	DDRC=(1<<2);     // led 0   pin pc2
	DDRC|=(1<<7);    // led 1   pin pc7
	DDRD=(1<<3);     // led 2   pin pd3
	//Global interrupt
	sei();
	while(1)
		{
		if(counter>=50)//100ms
		{
			    PORTC^=(1<<2);
				_delay_ms(10);
		      // counter=0;
	    	}
			 if(counter>=100)//100ms
			{
				PORTC^=(1<<7);
				_delay_ms(10);
				//counter=0;
			}
			 if(counter>=150)//100ms
			{
				PORTD^=(1<<3);
				_delay_ms(10);
				counter=0;
			}

     }
}
//main
//*****************************
ISR(TIMER0_OVF_vect){
	counter++;
}


//PORTC^=(1<<2);   //toggle led 0
//PORTC^=(1<<7);   //toggle led 1
//PORTD^=(1<<3);   //toggle led 2


