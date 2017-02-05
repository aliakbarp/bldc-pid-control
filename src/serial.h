#ifndef SERIAL_H
#define SERIAL_H

#define F_CPU 16000000UL
#define SERIAL_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (SERIAL_BAUDRATE * 16UL))) - 1)

void serial_init(void);
void serial_putc(uint8_t data);
uint8_t serial_getc(void);
void serial_putd(double data);
double serial_getd(void);

#endif
