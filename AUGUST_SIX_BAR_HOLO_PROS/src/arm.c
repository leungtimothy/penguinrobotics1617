#include "arm.h"
#include "main.h"
#include "util.h"

/**
 * Use this function to set the speed of all of the arm motors.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void armSetValue(int value)
{
	value = motorCap(value);

	motorSet(LEFT_ARM_MOTOR, value*MOTOR_4_DIR);
	motorSet(LEFT_ARM_MOTOR_2, value*MOTOR_7_DIR);
	motorSet(RIGHT_ARM_MOTOR, value*MOTOR_6_DIR);
}

void armSetTarget(int target) {
	arm.target = target;
	arm.isAtTarget = true;
}

int armGetPosition() {
	if (isPotFlipped)
		return abs(4000 - analogRead(ARM_POT_PORT));
	else
		return analogRead(ARM_POT_PORT);
}

/**
 * Use this function to set the speed of the claw motor.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void clawSetValue(int value)
{
	value = motorCap(value);

	motorSet(CLAW, value*MOTOR_9_DIR);
}
