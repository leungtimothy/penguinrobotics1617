#include "main.h"

/*
 * Use this function to ensure that the value being sent to the motors is within the correct range
 *
 *@param value of the motor
 *@return value of the motor between -127 to 127
 */
int motorCap(int value)
{
	if(value > 127)
		return 127;
	else if (value < -127)
		return -127;
	else
		return value;
}

int joystickCheckDeadzone(int value) {
	if (value > 0 && value < JOYSTICK_DEADZONE)
		return 0;
	else if (value < 0 && value > -JOYSTICK_DEADZONE)
		return 0;
	else
		return value;
}
