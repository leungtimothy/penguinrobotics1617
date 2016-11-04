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
}Claw;

extern Claw claw;

#define CLAW_HOLD_KP 0.4
#define CLAW_MOVE_KP 0.2
#define CLAW_IS_MOVING_THRESHOLD 75
#define MAX_HOLD_POWER 30
#define MAX_SETPOINT_MOVE_POWER 80

#define CLAW_DEBUG 1

#endif
