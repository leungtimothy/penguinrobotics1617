#include "main.h"

struct Arm {
	int target;
	bool isAtTarget;
} arm = {0, false};

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

// armstates located in main.h
void armTask(void *ignore) {
	int error = 0;
	float kP = 0.4;

	while (true) {
		error = arm.target - armGetPosition();

		while (arm.isAtTarget) {
			// cap target
			if (arm.target > ARM_TOP)
				arm.target = ARM_TOP;
			else if (arm.target < ARM_BOTTOM)
				arm.target = ARM_BOTTOM;

			error = arm.target - armGetPosition();
			if (abs(error) < 25) {
				armSetValue(10);
				arm.isAtTarget = false;
			} else
				armSetValue(error * kP);

			printf("\r\nError: %d\tPos: %d\tPower: %d", error, armGetPosition(), motorGet(RIGHT_ARM_MOTOR));
		}

		if (abs(error) > 50)
			arm.isAtTarget = true;

		printf("\r\nError: %d\tPos: %d\tPower: %d", error, armGetPosition(), motorGet(RIGHT_ARM_MOTOR));

		delay(20);
	}
}
