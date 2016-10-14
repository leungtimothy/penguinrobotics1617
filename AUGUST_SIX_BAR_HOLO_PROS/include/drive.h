#ifndef DRIVE_H_
#define DRIVE_H_

#include "util.h"

#define FORWARD 1
#define BACKWARD -1

struct DriveChannels {
  int powerX;
  int powerY;
  int powerYaw;
} driveChannels;

struct Odometry {
  int Y;
  int X;
  int YAW;
} odometry;

typedef enum Motor_Positions {
  FRONT_LEFT,
  FRONT_RIGHT,
  BACK_LEFT,
  BACK_RIGHT
} Motor_Positions;

typedef enum Channels { X, Y, YAW } Channels;

/**
 * Use this function to set the individual drive motors of the holonomic drive.
 *
 * @param motor_location Choose one of FRONT_LEFT, FRONT_RIGHT, BACK_LEFT and
 * BACK_RIGHT to set the speed of.
 * @param value the new signed speed; -127 is full reverse and 127 is full
 * forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 */
void driveSetPower(Motor_Positions motor_location, int value);

/**
 * Use this function to set a drive channel of the holonomic drive.
 *
 * @param channel Choose one of X, Y, or YAW to set the speed of.
 * @param value the new signed speed; -127 is full reverse and 127 is full
 * forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 */
void driveSetChannel(Channels channel, int value);

/**
 * Use this function to stop all drive motors.
 */
void driveStop(void);

// Odometry tracking task protoype
void odometryTask(void *ignore);

#endif
