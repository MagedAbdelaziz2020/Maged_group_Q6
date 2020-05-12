/*
 * NEW DC Motor Speed Control.c
 *
 * Created: 11/05/2020 06:02:08 م
 * Author : MAGED
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <util/delay.h> 
#include <avr/interrupt.h>
#define F_CPU  1000000UL 
#define BAUD 9600
#define MYUBRR   F_CPU/16/BAUD-1  //Asynchronous Normal Mode USART

//Serial Com , interrupt Service Routine or Button Switch 
ISR(USART_RXC_vect)
{
	char ReceivedByte ;
	ReceivedByte = UDR;  // Retrieves byte from serial port ( bluetooth Module )
	switch(ReceivedByte)
	{
		case 'U':
		if(OCR0 <= 255)
		OCR0 += 10;
		PORTB&=~(1<<PB5); // Red LED Is Off
		PORTB|=(1<<PB7);  //Green Led is turn on
		_delay_ms(150);
		PORTB&=~(1<<PB7);  //Green Led is turn off
		break; // Increase PWM duty cycle by 10
		
		case 'D':
		if(OCR0 >= 0)
		OCR0 -= 10;
		PORTB|=(1<<PB6); //turn on yellow LED
		_delay_ms(150);
		PORTB&=~(1<<PB6); // turn off yellow LED
		break;  //Decrease PWM duty cycle by 10
		
		case 'F' :
		PORTB&=~(1<<PB1);  //clear Dir pin
		PORTA&=~(1<<PA1);  //clear Dir pin
		PORTB|=(1<<PB0);    // in 1 =1
		PORTA|=(1<<PA0);    // in 3 =1
		break; // change motor direction to forward
		
		
	case 'B'  :
	PORTB&=~(1<<PB0);   // clear direction pin
	PORTA&=~(1<<PA0);   // clear direction pin
	PORTB|=(1<<PB1);     //  in2 =1
	PORTA|=(1<<PA1);	 //  in4 =1
	break;  // Change motor Direction to be Backward
	
	case 'R'  :
	PORTB&=~(1<<PB0);   // clear direction pin
	PORTB&=~(1<<PB1);   // clear direction pin
	PORTA&=~(1<<PA0);   // clear direction pin
	PORTA&=~(1<<PA1);   // clear direction pin
	PORTB|=(1<<PB0);           //in1 =1
	break;  // changed Motor Direction to Right
	
	case 'L'  :
	PORTB&=~(1<<PB0);   // clear direction pin
	PORTB&=~(1<<PB1);   // clear direction pin
	PORTA&=~(1<<PA0);   // clear direction pin
	PORTA&=~(1<<PA1);   // clear direction pin
	PORTA|=(1<<PA0);          //in3  =1
	break;  // changed Motor Direction to Left
	
	case 'S'  :
	PORTB |= 0b11; //in1 ,in2 =1
	PORTA |= 0b11; //in3 ,in4 =1
	OCR0 = 0;
	PORTB |=(1<<PB5);  // Red Led Will turn on
	break; // Stop Motor by Raising both Direction input , PWM duty cycle %0
	
	default :  
	break;  // character unknown to my routine , discard character
	}
}

int main(void)
{
    /* I/O  Initialization  */
	DDRB |=(1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB5)|(1<<PB6)|(1<<PB7);//Dir1, Enable 1 ,PWM pin & 3 LEDS as Output
	DDRA |=(1<<PA0)|(1<<PA1); // Dir2 , Enable Pins
	PORTB =0;  // All Initialized = 0
	PORTA =0;  // All Initialized = 0
	/*Timer 0 Initialization */
	TCCR0=(1<<WGM00)|(1<<WGM01); // Fast PWM Mode
	TCCR0|=(1<<COM01); // set OC0 (PB3) At Bottom NON Inverting Mode.. Note that OCR0 is Connected To ( EN 1,2 )
	TCCR0|=(1<<CS01); // PRESCALER /8
	TCNT0=0;  //Initialize TCNT0
	OCR0=0;   // Initialize PWM duty cycle to 0%
	/*UART  Initialization */
	UCSRB |=(1<<RXEN); // Enable RX 
	UCSRC =(1<<URSEL)|(1<<USBS)|(3<<UCSZ0); //UBBR Register Enable , Frame is 8 bit , one stop bit
	UCSRC =(1<<UPM1)|(1<<UPM0); // ODD Parity Enable
	UBRRL = MYUBRR;             // sets PAUDRATE Registers
	UBRRH =(MYUBRR>>8);         // sets PAUDRATE Registers
	UCSRB |=(1<<RXCIE);         // Enable USART Interrupt
	
	sei(); // Global Interrupt Enable
	/* this program is completely Interrupt driven , so nothing goes on in while loop*/
    while (1)  // Never Gets out from here !
	
	return 0;  // Never reaches this point !
	{
	}
}