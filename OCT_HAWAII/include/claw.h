#ifndef CLAW_H_
#define CLAW_H_

#include "main.h"


typedef enum {
	MOVING,
	STATIONARY,
	HOLDING,
  SETPOINT
} Claw_Status;

typedef enum{
  CLOSE,
  OPEN,
  NOT_PRESSED
} ClawButtonStatus;

typedef struct Claw{
  int holdTarget;
  Claw_Status status;
	int autoOpenTrigger;
	int autoOpenPos;
}Claw;

extern Claw claw;

#define CLAW_HOLD_KP 0.4
#define CLAW_MOVE_KP 0.2
#define CLAW_IS_MOVING_THRESHOLD 75
#define MAX_HOLD_POWER 30
#define MAX_SETPOINT_MOVE_POWER 80

#define CLAW_DEBUG 1

int clawGetPosition();
void waitUntilClawPos(int pos);
/**
 * Use this function to set the speed of the claw motor.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void setClawMotors(int value);
void clawTask(void *ignore);

#endif
