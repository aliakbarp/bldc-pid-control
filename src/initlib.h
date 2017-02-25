#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <src/hd44780.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <src/uart.h>
//#include <src/pid.h>
#include <src/timer.h>
#include <src/interrupt.h>
#include <src/interface.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define timer0_counting	TCNT0
#define timer2_counting	TCNT2
#define bldc_output OCR1B
// how many bldc rotation you use to get the rpm, 64 is max
//#define UART_BUFFER 10
#define UART_BAUD_RATE 9600

// TCNT0 limit, the max is 255 (8bit, start from 0)
uint16_t rotation_sampling = 0;
uint16_t timer0_counting_limit = 0;
float pid = 0;
float proportional = 0, integral = 0, derivative = 0, last_integral = 0;
float rot_time_counting = 0;
float rot_time_overflow = 0;
float rotation_time = 0;
float stamp_time_counting = 0;
float stamp_time_overflow = 0;
volatile float timer0_overflow = 0;
volatile float timer2_overflow = 0;
char buffer[33];
bool flags = false;
float dt = 0;
float error = 0, last_error = 0;
float rpm = 1000, last_rpm = 0;
float desired_rpm = 5000;
uint16_t i = 0;
unsigned char line[10];
unsigned char arr[10];