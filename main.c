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

char line[10];

int main(void){
	// disable global interrupt
	cli();
	timer_init();
	lcd_init();
	//bldc_init();
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
	// enable global interrupt
	sei();
	//get_rawrpm = true;
	while(1){
		// Get data from UART
		c = (uint16_t) uart_getc();
		
		// Check data from UART
        if ( c & UART_NO_DATA ){
            /* 
             * no data available from UART 
             */
             if (getting_data) get_rawrpm = true;
        }
        else{
            if ( c & UART_FRAME_ERROR ){
                uart_puts_P("UART Frame Error: ");
            }
            if ( c & UART_OVERRUN_ERROR ){
                uart_puts_P("UART Overrun Error: ");
            }
            if ( c & UART_BUFFER_OVERFLOW ){
                uart_puts_P("Buffer overflow error: ");
            }
            // Copy data from UART to array 'line'
			if(c!=10){
				if(c!=13){
					line[i] = c;
					i++;
				}
			} else {
				// Get rpm_desired
				//desired_rpm = atof(line);
				rpm = atof(line);
				//display=true;
				for(int g=0; g<i; g++){
					//Send back to terminal
					uart_putc(line[g]);
				}
				uart_putc(10);
				getting_data = true;
			}
		}
		/*
		if(display){
			display = false;
			char arr[10]="";
			snprintf(arr, i+1, "%.0f", rpm);
//			for(int g=0; g<i; g++){
				//Send back to terminal
//				uart_putc((uint8_t)arr[g]);
//			}
//			uart_putc(10);
			i = 0;
		}
		*/
		
		if(get_rawrpm){
			//timer0_counting = 0;
			//timer2_overflow = 0;
			//timer2_counting = 0;
			//while(timer0_counting <= timer0_counting_limit){};
			//timer2_temp = timer2_counting;
			//timer2_overflow_temp = timer2_overflow;
			//timer0_temp = timer0_counting;
			//if(rpm != last_rpm) get_rpm = true;
			get_rpm = true;
			get_rawrpm = false;
		}
		if(get_rpm){
			// get total counting for TIMER2
			//sampling_time = (double) timer2_overflow_temp * 256 + (double)timer2_temp;
			// convert TIMER2 count to millisecond, for each rotation
			//sampling_time = (double) sampling_time * 6.25E-5/(rotation_sampling);
			// convert to rpm
			//rpm = (double) 60E3/sampling_time;
			sprintf(buffer, "%.0f rpm", rpm);
			set_pid = true;
			get_rpm = false;
		}
		if(set_pid){
			//error = desired_rpm - rpm;
			//bldc_output += pid_output(error, last_error, sampling_time); 
			//last_error = error;
			display = true;
			set_pid = false;
		}
		if(display){
			lcd_display(0, 0, buffer);
			//serial_display(rpm);
			if (rpm > 4000){
				lcd_display(0, 0, "Kelebihan");
				rpm = 87654;
				serial_display(rpm);
			}
			get_rawrpm = true;
			display = false;
		}
		// if BLDC stop rotating for some times, init again
		if((timer2_overflow/100) >= 2000){
			bldc_init();
		}
		
	}
	//_delay_ms(500);
}
