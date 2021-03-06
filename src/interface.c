/********************************
 * INTERFACE LIBRARY
 * For LCD and/or serial
 * 
********************************/
#include <stdio.h>
#include <avr/pgmspace.h>
#include <src/hd44780.h>
#include "interface.h"
#include <stdlib.h>
#include <string.h>
#include <src/uart.h>

void lcd_display(uint8_t x, uint8_t y, char buffer[33]){
	#if defined NEED_LCD
		lcd_gotoxy(x, y);
		lcd_puts(buffer);
	#endif
}

void serial_display(float rpm){
	#if defined NEED_SERIAL
		unsigned char arr[10];
		snprintf(arr, sizeof(rpm)+3, "%.1f", rpm);
		for(int g=0; g<strlen(arr); g++){
			//Send back to terminal
			uart_putc((uint8_t)arr[g]);
		}
	#endif
}

void serial_rpm(float rpm, float hertz){
	#if defined NEED_SERIAL
		unsigned char arr[10];
		snprintf(arr, sizeof(rpm)+3, "%.2f", rpm);
		for(int g=0; g<strlen(arr); g++){
			//Send back to terminal
			uart_putc((uint8_t)arr[g]);
		}
		uart_putc(32);
		uart_puts_P("rpm");
		uart_putc(9);
		//uart_putc("#");
		snprintf(arr, sizeof(hertz)+3, "%.2f", hertz);
		for(int g=0; g<strlen(arr); g++){
			//Send back to terminal
			uart_putc((uint8_t)arr[g]);
		}
		uart_putc(32);
		uart_puts_P("Hz");
		uart_putc(10);
	#endif
}
