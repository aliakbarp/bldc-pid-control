/********************************
 * PID LIBRARY
 * 
 * Created by aliakbarp
********************************/

#include "pid.h"

double last_integral = 0;

double pid_output(double error, double last_error, double sampling_time){
	double integral = 0;
	double derivatif = 0;
	double output = 0;
	integral = last_integral + (error * sampling_time);
	derivatif = (error - last_error) / sampling_time;
	output = (KP * error) + (KI*integral) + (KD*derivatif);
	last_integral = integral;
	return output;
}
