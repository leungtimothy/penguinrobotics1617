#ifndef CLAW_H_
#define CLAW_H_

#include "main.h"
#include "pid.h"

#define CLAW_OPEN 2550
#define CLAW_CLOSE 3700

#define CLAW_THRESHOLD 5

typedef enum {
	OPEN,
	CLOSE,
	HOLD
} Claw_Settings;

struct Claw {
	int target;
	Claw_Settings setting;

	bool isAdjusting;
} claw;

PID pidClaw;

/**
 * Use this function to set the speed of the claw motor.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void clawSetPower(int power);

int clawGetPosition();

void clawSetting(Claw_Settings setting);

void clawTask(void*);

#endif
