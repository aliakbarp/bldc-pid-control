/***********************************
 * Main file of BLDC control system
 * with PID
 * 
 * Created by aliakbarp
 ***********************************/

#include <src/initlib.h> 

#define NEED_TIME_STAMP

int main(void){
	// disable global interrupt
	cli();
	timer_init();
	lcd_init();
	bldc_init();
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
	// enable global interrupt
	sei();
	set_pid = true;
	while(1){
		// Getting data desired_rpm automatically
		// from UART RX interrupt
		
		//if(get_rawrpm){
		//	#if defined NEED_TIME_STAMP
				//timer2_temp = timer2_counting;
				//timer2_overflow_temp = timer2_overflow;
				// Get total counting for TIMER2
				//time_stamp = (double) timer2_overflow_temp * 256 + (double)timer2_temp;
				// convert TIMER2 count to millisecond
				//time_stamp = (double) time_stamp * 5E-4;	
				// Get millisecond based on calibration with ms reference
				//time_stamp = (double) 0.9531 * time_stamp + (double) 0.0187;			
				//serial_rpm(rpm, time_stamp);
		//	#endif
		//	get_rpm = true;
		//	get_rawrpm = false;
		//}
		
		//if(get_rpm){
			// get total counting for TIMER2
			//sampling_time = (double) timer2_overflow_temp * 256 + (double)timer2_temp;
			// convert TIMER2 count to millisecond, for each rotation
			//sampling_time = (double) sampling_time * 5E-4/(rotation_sampling);
			// Get millisecond based on calibration with ms reference
			//sampling_time = (double) 0.9531 * sampling_time + (double) 0.0187;
			//serial_display(sampling_time);
			//uart_putc(9);
			// convert to rpm
			//rpm = (double) 60E3/sampling_time;
			// Get hertz (1 rot = 4 Hz)
			//hertz = 4 * (rpm/60);
			// calibration factor
		//	set_pid = true;
		//	get_rpm = false;
		//}
		sampling_rate = 0;
		data_sampling_time = 0;
		timer0_counting = 0;
		timer2_overflow = 0;
		timer2_counting = 0;
		while((timer0_counting <= timer0_counting_limit));
		timer2_temp = timer2_counting;
		timer2_overflow_temp = timer2_overflow;
		/*1
		while(sampling_rate <10){
			sampling_rate = (double) timer2_overflow * 256 + (double)timer2_counting;
			sampling_rate = (double) sampling_rate * 5E-4/(rotation_sampling);
			sampling_rate = (double) 0.9531 * sampling_rate + (double) 0.0187;
			_delay_us(1);
			//serial_display(timer2_overflow);
			//uart_putc(10);
		}	
		1*/
		// get total counting for TIMER2
		data_sampling_time = (double) timer2_overflow_temp * 256 + (double)timer2_temp;
		// convert TIMER2 count to millisecond, for each rotation
		data_sampling_time = (double) data_sampling_time * 5E-4/(rotation_sampling);
		// Get millisecond based on calibration with ms reference
		data_sampling_time = (double) 0.9531 * data_sampling_time + (double) 0.0187;
		
		//serial_display(sampling_rate);
		//uart_putc(9);
		
		// convert to rpm
		rpm = (double) 60E3/data_sampling_time;
		// Get hertz (1 rot = 4 Hz)
		//hertz = 4 * (rpm/60);
		
		serial_display(data_sampling_rate);
		uart_putc(32);

		serial_display(rpm);
		uart_putc(10);
		
		error = desired_rpm - rpm;
		bldc_output += pid_output(error, last_error, sampling_rate);
		last_error = error;
		//	display = true;
		//	set_pid = false;
		//if(display){
			//if(j>=1){
			//	serial_display(hertz);
			//	uart_putc(10);
			//	lcd_clrscr();
			//	sprintf(buffer, "%.0f rpm       ", rpm);
			//	lcd_display(0, 0, buffer);
			//	sprintf(buffer, "%.0f Hertz      ", hertz);
			//	lcd_display(0, 1, buffer);
			//	j = 0;
			//}
		//	get_rawrpm = true;
		//	display = false;
			//j++;
		//}
		// if BLDC stop rotating for some times, init again
		//if((timer2_overflow/100) >= 2000){
		//	bldc_init();
		//}
		
		
	}
}
