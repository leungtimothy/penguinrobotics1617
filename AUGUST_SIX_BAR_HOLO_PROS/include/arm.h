#include "main.h"

struct Arm{
	int target;
	bool isAtTarget;
} arm;

/**
 * Use this function to set the speed of the claw motor.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void clawSetValue(int value);

/**
 * Use this function to set the speed of all of the arm motors.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void armSetValue(int value);

/**
 * Use this function to set state of the arm.
 *
 * @param value int that corresponds to a certain arm state.
 *
 */
void armSetTarget(int state);

/**
 * Use this function to get the potentiometer value of the arm.
 *
 * @return value of potentiometer.
 *
 */
int armGetPosition();
