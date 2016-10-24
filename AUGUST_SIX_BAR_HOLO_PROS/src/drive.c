#include "drive.h"
#include "main.h"
#include "util.h"
#include <math.h>

#define ANGLE_OFFSET 45
#define DELTA_THRESHOLD 5
#define ROTATION_THRESHOLD 1

/**
 * Use this function to set the individual drive motors of the holonomic drive.
 *
 * @param motor_location Choose one of FRONT_LEFT, FRONT_RIGHT, BACK_LEFT and
 * BACK_RIGHT to set the speed of.
 * @param value the new signed speed; -127 is full reverse and 127 is full
 * forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void driveSetPower(Motor_Positions motor_location, int value) {
  // Verify motor value is between -127 and 127;
  value = motorCap(value);

  // Choose the motor port(s) to set
  switch (motor_location) {
  case FRONT_LEFT:
    motorSet(FRONT_LEFT_DRIVE_MOTOR_1, value * MOTOR_1_DIR);
    motorSet(FRONT_LEFT_DRIVE_MOTOR_2, value * MOTOR_10_DIR);
    break;

  case FRONT_RIGHT:
    motorSet(FRONT_RIGHT_DRIVE_MOTOR, value * MOTOR_6_DIR);
    break;

  case BACK_LEFT:
    motorSet(BACK_LEFT_DRIVE_MOTOR, value * MOTOR_5_DIR);
    break;

  case BACK_RIGHT:
    motorSet(BACK_RIGHT_DRIVE_MOTOR_1, value * MOTOR_2_DIR);
    motorSet(BACK_RIGHT_DRIVE_MOTOR_2, value * MOTOR_3_DIR);
    break;

  default:
    break;
  }
}

/**
 * Use this function to set a drive channel of the holonomic drive.
 *
 * @param channel Choose one of X, Y, or YAW to set the speed of.
 * @param value the new signed speed; -127 is full reverse and 127 is full
 * forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 */
void driveSetChannel(Channels channel, int value) {
  value = motorCap(value);

  switch (channel) {
  case X:
    driveChannels.powerX = value;
    break;
  case Y:
    driveChannels.powerY = value;
    break;
  case YAW:
    driveChannels.powerYaw = value;
    break;
  default:
    break;
  }

  driveSetPower(FRONT_LEFT, driveChannels.powerY + driveChannels.powerX +
                                driveChannels.powerYaw);
  driveSetPower(FRONT_RIGHT, driveChannels.powerY - driveChannels.powerX -
                                 driveChannels.powerYaw);
  driveSetPower(BACK_LEFT, driveChannels.powerY - driveChannels.powerX +
                               driveChannels.powerYaw);
  driveSetPower(BACK_RIGHT, driveChannels.powerY + driveChannels.powerX -
                                driveChannels.powerYaw);
}

/**
 * Use this function to stop all drive motors.
 */
void driveStop() {
  driveSetPower(FRONT_LEFT, 0);
  driveSetPower(FRONT_RIGHT, 0);
  driveSetPower(BACK_LEFT, 0);
  driveSetPower(BACK_RIGHT, 0);
}

// Odometry tracking task
void odometryTask(void *ignore) {
  float dY;
  float dX;
  int dYAW;

  int currYAW;
  int lastYAW = 0;

  int FL, FR, BL, BR;

  while (true) {
    // reset encoders
    encoderReset(FL_encoder);
    encoderReset(FR_encoder);
    encoderReset(BL_encoder);
    encoderReset(BR_encoder);

    // gyroReset(gyro);

    currYAW = gyroGet(gyro);

    // set tiny delay to allow for some tick accumulation
    delay(5);

    // record REAL time elapsed
    // dt = millis() - timeInitial;

    FL = encoderGet(FL_encoder);
    FR = encoderGet(FR_encoder);
    BL = encoderGet(BL_encoder);
    BR = encoderGet(BR_encoder);

    // calculate calculate the amount of ticks DISPLACED within this
    // timeframe
    dY = (FL + BR) * cos(ANGLE_OFFSET) + (FR + BL) * cos(-ANGLE_OFFSET);

    dX = (FL + BR) * sin(ANGLE_OFFSET) + (FR + BL) * sin(-ANGLE_OFFSET);

    dYAW = currYAW - lastYAW;

    // printf("YAW: %d\t dYAW: %d\t", currYAW, dYAW);

    lastYAW = currYAW;

    // printf("currY: %f\t currX: %f\t", currY, currX);
    // currYAW = gyroGet(gyro);

    // printf("dY: %f\t dX: %f\t", dY, dX);

    // integrate X & Y to get displacement from initial position
    if (abs(dYAW) < ROTATION_THRESHOLD) {
      // if (abs(dY) > DELTA_THRESHOLD)
      odometry.Y += dY;
      // if (abs(dX) > DELTA_THRESHOLD)
      odometry.X += dX;

      odometry.YAW = currYAW;
    }

    // printf("Y: %f\t X: %f\t", odometry.Y, odometry.X);

    // printf("\r\n");
    delay(20);
  }
}

void odometryReset() {
  odometry.Y = 0;
  odometry.X = 0;
  odometry.YAW = 0;
}
