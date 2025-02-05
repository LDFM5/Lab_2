/*
 * LCD.h
 *
 * Created: 30/01/2025 19:08:51
 *  Author: luisd
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000
#include <avr/delay.h>
#include <avr/io.h>

#define RS (1<<PORTD2)
#define E (1<<PORTD3)
#define D0 (1<<PORTD4)
#define D1 (1<<PORTD5)
#define D2 (1<<PORTD6)
#define D3 (1<<PORTD7)
#define D4 (1<<PORTB0)
#define D5 (1<<PORTB1)
#define D6 (1<<PORTB2)
#define D7 (1<<PORTB3)

void initLCD8bits(void);

void LCD_Port(char a);

void LCD_CMD(char a);

void LCD_Write_Char(char c);

void LCD_Write_String(char *a);

void LCD_Shift_Right(void);

void LCD_Shift_Left(void);

void LCD_Set_Cursor(char c, char f);

#endif /* LCD_H_ */