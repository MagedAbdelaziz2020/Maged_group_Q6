/*
 * Input_Capture_timer1.c
 *
 * Created: 06/05/2020 06:16:57 م
 * Author : MAGED
 */ 
#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "dio_hw.h"
#include "dio_types.h"
#include "STD_Types.h"
#include "lcd.h"
#include "lcd_cfg.h"
#include "dio.h"


int main(void)
{
    unsigned int a,b,c,high,period;
	char frequency[14],duty_cy[7];
	
	LCD_Init(void);
	PORTD=0XFF;  /* Turn on pull-up Resistor*/
	
    while (1) 
    {
		TCCR1A = 0;
		TCNT1 = 0;
		TIFR = (1<<ICF1);/* Clear ICF (Input Capture flag) flag*/
		
		TCCR1B =0X41; /*Rising edge , No PreScaler */
		while((TIFR&(1<<ICF1))==0);
		a = ICR1; /* Take value of capture register*/
		TIFR = (1<<ICF1); /* Clear ICF flag*/
		
		TCCR1B =0X01; /* Falling edge , No PreScaler */
		while((TIFR&(1<<ICF1))==0);
		b = ICR1; /* Take value of capture register*/
		TIFR = (1<<ICF1); /* Clear ICF flag*/
		
		TCCR1B =0X41; /*Rising edge , No PreScaler */
		while((TIFR&(1<<ICF1))==0);
		c = ICR1; /* Take value of capture register*/
		TIFR = (1<<ICF1); /* Clear ICF flag*/
		
		
		TCCR1B =0; /* Stop the timer*/
		
		if(a<b && b<c)/* Check for valid condition, 
		        to avoid timer overflow reading */
		{
			high = b-a;  //falling edge time -rising edge time = ON
			period =c-a;  //time period =
			
			long freq=F_CPU/period;/* Calculate frequency*/
			
			   /* Calculate duty cycle */
			float duty_cycle =((float) high /(float)period)*100;
			ltoa(freq,frequency,10);
			//sprintf(frequency,"%d",freq);
			itoa((int)duty_cycle,duty_cy,10);
			
			LCD_Command(0X80);
			LCD_String("Freq: ");
			LCD_String(frequency);
			LCD_String(" HZ   ");
			
			
			LCD_Command(0XC0);
			LCD_String("Duty: ");
			LCD_String(duty_cy);
			LCD_String(" %    ");
			
		}
		
		else
		{
			LCD_Clear();
			LCD_String( "OUT OF RANGE !!" );
		}
		
		_delay_ms(50);
		
    }
}

