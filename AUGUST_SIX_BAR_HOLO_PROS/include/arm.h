#ifndef ARM_H_
#define ARM_H_

#include "main.h"

#define ARM_TOP 1950
#define ARM_MID 1175
#define ARM_BOTTOM 125

int armTarget;

/**
 * Use this function to set the speed of all of the arm motors.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void armSetPower(int value);

/**
 * Use this function to get the potentiometer value of the arm.
 *
 * @return value of potentiometer.
 *
 */
int armGetPosition();

/**
 * Use this function to set the speed of the claw motor.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void clawSetValue(int value);

/*
 * Arm task function.
 */
void armTask(void*);

#endif
