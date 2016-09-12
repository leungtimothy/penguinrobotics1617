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

void armSetTarget(int target) {
	arm.manualSet = false;

	if (target > ARM_TOP)
		arm.target = ARM_TOP;
	else if (target < ARM_BOTTOM)
		arm.target = ARM_BOTTOM;
	else
		arm.target = target;
}

void armSetManual(Arm_Directions dir) {
	arm.manualSet = true;
	arm.direction = dir;
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
	pidInit(pidArm, 0.5, 0, 0, 0, 0);

	while (true) {
		if (arm.manualSet) {
			armSetPower(arm.direction == UP ? 127 : -127);
			armSetTarget(armGetPosition());
		} else {
			int PID = pidCalculate(pidArm, armGetPosition(), arm.target);
			armSetPower(PID);
			printf(" PID: %d", PID);
		}

		printf("\r\nTarget: %d\tPos: %d\tPower: %d", arm.target, armGetPosition(), motorGet(RIGHT_ARM_MOTOR));

		delay(20);


	}
}
