/*
 * LCD.c
 *
 * Created: 30/01/2025 19:09:02
 *  Author: luisd
 */ 
#include "LCD.h"

void initLCD8bits(void){
	// Configurar D2 - D7 como salidas (PD2 - PD7)
	DDRD |= 0b11111100; // (1 en PD2-PD7) 

	// Configurar D8 - D11 como salidas (PB0 - PB3)
	DDRB |= 0b00001111; // (1 en PB0-PB3)
	
	// Asegurar que todas las salidas inicien en 0
	PORTD &= ~0b11111100; // Poner en 0 D2-D7
	PORTB &= ~0b00001111; // Poner en 0 D8-D11
	
	LCD_Port(0x00);
	_delay_ms(20);
	LCD_CMD(0x38);
	LCD_CMD(0x0C);
	LCD_CMD(0x06);
	LCD_CMD(0x01);
}

void LCD_CMD(char a){
	PORTD &= ~RS;
	LCD_Port(a);
	PORTD |= E; 
	_delay_ms(4);
	PORTD &= ~E;
}

void LCD_Port(char a){
	if (a & 1)
	PORTD |= D0;
	else
	PORTD &= ~D0;
	
	if (a & 2)
	PORTD |= D1;
	else
	PORTD &= ~D1;
	
	if (a & 4)
	PORTD |= D2;
	else
	PORTD &= ~D2;
	
	if (a & 8)
	PORTD |= D3;
	else
	PORTD &= ~D3;
	
	if (a & 16)
	PORTB |= D4;
	else
	PORTB &= ~D4;
	
	if (a & 32)
	PORTB |= D5;
	else
	PORTB &= ~D5;
	
	if (a & 64)
	PORTB |= D6;
	else
	PORTB &= ~D6;
	
	if (a & 128)
	PORTB |= D7;
	else
	PORTB &= ~D7;
}

void LCD_Write_Char(char c){
	PORTD |= RS;
	LCD_Port(c);
	
	PORTD |= E;
	_delay_ms(4);
	PORTD &= ~E;
}

void LCD_Write_String(char *a){
	int i;
	for (i = 0; a[i] != '\0'; i++)
	LCD_Write_Char(a[i]);
}

void LCD_Shift_Right(void){
	LCD_CMD(0x1C);
}

void LCD_Shift_Left(void){
	LCD_CMD(0x18);
}

void LCD_Set_Cursor(char c, char f){
	char temp;
	if (f == 1){
		temp = 0x80 + c - 1;
		LCD_CMD(temp);
	} else if (f == 2){
		temp = 0xC0 + c - 1;
		LCD_CMD(temp);
	}
}