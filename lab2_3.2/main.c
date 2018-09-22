/*
 * lab2_3.2.c
 *
 * Created: 2018/9/19 17:33:25
 * Author : Lenovo
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "uart.h"

int main(void)
{
	uart_init();
	DDRC = 0x00;
	DDRB |= (1 << PORTB2);
	DDRB |= (1 << PORTD3);
	DDRB |= (1 << PORTB4);
	PORTB |= (1 << PORTB2) | (1 <<PORTB3) | (1 << PORTB4);
	PORTC |= (1 << PORTC0);
	
	ADMUX |= (1 << REFS0);         //reference 5V
	ADCSRA |= (1 << ADEN) | (1 << ADATE);          //enable ADC
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);  //factor 128
	ADCSRA |= (1 << ADSC);        //Start conversion
	ADCSRB &= ~((1 << ADTS0)|(1 << ADTS1)|(1 << ADTS2));    //free-running mode
	while (1)
	{
		if(ADC > 0 && ADC <= 128)
		{
			PORTB &= ~((1 << PORTB2) | (1 <<PORTB3) | (1 << PORTB4));
		}
		if(ADC > 128 && ADC <= 256)
		{
			PORTB &= ~((1 <<PORTB3) | (1 << PORTB4));
			PORTB |= (1 << PORTB2);
		}
		if(ADC > 256 && ADC <= 384)
		{
			PORTB &= ~((1 <<PORTB2) | (1 << PORTB4));
			PORTB |= (1 << PORTB3);
		}
		if(ADC > 384 && ADC <= 512)
		{
			PORTB &= ~((1 << PORTB4));
			PORTB |= (1 <<PORTB2) | (1 << PORTB3);
		}
		if(ADC > 512 && ADC <= 640)
		{
			PORTB &= ~((1 <<PORTB3) | (1 << PORTB2));
			PORTB |= (1 << PORTB4);
		}
		if(ADC > 640 && ADC <= 768)
		{
			PORTB &= ~((1 << PORTB3));
			PORTB |= (1 <<PORTB2) | (1 << PORTB4);
		}
		if(ADC > 768 && ADC <= 896)
		{
			PORTB &= ~((1 << PORTB2));
			PORTB |= (1 <<PORTB3) | (1 << PORTB4);
		}
		if(ADC > 896 && ADC <= 1024)
		{
			PORTB |= (1 << PORTB2) | (1 <<PORTB3) | (1 << PORTB4);
		}
	}
}

