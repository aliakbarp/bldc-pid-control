/********************************
 * PID LIBRARY
 * 
 * Created by aliakbarp
********************************/

#ifndef PID_H
#define PID_H

//PID constants
#define	KP	6.5E-3
#define KI	0.4E-7
#define KD	0.8

double pid_output(double error, double last_error, double sampling_time);

#endif
