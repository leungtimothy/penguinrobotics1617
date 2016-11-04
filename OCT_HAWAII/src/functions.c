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

int armGetPosition() {
  if (isArmPotFlipped)
    return abs(4095 - analogRead(ARM_POT));
  else
    return analogRead(ARM_POT);
}

/**
 * Use this function to set the speed of all of the arm motors.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void setArmMotors(int value)
{
	value = motorCap(value);

	motorSet(LEFT_ARM_MOTOR, value*MOTOR_4_DIR);
	motorSet(RIGHT_ARM_INSIDE_MOTOR, value*MOTOR_8_DIR);
	motorSet(RIGHT_ARM_OUTSIDE_MOTOR, value*MOTOR_1_DIR);
}

int armHold = 0;
int armPos = 0;

void armTask(void *ignore)
{
	armHold = 1;
	armPos = armGetPosition();
	float kp = 0.2;
	while(true)
	{
		if(armHold)
		{
			int errorArm = armPos - armGetPosition();
			errorArm = motorCap(errorArm*kp);
			setArmMotors(errorArm);
			//printf("armpot: %d\n",analogRead(ARM_POT));
		}
		delay(20);
	}
}
