/***********************************
 * Main file of BLDC control system
 * with PID
 * 
 * Created by aliakbarp
 ***********************************/

#include <src/initlib.h> 

#define NEED_TIME_STAMP
#define KP	8E-3
#define KI	0
#define KD	0

int main(void){
	// disable global interrupt
	cli();
	timer_init();
	lcd_init();
	bldc_init();
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
	// enable global interrupt
	sei();
	uart_puts_P("TEST");
	uart_putc(10);
	rotation_sampling = 10;
	timer0_counting_limit = 4 * 10;
	while(1){
		timer0_overflow = 0;
		TCNT0 = 0;
		timer2_overflow = 0;
		TCNT2 = 0;
		while(TCNT0 < timer0_counting_limit);
		rot_time_counting = timer2_counting;
		rot_time_overflow = timer2_overflow;
		flags = true;
		// waiting till 20 ms
		while(timer2_overflow < 2458 || TCNT2 < 237){
			if(flags){
				rotation_time = rot_time_overflow * 256.0 + rot_time_counting;
				// convert TIMER2 count to millisecond, for each rotation
				rotation_time = rotation_time * 5.0E-4/(rotation_sampling);
				// Get millisecond based on calibration with ms reference
				rotation_time = 0.9531 * rotation_time + 0.0187;
				flags = false;
			}
		}
		stamp_time_counting = timer2_counting;
		stamp_time_overflow = timer2_overflow;

		// Get total TIMER2
		dt = stamp_time_overflow * 256.0 + stamp_time_counting;
		// Convert TIMER2 count to millisecond, for each rotation
		dt = dt * 5.0E-4;
		// Get millisecond based on calibration with ms reference
		dt = 0.9531 * dt + 0.0187;
		
		// Get rpm
		rpm = 60E3 / rotation_time;

		error = desired_rpm - rpm;
		integral = last_integral + error * dt;
		derivative = (error - last_error) / dt;
		pid = (KP * error) + (KI * integral) + (KD * derivative);
		bldc_output += pid;

		last_error = error;
		last_integral = integral;

		rotation_sampling = 0.0047 * rpm - 0.6888;
		timer0_counting_limit = rotation_sampling * 4;
		
		serial_display(dt);
		uart_putc(32);
		serial_display(rpm);
		uart_putc(10);
	}
}
