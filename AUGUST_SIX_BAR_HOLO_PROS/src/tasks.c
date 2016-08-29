#include "main.h"

struct Arm {
	int state;
	bool isNewState;
} arm = {0, false};

int armStates[] = {
		1650, 	// top
		2000,
		3000,
		3650	// bottom
};

void armSetState(int state) {
	arm.state = state;
	arm.isNewState = true;
}

int armGetPosition() {
	if (isPotFlipped)
		return abs(4000 - analogRead(armPotPort));
	else
		return analogRead(armPotPort);
}

void armTask(void *ignore) {
	int error = 0;
	float kP = 1;

	while(true) {
		while(arm.isNewState) {
			error = armStates[arm.state] - armGetPosition();
			if (abs(error) < 50) {
				armSetValue(25);
				arm.isNewState = false;
			}
			else
				armSetValue(error * kP);
		}

		delay(20);
	}
}
