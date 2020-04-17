/*
	 * ExternalInterrupt.c
	 *
	 * Created: 9/28/2019 3:59:25 PM
	 * Author : Mohamed
	 */ 
	#define F_CPU 16000000
	#include <util/delay.h>
	#include <avr/io.h>
	#include <avr/interrupt.h>
	
	
	volatile unsigned char counter=0;
	#include "bit_math.h"
	
	#define TOGGLE_LED()	TOGGLE_BIT(PORTB,2)
	#define SevenSeg_PORT   PORTA
	#define SevenSeg_EN_PORT PORTB
	#define SevenSeg_EN_DIR  DDRB
	#define SevenSEG_EN1    (1<<1) //PB1
	#define SevenSEG_EN2    (1<<2)//PB2
	
	#define SevenSeg_direction	DDRA		/* define LED Direction */
	#define SevenSeg_PORT		PORTA
	
	void ExInterrupt_Init(){
		CLR_BIT(DDRD,2); //PD2 as input to Led 0,1,2
		GICR=(1<<INT0);   //Enable External Interrupts INT1
		MCUCR  &=~(1<<ISC00);       //falling edge
		MCUCR  |=(1<<ISC01);       //falling edge
	
		sei();     // Enable global interrupts by setting global interrupt enable bit in SREG
	}
	/*
	
	*/
	void sevenSegment(){
				SevenSeg_EN_PORT |= SevenSEG_EN1 | SevenSEG_EN2; //Enable Seven Seg
				sevenSegment();
	
		char array[]={0,1,2,3,4,5,6,7,8,9};
		/* write BCD value for CA display from 0 to 9 */
	
		for(int i=0;i<10;i++)
		{
			
			SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
			//_delay_ms(100); /* wait for 500 melli second */
		}
	}
	int main(void)
	{
		 ExInterrupt_Init();
		//Seven segment pins to be output
		SevenSeg_direction |=(1<<4) |(1<<5) | (1<<6) | (1<<7);//PA4 to PA7
		SevenSeg_EN_DIR |= SevenSEG_EN1 | SevenSEG_EN2; //PB1 , PB2 are output for EN sv
	    while (1) 
	    {
			if( GET_BIT(PIND,2)==1)
			{_delay_ms(30);  //debounce time
						SevenSeg_EN_PORT |= SevenSEG_EN1 | SevenSEG_EN2; //Enable Seven Seg
						sevenSegment();
				          char array[]={0,1,2,3,4,5,6,7,8,9};
				/* write BCD value for CA display from 0 to 9 */
				for(int i=0;i<10;i++)
				{
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					_delay_ms(100); /* wait for 500 melli second */
				                
				}
		        }else if( GET_BIT(PIND,2)==1)
			                    {_delay_ms(30);      //debounce time
						   char array[]={0,1,2,3,4,5,6,7,8,9};
				     /* write BCD value for CA display from 0 to 9 */
					        	for(int i=0;i<1;i++)
						        {
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
				}
				}else if( GET_BIT(PIND,2)==1)
						        {_delay_ms(30);      //debounce time
							char array[]={0,1,2,3,4,5,6,7,8,9};
					/* write BCD value for CA display from 0 to 9 */
							   for(int i=0;i<2;i++)
							    {
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
				}
				}else if( GET_BIT(PIND,2)==1)
							    {_delay_ms(30);      //debounce time
						  char array[]={0,1,2,3,4,5,6,7,8,9};
					/* write BCD value for CA display from 0 to 9 */
						        for(int i=0;i<3;i++)
					            {			
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
				}
				}else if( GET_BIT(PIND,2)==1)
								{_delay_ms(30);      //debounce time
							char array[]={0,1,2,3,4,5,6,7,8,9};
					/* write BCD value for CA display from 0 to 9 */
							    for(int i=0;i<4;i++)
								{
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
				}
				}else if( GET_BIT(PIND,2)==1)
							    {_delay_ms(30);      //debounce time
							char array[]={0,1,2,3,4,5,6,7,8,9};
					/* write BCD value for CA display from 0 to 9 */
								for(int i=0;i<5;i++)
							    {
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
				}
				}else if( GET_BIT(PIND,2)==1)
								{_delay_ms(30);      //debounce time
							char array[]={0,1,2,3,4,5,6,7,8,9};
					/* write BCD value for CA display from 0 to 9 */
								for(int i=0;i<6;i++)
								{
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
				}
				}else if( GET_BIT(PIND,2)==1)
								{_delay_ms(30);      //debounce time
							char array[]={0,1,2,3,4,5,6,7,8,9};
			    	/* write BCD value for CA display from 0 to 9 */
								for(int i=0;i<7;i++)
								{										
		    		SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
				}
				}else if( GET_BIT(PIND,2)==1)
								{_delay_ms(30);      //debounce time
						    char array[]={0,1,2,3,4,5,6,7,8,9};
					/* write BCD value for CA display from 0 to 9 */

								for(int i=0;i<8;i++)
								{	
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
				}
				}else if( GET_BIT(PIND,2)==1)
			                    {_delay_ms(30);      //debounce time
						    char array[]={0,1,2,3,4,5,6,7,8,9};
					/* write BCD value for CA display from 0 to 9 */

			                   for(int i=0;i<9;i++)
		                        {								
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
			   	}
				}else if( GET_BIT(PIND,2)==1)
								{_delay_ms(30);      //debounce time
						    char array[]={0,1,2,3,4,5,6,7,8,9};
					/* write BCD value for CA display from 0 to 9 */
								for(int i=0;i<10;i++)
								{	
					SevenSeg_PORT = ( array[i] <<4);/* write data on to the LED port */
					//_delay_ms(100); /* wait for 500 melli second */
				}
			}
	    }  
    }
			
	
	//sevenSegment();
		//ISR (INT0_vect){
		//Do something
		//TOGGLE_LED();
		
		
	
	/*
	
	*/


