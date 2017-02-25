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
	extern volatile float timer0_overflow;
	timer0_overflow+=1.0;
	TIFR0=0x00;
}

// TIMER 2 overflow interrupt function
ISR(TIMER2_OVF_vect){
	extern volatile float timer2_overflow;
	timer2_overflow+=1.0;
	//TIFR2=0x00;
}