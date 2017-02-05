#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <src/hd44780.h>
#include "serial.h"

void serial_init(void){
	// Set baud rate
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)UBRR_VALUE;
	// 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	// Enabling transmission and reception
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}

void serial_putc(uint8_t data){
	//wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0))){};
	// Transmit data
	UDR0 = data;
}

uint8_t serial_getc(void){
	// Wait for byte to be received
	while(!(UCSR0A&(1<<RXC0))){};
	// Return received data
	return UDR0;
}

// get the int array from a double/float data
void serial_putd(double data){
	char arr[10];
	snprintf(arr, sizeof(data)+3, "%.0f", data);
	for(int g=0; g<strlen(arr); g++){
		//Send back to terminal
		serial_putc((uint8_t)arr[g]);
		lcd_gotoxy(g,0);
		lcd_putc(arr[g]);
	}
	serial_putc(10);
}

double serial_getd(void){
	uint8_t data = 0;
	uint8_t i = 0;
	char line[10]="";
	double j = 0;
	while(data!=10 && data!=13){
		data = serial_getc();
		line[i] = (char) data;
		i++;
	}
	j = atof(line);
	
	return j;
}
