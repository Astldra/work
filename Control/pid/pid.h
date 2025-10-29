#ifndef _PID_H_
#define _PID_H_

typedef struct {
	float setpoint;
	float feedback;
	float output;
	float error;
	float last_error;
	float kp;
	float ki;
	float kd;
	float proportion;
	float integral;
	float derivative;
	float limit;
	float max_output;
}PID_Typedef;

void PID_Reset(PID_Typedef *pid);
void PID_Init(PID_Typedef *pid,float kp,float ki,float kd,float dt,float limit,float max_output);
float PID_Compute(PID_Typedef *pid,const float feedcack);
void PID_Setpoint(PID_Typedef *pid,float setpoint);
#endif