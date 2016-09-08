#include "arm.h"
#include "util.h"
#include "pid.h"

/**
 * Use this function to set the speed of all of the arm motors.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void armSetPower(int value)
{
	value = motorCap(value);

	motorSet(LEFT_ARM_MOTOR, value * MOTOR_4_DIR);
	motorSet(LEFT_ARM_MOTOR_2, value * MOTOR_7_DIR);
	motorSet(RIGHT_ARM_MOTOR, value * MOTOR_6_DIR);
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

	motorSet(CLAW, value * MOTOR_9_DIR);
}

// armstates located in header file
void armTask(void *ignore) {
	PID pidArm;
	pidInit(pidArm, 0.75, 0, 0, 0, 0);

	while (true) {
		armSetPower(pidCalculate(pidArm, armGetPosition(), armTarget));

		printf("\r\nError: %d\tPos: %d\tPower: %d", pidArm.error, armGetPosition(), motorGet(RIGHT_ARM_MOTOR));

		delay(20);
	}
}
