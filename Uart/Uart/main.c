/*
 * Uart.c
 *
 * Created: 04.09.2018 09.43.47
 * Author : Grendar
 */ 


#define F_CPU 4912500 /*4912500UL*/
#define BAUD 9600
#define UBRREG F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "UART.h"

void SRAM_test(void);

int main(void)
{
//	MCUCR= (1<<SRE);
	SFIOR =(1<<XMM2);

	DDRA = 0x01;
	DDRC |= 0b00000111;
	//unsigned int a = 0;
	UART_Init(UBRREG);
	printf("----T1N6 5UNK---- \n\r");
//	SRAM_test();
	 
	while(1){
		PORTC |= 0b00000110;
		_delay_ms(100);
		PORTC &= 0b00000100;
		_delay_ms(100); 
		
	/*	PORTA |= (1 << 0);
		_delay_ms(500);
		PORTA &= ~ (1 << 0);
		_delay_ms(500);
		printf("Jeg skrev; %c\n\r",UART_RX());*/
	}
	return 0;
}

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) 
		{
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i,retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n\r",i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase \n \n", write_errors, retrieval_errors);
}