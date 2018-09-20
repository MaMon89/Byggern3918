#include <avr/io.h>
#include "UART.h"
#include <stdio.h>




void UART_Init(unsigned int ubrr)
{
	// Baud rate
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)(ubrr);
	
	// Enable Rx and Tx
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) ;
	UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
	fdevopen(UART_TX, UART_RX);
}

int UART_TX(char data, FILE * _in){
	(void)(_in);
	
	while( !(UCSR0A & (1 << UDRE0)) );
	
	// send data
	UDR0 = data;
	
	return 0;
}

int UART_RX(FILE * _in ){
	(void)(_in);
	while( !(UCSR0A & (1 << RXC0)) );
	
	// Data recieved
	return UDR0;
}