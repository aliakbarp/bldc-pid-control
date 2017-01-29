/***********************************
 * Main file of BLDC control system
 * with PID
 * 
 * Created by aliakbarp
 ***********************************/

#include <src/initlib.h> 

int main(void){
// disable global interrupt
cli();
timer_init();
lcd_init();
bldc_init();
// enable global interrupt
sei();
get_rawdata = true;

	while(1){
		if(get_rawdata){
			timer0_counting = 0;
			timer2_overflow = 0;
			timer2_counting = 0;
			while(timer0_counting <= timer0_counting_limit){};
			timer2_temp = timer2_counting;
			timer2_overflow_temp = timer2_overflow;
			timer0_temp = timer0_counting;
			get_rpm = true;
			get_rawdata = false;
		}
		if(get_rpm){
			// get total counting for TIMER2
			sampling_time = (double) timer2_overflow_temp * 256 + (double)timer2_temp;
			// convert TIMER2 count to millisecond, for each rotation
			sampling_time = (double) sampling_time * 6.25E-5/(rotation_sampling);
			// convert to rpm
			rpm = (double) 60E3/sampling_time;
			sprintf(buffer, "%f rpm %f", rpm, error);
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
			get_rawdata = true;
			display = false;
		}
		// if BLDC stop rotating for some times, init again
		if((timer2_overflow/100) >= 2000){
			bldc_init();
		}
	}
}
