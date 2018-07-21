#include "PID.h"

//using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd)
{
	PID::Kp = Kp;
	PID::Ki = Ki;
	PID::Kd = Kd;

	p_error = 0.0;
    i_error = 0.0;
    d_error = 0.0;

    prev_cte = 0.0;
}

void PID::UpdateError(double cte)
{
	p_error = cte; // Proportional error
	
	i_error += cte; // Integral error

	d_error = cte - prev_cte; // Differential error
	prev_cte = cte; // Save for next time step
}

double PID::TotalError()
{
	return( Kp * p_error + Ki * i_error + Kd * d_error );
	// Note we return the positive value of the new steering angle,
	// so either Kp, Ki and Kd must be initialized to negative values,
	// or the returned value must be subtracted by the calling entity.
}

