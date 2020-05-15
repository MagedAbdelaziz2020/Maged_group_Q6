/*
 * Master .Smart Home Maged.c
 *
 * Created: 13/05/2020 08:55:25 ã
 * Author : MAGED
 */ 

#define F_CPU	16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#define MOSI	5
#define MISO	6
#define SCK		7
#define CS		0

#define SS_ENABLE()		PORTC&=~(1<<CS)
#define SS_DISABLE()	PORTC|=(1<<CS)

#define LED0	5
#define LED1	6
#define LED2	7

#define BAUD   9600
#define BAUD_EQ		((F_CPU/(BAUD*16UL))-1)

void SPI_Init();
char uartReceive();
void uartInit();
void uartSend(char data);
unsigned char SPI_Transfer(unsigned char sendByte);

//Serial Com , interrupt Service Routine 
volatile ISR(USART_RXC_vect)
{
	//uartInit();
	char ReceivedByte ;
	ReceivedByte = UDR;  // Retrieves byte from serial port ( bluetooth Module ) 
	switch(ReceivedByte)     // Tested By RealTerm & Configure Virtual Serial Port Drive Program
	{
		case 'R':   //Case 'R' LED 1 Room 1 set on
		SS_ENABLE();
		unsigned char recvByte=SPI_Transfer(0xAA);
		SS_DISABLE();
		_delay_ms(1000);
		if(recvByte==0x11)
		{
			PORTD=(1<<LED0);    
		}
		uart_sendString("LED_1_ROOM_1_ON\r\n");
		_delay_ms(5000);
		break;
		//***********************
		
		case 'RO':         //Case 'RO' LED 1 Room 1 set off
		SS_ENABLE();
		         recvByte=SPI_Transfer(0x0A);
		SS_DISABLE();
		if (recvByte==0x01)
		{
			PORTD^=(1<<LED0);
		}
		_delay_ms(1000);
		uart_sendString("LED_1_ROOM_1_OOF\r\n");
		_delay_ms(3000);
		break;
		
		//************************************
		case 'RR':             //Case 'RR' LED 2 Room 1 set on
		SS_ENABLE();
		 recvByte=SPI_Transfer(0xBB);
		SS_DISABLE();
		if (recvByte==0x22)
		{
			PORTD=(1<<LED1);
		}
		_delay_ms(1000);
		uart_sendString("LED_2_ROOM_1_ON\r\n");
		_delay_ms(3000);
		break;
		
		//************************************
		case 'RRO':           //Case 'RRO' LED 2 Room 1 set off
		SS_ENABLE();
	    recvByte=SPI_Transfer(0x0B);
		SS_DISABLE();
		if (recvByte==0x02)
		{
			PORTD^=(1<<LED1);
		}
		_delay_ms(1000);
		uart_sendString("LED_2_ROOM_1_OOF\r\n");
		_delay_ms(3000);
		break;
		
		default :
		break;  
	}
}
	void uartInit(){
		//Setting Baud Rate
		UBRRL=BAUD_EQ;
		//Enable RX and TX
		UCSRB =(1<<RXEN)|(1<<TXEN);
		//select frame size and number of stop bits Enable UART
		UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	}
void uartSend(char data){
	
	while( !(UCSRA & (1<<UDRE)));										
	UDR=data;
}

char uartReceive(){
	while( !(UCSRA & (1<<RXC)));
	return UDR;
}
void uart_sendString(char *str){
	char i=0;
	while(str[i]!='\0'){
		uartSend(str[i]);
		i++;
	}
}
void SPI_Init(){
	
	DDRB|=(1<<MOSI)|(1<<SCK);
	DDRC|=(1<<CS);
	
	SPCR|=(1<<MSTR)|(1<<SPE)|(1<<SPR0);
}
unsigned char SPI_Transfer(unsigned char sendByte){
	
	SPDR=sendByte;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}



int main(void)
{
	uartInit();
	sei(); // Global Interrupt Enable
	

	while (1)
	{
		uart_sendString("SMART_HOME_MAGED\r\n");
		_delay_ms(2000);
	}
}

