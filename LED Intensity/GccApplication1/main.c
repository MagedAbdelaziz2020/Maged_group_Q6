/*
 * GccApplication1.c
 *
 * Created: 24/04/2020 03:18:02 م
 * Author : MAGED
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    // Direction  OC0 out put
	DDRB|=(1<<3); 
	//TIMER 0 AT NO PRESCALE AND FAST PWM , INVERTING MODE
	TCCR0=(1<<CS00)|(1<<WGM00)|(1<<WGM01)|(1<<COM00)|(1<<COM01);
    while (1) 
    {
		// LED to be DIMMED
		OCR0=127;
    for(int i=0;i<255;i++)
		{
			OCR0=i;
			_delay_ms(50);
    }
	OCR0=254;
	for(int i=0;i<255;i++)
	{
		OCR0=i;
		_delay_ms(50);
	}
	for(int i=255;i>0;i--)
	{
		OCR0=127;
		_delay_ms(50);
	} 
	for(int i=255;i>0;i--)
	{
		OCR0=i;
		_delay_ms(50);
	}
	
		 //for
	}//while 1
}//main
	

