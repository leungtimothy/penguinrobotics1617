#include "pid.h"

void pidInit(PID * pid, float kp, float ki, float kd, int limitUpper, int limitLower) {
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;

	pid->limitUpper = limitUpper;
	pid->limitLower = limitLower;

	pid->errorDiff = 0;
	pid->errorLast = 0;
}

int pidCalculate(PID * pid, int input, int target) {
	pid->error = target - input;
	pid->errorDiff = pid->error - pid->errorLast;
	pid->errorLast = pid->error;
	if (abs(pid->error) < pid->limitUpper && abs(pid->error) > pid->limitLower)
		pid->errorSum += pid->error;
	else if (abs(pid->error) > pid->limitUpper)
		pid->errorSum = 0;
	return pid->error * pid->kp + pid->errorSum * pid->ki + pid->errorDiff * pid->kd;
}
