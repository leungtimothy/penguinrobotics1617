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
	motorSet(RIGHT_ARM_MOTOR_1, value * MOTOR_7_DIR);
	motorSet(RIGHT_ARM_MOTOR_2, value * MOTOR_8_DIR);
}

int armGetPosition() {
	if (isArmPotFlipped)
		return abs(4000 - analogRead(ARM_POT_PORT));
	else
		return analogRead(ARM_POT_PORT);
}

void armSetTarget(int target) {
	/*if (target > ARM_TOP)
		arm.target = ARM_TOP;
	else if (target < ARM_BOTTOM)
		arm.target = ARM_BOTTOM;
	else*/
		arm.target = target;
}

void armSetManual(Arm_Directions dir) {
	if (dir == AUTO)
		arm.manualSet = false;
	else {
		arm.manualSet = true;
		arm.direction = dir;
	}
}



// armstates located in header file
void armTask(void *ignore) {
	PID pidArm;
	pidInit(&pidArm, 0.3, 0.0, 0.0, 0, 0);

	int PID = pidCalculate(&pidArm, armGetPosition(), arm.target);

	armSetTarget(armGetPosition());
	while (true) {
		if (arm.manualSet) {
			armSetPower(arm.direction == UP ? 127 : -127);
			armSetTarget(arm.direction == UP ? armGetPosition() + 50 : armGetPosition() - 50);
		} else {
			int PID = pidCalculate(&pidArm, armGetPosition(), arm.target);
			if (abs(PID) > ARM_THRESHOLD)
				armSetPower(PID);

		}

		//printf("\r\nTarget: %d\tPos: %d\tPower: %d", arm.target, armGetPosition(), motorGet(RIGHT_ARM_MOTOR_1));

		delay(20);
	}
}
