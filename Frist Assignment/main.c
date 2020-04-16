/*
 * GccApplication Group 6.c
 *
 * Created: 04/04/2020 01:19:55 م
 * Author : MAGED
 */ 
#define F_CPU  16000000
#include <avr/io.h>  //registers AVR prephierals
#include <util/delay.h>
#include "bit_math.h"


int main(void)
{
  CLEAR_BIT(DDRB,0); //PB0 as input to Buzzer
  CLEAR_BIT(DDRB,4); //PB4 as input to Relay
  CLEAR_BIT(DDRD,2); //PD2 as input to Led 0,1,2
  
  SET_BIT(DDRA,3);   //PA3 Buzzer   an output pin
  SET_BIT(DDRA,2);   //PA2 Relay    an output pin
  SET_BIT(DDRC,2);   //PC2  Led 0   an output pin
  SET_BIT(DDRC,7);   //PC7  Led 1   an output pin
  SET_BIT(DDRD,3);   //PD3  Led 2   an output pin
 
  
    while (1) 
    {
		if(GET_BIT(PINB,0)==1){ //BUTTON Active high
			_delay_ms(30);      //debounce time
			SET_BIT(PORTA,3);   // Buzzer is on 
			_delay_ms(1500);    //to realize output
			}
			else if(GET_BIT(PINB,4)==1){ //BUTTON Active high
				_delay_ms(30);      //debounce time is on
				SET_BIT(PORTA,2);   // Relay is on
				_delay_ms(2000);    //to realize output)
				}
				else if(GET_BIT(PIND,2)==1){ //BUTTON Active high
					_delay_ms(30);      //debounce time
					SET_BIT(PORTC,2);   // Led 0 is on
					_delay_ms(500);    //to realize output)
					SET_BIT(PORTC,7);   // Led 1 is on
					_delay_ms(500);    //to realize output)
					SET_BIT(PORTD,3);   // Led 2 is on
					_delay_ms(500);    //to realize output)
				}
	else{
		CLEAR_BIT(PORTA,3);
		CLEAR_BIT(PORTA,2);
		CLEAR_BIT(PORTC,2);
		CLEAR_BIT(PORTC,7);
		CLEAR_BIT(PORTD,3);
		_delay_ms(100);
	}
  }
}

