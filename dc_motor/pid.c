#include "dc_motor/pid.h"
#include "dc_motor/tb6612.h"

float P = 2.3; //112.75;//6.7229;
float I = 0.67;//337;//329.5087;
float D = 0;//52.25;//0;
uint16_t INTEGER_WINDUP = 1000;

int16_t error = 0;
int16_t e_int = 0;

uint16_t pwm_value = 0;//na testy

/**************************************************************************************/

uint16_t PID(uint16_t req_speed, uint16_t measured_speed)
{
	uint16_t prev_error = error;

	error = req_speed - measured_speed;

	e_int += error;//simple integrating by summing
	if(e_int > INTEGER_WINDUP) e_int = INTEGER_WINDUP;
	if(e_int < -INTEGER_WINDUP) e_int = -INTEGER_WINDUP;

	pwm_value = ( (error * P) + (e_int * I) + (error - prev_error) * D);
	if(pwm_value<0) pwm_value*=(-1);
//	if(pwm_value<500) pwm_value = 500;
	return pwm_value; // PWM value
}
/**************************************************************************************/


/**************************************************************************************/
//struct pid_params_t
//{
//	 float P;
//	 float I;
//	 float D;
//	 uint16_t INTEGER_WINDUP;
//
//	float error;
//	float e_int;
//
//}pid = {.P = 112.75, .I = 337, .D = 52.25, .INTEGER_WINDUP = 3500, .error = 0, .e_int = 0 };//, *pid_p = &pid ;

//uint16_t PID(uint16_t req_speed, uint16_t measured_speed)
//{
//	uint16_t prev_error = pid.error;
//
//	pid.error = req_speed - measured_speed;
//
//	pid.e_int += pid.error;//simple integrating by summing
//	if(pid.e_int > pid.INTEGER_WINDUP) pid.e_int = pid.INTEGER_WINDUP;
//	if(pid.e_int < -pid.INTEGER_WINDUP) pid.e_int = -pid.INTEGER_WINDUP;
//
//	pwm_value = ( (pid.error * pid.P) + (pid.e_int * pid.I) + (pid.error - prev_error) * pid.D);
//	if(pwm_value<0) pwm_value*=(-1);
//	return pwm_value; // PWM value
//}
///**************************************************************************************/
