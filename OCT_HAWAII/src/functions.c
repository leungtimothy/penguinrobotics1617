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
    return abs(4000 - analogRead(ARM_POT));
  else
    return analogRead(ARM_POT);
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
		case RIGHT:
			motorSet(RIGHT_DRIVE_MOTOR,value*MOTOR_5_DIR);
			motorSet(RIGHT_DRIVE_MOTOR_2,value*MOTOR_6_DIR);
			break;
		case LEFT:
			motorSet(LEFT_DRIVE_MOTOR,value*MOTOR_7_DIR);
			break;

		case STRAFE:
			motorSet(STRAFE_FRONT,value*MOTOR_3_DIR);
			motorSet(STRAFE_REAR,value*MOTOR_10_DIR);
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
void setArmMotors(int value)
{
	value = motorCap(value);

	motorSet(LEFT_ARM_MOTOR, value*MOTOR_4_DIR);
	motorSet(RIGHT_ARM_INSIDE_MOTOR, value*MOTOR_8_DIR);
	motorSet(RIGHT_ARM_OUTSIDE_MOTOR, value*MOTOR_1_DIR);
}

/**
 * Use this function to set the speed of the claw motor.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void setClawMotors(int value)
{
	value = motorCap(value);

	motorSet(CLAW_MOTOR_2, value*MOTOR_9_DIR);
	motorSet(CLAW_MOTOR, value * MOTOR_2_DIR);
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
			delay(20);
		}
		delay(20);
	}
}

int clawHold = 0;
int clawPos = 0;

void clawTask(void *ignore)
{
	clawHold = 1;
	clawPos = analogRead(CLAW_POT);
	float kp = 0.2;
	while(true)
	{
		if(clawHold)
		{
			int errorClaw = clawPos - analogRead(CLAW_POT);
			errorClaw = motorCap(errorClaw*kp);
			setClawMotors(errorClaw);
			printf("clawpot: %d\n",analogRead(CLAW_POT));
			delay(20);
		}
		delay(20);
	}
}
