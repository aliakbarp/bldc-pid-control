/********************************
 * INTERFACE LIBRARY
 * For LCD and/or serial
 * 
********************************/
#include <stdio.h>
#include <avr/pgmspace.h>
#include <src/hd44780.h>
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"

void lcd_display(uint8_t x, uint8_t y, char buffer[33]){
	#if defined NEED_LCD
		lcd_clrscr();
		lcd_gotoxy(x, y);
		lcd_puts(buffer);
	#endif
}

void serial_display(double rpm){
	#if defined NEED_SERIAL
		char arr[10]="";
		snprintf(arr, sizeof(rpm), "%.0f", rpm);
		for(int g=0; g<strlen(arr); g++){
			//Send back to terminal
			uart_putc((uint8_t)arr[g]);
		}
		//uart_putc(10);
	#endif
}
