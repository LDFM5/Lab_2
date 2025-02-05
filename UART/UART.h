/*
 * UART.h
 *
 * Created: 2/02/2025 19:56:02
 *  Author: luisd
 */ 

#include <avr/eeprom.h>

#ifndef UART_H_
#define UART_H_

void initUART9600(void);
void writeUART(char caracter);
void writeTextUART(char* texto);

#endif /* UART_H_ */