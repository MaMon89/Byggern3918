#include <stdint.h>
#include <stdio.h>

#ifndef UART_H_
#define UART_H_

void UART_Init(unsigned int ubrr);
int UART_TX(char data, FILE * _in);
int UART_RX(FILE * _in);

#endif 

