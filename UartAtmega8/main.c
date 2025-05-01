/*
* UartAtmega8.c
*
* Created: 1.05.2025 16:31:24
* Author : mehmet
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

char buff[10];

void uart_init(int baudRate,unsigned long Fosc)
{
	int UBRRVAL = ((Fosc/(baudRate*16UL))-1);
	
	UBRRH =  (UBRRVAL>>8);
	UBRRL = (uint8_t)UBRRVAL;
	
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<URSEL) | (3<<UCSZ0) ;
}

void uart_send_c(char karakter)
{
	while( !(UCSRA & (1<<UDRE) ) );
	UDR = karakter;
}

void uart_send_str(char * mesaj)
{
	char c;
	while(*mesaj)
	{
		c=*mesaj;
		uart_send_c(c);
		mesaj++;
	}
}

void uart_send_int(int sayi)
{
	uart_send_str(itoa(sayi, buff, 10));
}


int main(void)
{
	
	uart_init(9600,F_CPU);
	DDRB |= (1<<PORTB1);

	while(1)
	{
		PORTB |= (1<<PORTB1);
		uart_send_str("a1");
		_delay_ms(500);
		PORTB &= ~(1<<PORTB1);
		uart_send_str("a0");
		_delay_ms(500);
	}
}
