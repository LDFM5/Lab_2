/*
 * Lab_2.c
 *
 * Created: 30/01/2025 19:08:20
 * Author : luisd
 */ 

#define F_CPU 16000000
#include <avr/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "LCD/LCD.h"
#include "ADC/ADC.h"
#include "UART/UART.h"

volatile uint8_t valorADC=0;
volatile uint8_t contador=0;
volatile uint8_t PuertoADC=3;
volatile uint8_t valor = 0;
volatile float valor_reescalado = 0;
volatile char opcion;

char buffer[5];
char buffer2[5];

void init_pines(void){
	// Configurar los pines PC4 y PC5 como entradas
	DDRC &= ~(1 << DDC4) & ~(1 << DDC5);
	PORTC = 0;
	
	sei();
}

float reescalar(uint8_t valor, uint8_t max_origen, uint8_t max_destino) {
	// Escalar el valor al rango 0 - max_destino
	float valor_reescalado = (float)valor / max_origen * max_destino;
	return valor_reescalado;
}

int main(void)
{
	initLCD8bits();
	init_pines();
	init_ADC(0,0,128);
	initUART9600();
	
	LCD_Set_Cursor(2,1);
	LCD_Write_String("S1:");
	LCD_Set_Cursor(5,2);
	LCD_Write_Char('V');
	LCD_Set_Cursor(8,1);
	LCD_Write_String("S2:");
	LCD_Set_Cursor(11,2);
	LCD_Write_Char('V');
	LCD_Set_Cursor(13,1);
	LCD_Write_String("S3:");
	LCD_Set_Cursor(13,2);
	LCD_Write_String("0");
	
	
	
    /* Replace with your application code */
    while (1) 
    {
		//LCD_Shift_Right();
		if (PuertoADC==6) {
			valor = readADC(4);
			valor_reescalado = reescalar(valor, 255, 5);
			memset(buffer, 0, sizeof(buffer));
			dtostrf(valor_reescalado, 1, 2, buffer);
			writeTextUART("P1:");
			writeTextUART(buffer);
			writeTextUART("\n");
			
			LCD_Set_Cursor(7,2);
			LCD_Write_String(buffer);
			PuertoADC++;
		} else if (PuertoADC==7) {
			valor = readADC(5);
			valor_reescalado = reescalar(valor, 255, 5);
			memset(buffer, 0, sizeof(buffer));
			dtostrf(valor_reescalado, 1, 2, buffer);
			writeTextUART("P2:");
			writeTextUART(buffer);
			writeTextUART("\n");
			
			LCD_Set_Cursor(1,2);
			LCD_Write_String(buffer);
			PuertoADC++;
		} else {
			PuertoADC = 6;
		}
		_delay_ms(500);
    }
}

ISR(USART_RX_vect){
	opcion = UDR0;
	
	if (opcion == '+'){
		contador++;
		itoa(contador, buffer2, 10);
		LCD_Set_Cursor(13,2);
		LCD_Write_String("   ");
		LCD_Set_Cursor(13,2);
		LCD_Write_String(buffer2);
		//writeTextUART(buffer2);
	} else if (opcion == '-') {
		contador--;
		itoa(contador, buffer2, 10);
		LCD_Set_Cursor(13,2);
		LCD_Write_String("   ");
		LCD_Set_Cursor(13,2);
		LCD_Write_String(buffer2);
		//writeTextUART(buffer2);
	}
}