#include "main.h"


/*
 * Use this function to ensure that the value being sent to the motors is within the correct range
 *
 *@param value of the motor
 *@return value of the motor between -127 to 127
 */
int motorCap(int value, int maxValue)
{
	if(value > maxValue)
		return maxValue;
	else if (value < -maxValue)
		return -maxValue;
	else
		return value;
}

int customMotorCap(int value, int lower, int upper)
{
	if(value > upper)
		return upper;
	else if (value < lower)
		return lower;
	else
		return value;
}
