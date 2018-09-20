#include <stdint.h>

#ifndef UART_H_
#define UART_H_


void UART_Init(unsigned int ubrr);
int UART_TX(uint8_t data);
int UART_RX( void );

#endif 

