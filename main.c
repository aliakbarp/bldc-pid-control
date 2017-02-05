/***********************************
 * Main file of BLDC control system
 * with PID
 * 
 * Created by aliakbarp
 ***********************************/

#include <src/initlib.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <src/uart.h>

#define UART_BAUD_RATE 9600

unsigned char line[10];
unsigned char arr[10];

int main(void){
	// disable global interrupt
	cli();
	timer_init();
	lcd_init();
	bldc_init();
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
	// enable global interrupt
	sei();
	get_rawrpm = true;
	while(1){
		// Get data from UART
		//snprintf(arr, sizeof(desired_rpm)+3, "%.0f", desired_rpm);
		//for(int g=0; g<strlen(arr); g++){
			//Send back to terminal
			//uart_putc((uint8_t)arr[g]);
		//}		
		//uart_putc(10);
		
		if(get_rawrpm){
			timer0_counting = 0;
			timer2_overflow = 0;
			timer2_counting = 0;
			while(timer0_counting <= timer0_counting_limit){};
			timer2_temp = timer2_counting;
			timer2_overflow_temp = timer2_overflow;
			timer0_temp = timer0_counting;
			get_rpm = true;
			get_rawrpm = false;
		}
		
		if(get_rpm){
			// get total counting for TIMER2
			sampling_time = (double) timer2_overflow_temp * 256 + (double)timer2_temp;
			// convert TIMER2 count to millisecond, for each rotation
			sampling_time = (double) sampling_time * 6.25E-5/(rotation_sampling);
			// convert to rpm
			rpm = (double) 60E3/sampling_time;
			sprintf(buffer, "%.0f rpm", rpm);
			set_pid = true;
			get_rpm = false;
		}
		if(set_pid){
			error = desired_rpm - rpm;
			bldc_output += pid_output(error, last_error, sampling_time); 
			last_error = error;
			display = true;
			set_pid = false;
		}
		if(display){
			lcd_display(0, 0, buffer);
			if(j>=50){
				unsigned char arr[10];
				snprintf(arr, sizeof(rpm)+3, "%.0f", rpm);
				for(int g=0; g<strlen(arr); g++){
					//Send back to terminal
					uart_putc((uint8_t)arr[g]);
				}
				uart_putc(10);
				j = 0;
			}
			get_rawrpm = true;
			display = false;
			j++;
		}
		// if BLDC stop rotating for some times, init again
		if((timer2_overflow/100) >= 2000){
			bldc_init();
		}
		
		
	}
	//_delay_ms(500);
}
