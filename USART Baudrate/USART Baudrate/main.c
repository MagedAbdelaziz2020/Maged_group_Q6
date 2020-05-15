/*
 * USART Baudrate.c
 *
 * Created: 01/05/2020 03:02:10 م
 * Author : MAGED
 * Baud rate 9600 bps Normal mode
 * 8bits frame size
 * 1 stop bit , No Parity
 * TX EN      TO BLUETOOTH
 * UDR = 'M'
 */
#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>
#define BAUD   9600
#define BAUD_EQ  ((F_CPU/BAUD*16UL)-1)

int main(void)
{
	 //Initialize Baud rate
		UBRRL=BAUD_EQ;
		//TXEN and Receive
		UCSRB=(1<<TXEN)|(1<<RXEN);
		//Frame size 8 bits , no parity , one stop bit
		UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1); 
    while (1) 
    {
		//SEND DATA
		while(!(UCSRA&(1<<UDRE)));  // Polling
		UDR='M';
    }
}

