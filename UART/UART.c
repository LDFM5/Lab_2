/*
 * UART.c
 *
 * Created: 2/02/2025 19:56:16
 *  Author: luisd
 */ 
#include "UART.h"

void initUART9600(void){
	DDRD &= ~(1 << DDD0);
	DDRD |= (1 << DDD1);
	
	UCSR0A = 0;
	UCSR0A |= (1 << U2X0);
	
	UCSR0B = 0;
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
	
	UCSR0C = 0;
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	
	UBRR0 = 207;
}

void writeUART(char caracter){
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = caracter;
}

void writeTextUART(char* texto){
	uint8_t i;
	for(i = 0; texto[i] != '\0'; i++){
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = texto[i];
	}
}