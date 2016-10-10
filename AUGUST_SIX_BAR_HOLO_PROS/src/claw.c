#include "claw.h"
#include "util.h"
#include "pid.h"

/**
 * Use this function to set the speed of the claw motor.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void clawSetPower(int power) {
	power = motorCap(power);

	motorSet(CLAW, power * MOTOR_9_DIR);
}

int clawGetPosition() {
	if (isClawPotFlipped)
		return abs(4000 - analogRead(CLAW_POT_PORT));
	else
		return analogRead(CLAW_POT_PORT);
}

void clawSetting(Claw_Settings setting) {
	if (setting == OPEN || setting == CLOSE)
		claw.isAdjusting = false;
	else if (setting == HOLD)
		claw.isAdjusting = true;
	claw.setting = setting;
}

void clawTask(void *ignore) {
/*	int PID;

	pidInit(&pidClaw, 0.35, 0, 0, 0, 0);

	claw.target = clawGetPosition();
	clawSetting(HOLD);

	while (true) {
		if (claw.setting == HOLD) {
			while (claw.isAdjusting) {
				pidCalculate(&pidClaw, clawGetPosition(), claw.target);

				if (abs(pidClaw.errorDiff) < 5)
					claw.isAdjusting = false;
			}

			PID = pidCalculate(&pidClaw, clawGetPosition(), claw.target);
			if (abs(PID) > CLAW_THRESHOLD)
				clawSetPower(PID);
		} else {
			clawSetPower(claw.setting == OPEN ? 127 : -127);
		}
		printf("\r\nTarget: %d\tPos: %d\tPower: %d", claw.target, clawGetPosition(), motorGet(CLAW));

		delay(20);
	}*/
}
