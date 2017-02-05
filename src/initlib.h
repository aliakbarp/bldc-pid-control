#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <src/hd44780.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <src/uart.h>
#include <src/pid.h>
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
#define rotation_sampling 5
// TCNT0 limit, the max is 255 (8bit, start from 0)
#define timer0_counting_limit (4*rotation_sampling)
//#define UART_BAUD_RATE 9600
//#define UART_BUFFER 10

uint32_t timer2_overflow = 0;
char buffer[33];
bool get_rawrpm = false;
bool get_rpm = false;
bool display = false;
bool set_pid = false;
bool getting_data = false;
bool serial_complete = false;
double sampling_time = 0;
double error = 0, last_error = 0;
double rpm = 1000, last_rpm = 0;
double desired_rpm = 7000;
double timer2_overflow_temp = 0;
uint16_t timer0_temp = 0, timer2_temp = 0;
uint16_t c = 0;
//char line[UART_BUFFER];
uint16_t i = 0, j = 0x30;
