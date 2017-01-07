#ifndef DRIVE_H_
#define DRIVE_H_

#include "main.h"

typedef enum {
	FORWARD = 1,
	BACKWARD = -1,
	TURN_LEFT,
  TURN_RIGHT
} Direction;

#define MIN_MOVE_POWER 30
#define STRAIGHT_CONSTANT 0.5


int drive(Direction dir, int distance, int power);
void driveADP(int dir, int distance, int maxPower, int timeout,float acclerationConst,float decclerationConst);
void driveAP(int dir, int distance, int maxPower, int timeout,float acclerationConst);
void driveDP(int dir, int distance, int maxPower, int timeout,float decclerationConst);
void setDrive(int motor_location, int value);

int turn(Direction dir, int distance, int power);

#endif
