#include "pid.h"
void PID_Reset(PID_Typedef *pid){
	pid->proportion = 0.0f;
	pid->integral = 0.0f;
	pid->derivative = 0.0f;
	pid->setpoint = 0.0f;
	pid->feedback = 0.0f;
	pid->error = 0.0f;
	pid->last_error = 0.0f;
	pid->output = 0.0f;
}

void PID_Init(PID_Typedef *pid,float kp,float ki,float kd,float dt,float limit,float max_output){
	pid->kp = kp;
	pid->ki = ki * dt;
	pid->kd = kd / dt;
	pid->limit = limit;
	pid->max_output = max_output;
	
	PID_Reset(pid);
}

float PID_Compute(PID_Typedef *pid,const float feedcack){
	pid->feedback = feedcack;
	pid->error = pid->setpoint - pid->feedback;
	
	pid->proportion = pid->kp * pid->error;
	pid->integral += pid->ki * pid->error;
	if(pid->integral > pid->limit) pid->integral = pid->limit;
	pid->derivative = pid->kd * (pid->error - pid->last_error);
	
	pid->last_error =  pid->error;
	
	pid->output = pid->proportion + pid->integral + pid->derivative;
	if(pid->output > pid->max_output) pid->output = pid->max_output;
	if(pid->output < -pid->max_output) pid->output = -pid->max_output;
	return pid->output;
}
void PID_Setpoint(PID_Typedef *pid,float setpoint){
	pid->setpoint = setpoint;
}
