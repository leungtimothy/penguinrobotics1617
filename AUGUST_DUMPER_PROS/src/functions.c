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


/**
 * Use this function to set the individual drive motors of the holonomic drive.
 *
 * @param motor_location Choose one of FRONT_LEFT, FRONT_RIGHT, BACK_LEFT and BACK_RIGHT to set the speed of.
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void setDrive(int motor_location, int value)
{
	// Verify motor value is between -127 and 127;
	value = motorCap(value);

	// Choose the motor port(s) to set
	switch(motor_location)
	{
		case FRONT_LEFT:
			motorSet(FRONT_LEFT_DRIVE_MOTOR,value*MOTOR_9_DIR);
			break;

		case FRONT_RIGHT:
			motorSet(FRONT_RIGHT_DRIVE_MOTOR,value*MOTOR_6_DIR);
			break;

		case BACK_LEFT:
			motorSet(BACK_LEFT_DRIVE_MOTOR,value*MOTOR_1_DIR);
			motorSet(BACK_LEFT_DRIVE_MOTOR_2,value*MOTOR_10_DIR);
			break;

		case BACK_RIGHT:
			motorSet(BACK_RIGHT_DRIVE_MOTOR,value*MOTOR_4_DIR);
			motorSet(BACK_RIGHT_DRIVE_MOTOR_2,value*MOTOR_5_DIR);
			break;

		default:
			break;
	}
}



/**
 * Use this function to set the speed of all of the arm motors.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void setArm(int value)
{
	value = motorCap(value);

	motorSet(LEFT_ARM_MOTOR, value*MOTOR_3_DIR);
	motorSet(RIGHT_ARM_MOTOR, value*MOTOR_2_DIR);
}

/**
 * Use this function to set the speed of the claw motor.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void setClaw(int value)
{
	value = motorCap(value);

	motorSet(CLAW, value*MOTOR_8_DIR);
}
