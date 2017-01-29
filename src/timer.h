/********************************
 * TIMER LIBRARY
 * Using for :
 * Generate pulse to BLDC (using TIMER1)
 * Counting BLDC rotation (using TIMER0)
 * Counting BLDC rpm (using TIMER2)
 * Make delay function
 * 
 * Created by aliakbarp
********************************/

#ifndef TIMER_H
#define TIMER_H

void timer_init(void);
void timer0_init(void);
void timer1_init(void);
void timer2_init(void);
void bldc_init(void);
void millisec(int d);

#endif
