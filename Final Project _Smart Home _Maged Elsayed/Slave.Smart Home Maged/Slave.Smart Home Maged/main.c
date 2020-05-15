/*
 * Slave.Smart Home Maged.c
 *
 * Created: 13/05/2020 09:56:25 م
 * Author : MAGED
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#define  SS		4
#define MOSI	5
#define MISO	6
#define LED0	5
#define LED1	6
#define LED2	7
unsigned char SPI_Transfer(unsigned char sendByte){
	
	SPDR =sendByte;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}
int main(void)
{
	/* I/O  Initialization  */
	DDRA|=(1<<PA0)|(1<<PA1)|(1<<PA2);//Dir1, Enable  Motor ROOM 3 Control , IN1,IN2,EN
	DDRD|=(1<<LED0);//|(1<<LED1)(1<<LED2); //LED0 ROOM 1 ,LED ROOM 1 , LED2 ROOM 2
	DDRB|=(1<<MISO);
	DDRB&=~(1<<SS); //input pin
	
	SPCR|=(1<<SPE);

    while (1) 
    {
		unsigned char recvByte=SPI_Transfer(0X11);
		_delay_ms(1000);
		if(recvByte==0XAA){
			PORTD=(1<<LED0);
			
			_delay_ms(5000);
		}
		else 
		{ 
			recvByte=SPI_Transfer(0X01);
			_delay_ms(1000);
			(recvByte==0X0A);
			PORTD^=(1<<LED0);
			
			_delay_ms(5000);
			
		}
		//*******************************************
		recvByte=SPI_Transfer(0X22);
		_delay_ms(1000);
		if(recvByte==0XBB){
			PORTD=(1<<LED1);
			
			_delay_ms(5000);
		}
		else
		{
			recvByte=SPI_Transfer(0X02);
			_delay_ms(1000);
			(recvByte==0X0B);
			PORTD^=(1<<LED1);
			
			_delay_ms(5000);
			
		}
    }
}






