#include "drive.h"
#include "main.h"
#include "util.h"
#include <math.h>

#define ANGLE_OFFSET 45
#define DELTA_THRESHOLD 0

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
  // variables for odometry calculation
  int timeInitial;
  int dt;
  int dY;
  int dX;
  // int dYAW;

  int currY;
  int currX;
  // int currYAW;

  int lastY = 0;
  int lastX = 0;
  // int lastYAW = 0;

  while (true) {
    // reset encoders
    encoderReset(FL_encoder);
    encoderReset(FR_encoder);
    encoderReset(BL_encoder);
    encoderReset(BR_encoder);

    // gyroReset(gyro);

    // record time
    timeInitial = millis();

    // set tiny delay to allow for some tick accumulation
    delay(5);

    // record REAL time elapsed
    dt = millis() - timeInitial;

    // calculate calculate the amount of ticks DISPLACED within this timeframe
    currY =
        ((encoderGet(FL_encoder) + encoderGet(BR_encoder)) * cos(ANGLE_OFFSET) +
         (encoderGet(FR_encoder) + encoderGet(BL_encoder)) *
             cos(-ANGLE_OFFSET)) /
        2;

    currX =
        ((encoderGet(FL_encoder) + encoderGet(BR_encoder)) * sin(ANGLE_OFFSET) +
         (encoderGet(FR_encoder) + encoderGet(BL_encoder)) *
             sin(-ANGLE_OFFSET)) /
        2;

    // currYAW = gyroGet(gyro);

    // differentiate X & Y ticks in this timeframe
    dY = (currY - lastY) / dt;
    dX = (currX - lastX) / dt;

    // dYAW = (currYAW - lastYAW) / dt;

    // record ticks within this timeframe as previous values for next cycle
    lastY = currY;
    lastX = currX;

    // lastYAW = currYAW;

    // integrate X & Y to get displacement from initial position
    if (abs(dY) > DELTA_THRESHOLD)
      odometry.Y += dY;
    if (abs(dX) > DELTA_THRESHOLD)
      odometry.X += dX;

    odometry.YAW = gyroGet(gyro);

    delay(20);
  }
}

void resetOdometry() {
  odometry.Y = 0;
  odometry.X = 0;
  odometry.YAW = 0;
}
