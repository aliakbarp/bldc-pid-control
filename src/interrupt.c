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
	
}

// TIMER 2 overflow interrupt function
ISR(TIMER2_OVF_vect){
	extern uint32_t timer2_overflow;
	timer2_overflow++;
	TIFR2=0x00;
}
