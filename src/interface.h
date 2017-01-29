/********************************
 * INTERFACE LIBRARY
 * For LCD and/or serial
 * 
 * Created by aliakbarp
********************************/

#ifndef INTERFACE_H
#define INTERFACE_H

#define NEED_LCD
//#define NEED_SERIAL

void lcd_display(uint8_t x, uint8_t y, char buffer[33]);

#endif
