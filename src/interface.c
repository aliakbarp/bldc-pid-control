/********************************
 * INTERFACE LIBRARY
 * For LCD and/or serial
 * 
 * Created by aliakbarp
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
