#ifndef ARM_H_
#define ARM_H_

#include "main.h"

#define MAX_HEIGHT 2300
#define OUTSIDE_FENCE_SCORING_HEIGHT 1980
#define MIDDLE_FENCE_SCORING_HEIGHT 1820
#define OUTSIDE_FENCE_PUSH_HEIGHT 1650
#define MIDDLE_FENCE_PUSH_HEIGHT 1525
#define GROUND_HEIGHT 775

#define ARM_THRESHOLD 10

typedef enum { UP, DOWN, AUTO } Arm_Directions;

struct Arm {
  int target;
  bool manualSet;
  Arm_Directions direction;
} arm;

// int armTarget;
//
// bool armManualSet;
// Arm_Directions armDirection;

/**
 * Use this function to set the speed of all of the arm motors.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full
 * forward, with 0
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

void armSetTarget(int target);

void armSetManual(Arm_Directions dir);

/*
 * Arm task function.
 */
void armTask(void *);

#endif
