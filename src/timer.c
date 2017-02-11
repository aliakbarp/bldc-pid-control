/********************************
 * TIMER LIBRARY
 * Using for :
 * Generate pulse to BLDC (using TIMER1)
 * Counting BLDC rotation (using TIMER0)
 * Counting BLDC rotation time (using TIMER2)
 * Make delay function
 * 
 * Created by aliakbarp
********************************/

#include <avr/io.h>
#include <util/delay.h>

void timer0_init(void){
	// T0, input for clock signal
	DDRD&=~(1<<DDD4);
	// T0, internal pull-up
	PORTD|=(1<<PD4);
	// Input clock from T0, rising edge
	TCCR0B|=(1<<CS02)|(1<<CS01)|(1<<CS00);
	// Enable overflow interrupt
	TIMSK0|=(1<<TOIE0);
}

void timer1_init(void){
	// PINB2 as output, PWM generator pin
	DDRB|=(1<<DDB2);
	// OC1B activation for PWM output pin (COM)
	// Fast PWM mode, with ICR1 as TOP (WGM)
	TCCR1A|=(1<<COM1B1)|(1<<WGM11);
	// Prescaller 8 (CS)
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11);
	// TOP value of TIMER1 counting
	ICR1 = 20000;
}

void timer2_init(void){
	// No prescalling
	TCCR2B|=(1<<CS20);
	// Enable overflow interrupt 
	TIMSK2|=(1<<TOIE2);
}

void millisec(int d){
	int i = 0;
	for(i=0; i<d; i++){
		_delay_ms(1);
	}
}

void bldc_init(void){
	TCNT0 = 0;
	while(TCNT0 <= 32){
		OCR1B = 1000;
		millisec(1000);
		uint16_t g;
		for(g=1500; g<2300; g+=100){
			OCR1B = g;
			millisec(600);
		}
		for(g=2300; g>1900; g-=100){
			OCR1B = g;
			millisec(600);
		}
	}
}

void timer_init(void){
	timer0_init();
	timer1_init();
	timer2_init();
}
