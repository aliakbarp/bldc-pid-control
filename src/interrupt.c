/********************************
 * INTERRUPT LIBRARY
 * 
 * Created by aliakbarp
********************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "interrupt.h"

// TIMER 0 overflow interrupt function
ISR(TIMER0_OVF_vect){
	extern double timer0_overflow;
	timer0_overflow+=1;
	TIFR0=0x00;
}

// TIMER 2 overflow interrupt function
ISR(TIMER2_OVF_vect){
	extern double timer2_overflow;
	timer2_overflow+=1;
	TIFR2=0x00;
}