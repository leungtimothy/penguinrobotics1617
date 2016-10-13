#include "auto_functions.h"
#include "drive.h"
#include "main.h"
#include "pid.h"
#include <math.h>

#define ANGLE_OFFSET 45

// PASS DESIRED DISTANCES IN CARTESIAN COORDINATES
void driveHolo(int targetY, int targetX) {
  // variables for odometry calculation
  int timeInitial;
  int dt;
  int dY;
  int dX;

  int currY;
  int currX;
  int currYAW;

  int lastY = 0;
  int lastX = 0;

  int sumY = 0;
  int sumX = 0;

  int targetYAW = gyroGet(gyro);

  PID pidY;
  pidInit(&pidY, 0.2, 0.0, 0.0, 0, 0);
  int outputY;

  PID pidX;
  pidInit(&pidX, 0.2, 0.0, 0.0, 0, 0);
  int outputX;

  PID pidYAW;
  pidInit(&pidYAW, 0.4, 0, 0, 0, 0);
  int outputYAW;

  // finish check variables
  int timeDelta = 0;
  int timePrevious = 0;
  bool isAtTarget = false;
  bool isTimerOn = false;

  while (!isAtTarget) {
    // reset encoders
    encoderReset(FL_encoder);
    encoderReset(FR_encoder);
    encoderReset(BL_encoder);
    encoderReset(BR_encoder);

    // record time
    timeInitial = millis();

    // set tiny delay to let some ticks to accumlate
    delay(20);

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

    // differentiate X & Y ticks in this timeframe
    dY = (currY - lastY) / dt;
    dX = (currX - lastX) / dt;

    // record ticks within this timeframe as previous values for next cycle
    lastY = currY;
    lastX = currX;

    // integrate X & Y to get displacement from initial position
    sumY += dY;
    sumX += dX;

    // record current gyroscope reading
    currYAW = gyroGet(gyro);

    // calculate p controller output
    outputY = pidCalculate(&pidY, sumY, targetY);
    outputX = pidCalculate(&pidX, sumX, targetX);
    outputYAW = pidCalculate(&pidYAW, currYAW, targetYAW);

    // FOR DEBUGGING
    printf("Y: %d\t X: %d\t YAW: %d\r\n", sumY, sumX, currYAW);

    // set drive channels
    driveSetChannel(Y, outputY);
    driveSetChannel(X, outputX);
    driveSetChannel(YAW, -outputYAW);

    // CHECK FOR FINISH
    // if robot is within 10 ticks of target and timer flag is off
    if ((abs(pidY.error) < 10 && abs(pidX.error) < 10) && !isTimerOn) {
      timeDelta = millis() - timePrevious;
      isTimerOn = true; // set timer flag to indicate timer is running
      timePrevious = millis();

      // if robot is not within 10 ticks of target
    } else if (abs(pidY.error) > 10 && abs(pidX.error) > 10)
      isTimerOn = false; // timer flag is reset

    // if the timer is over 250ms and timer flag is true
    if (timeDelta > 1000 && isTimerOn)
      isAtTarget = true; // set boolean to complete while loop

    // don't kill cortex
    delay(20);
  }
  driveStop();
}

/**
 * Use this function command the robot to rotate about its Z axis using the data
 * obtained via the gyroscope.
 *
 * @param turnDirection Choose LEFT or RIGHT for direction of turn.
 * @param targetDegrees the amount of degrees the robot will rotate relative to
 * its original bearing.
 *
 */
void driveGyroTurn(enum Turn_Directions turnDirection, int targetDegrees) {
  int drivePower = 0;

  PID pid;
  pidInit(&pid, 2.0, 0, 0.15, 0, 0);

  // min/max power
  int maxPower = 90;
  int minPower = 25;

  // finish check variables
  int timeDelta = 0;
  int timePrevious = 0;
  bool isAtTarget = false;
  bool isTimerOn = false;

  // initialize gyro data variables
  int targetReading = gyroGet(gyro);

  // get gyroscope target reading
  if (turnDirection == 7)
    targetReading += targetDegrees;
  else if (turnDirection == 8)
    targetReading -= targetDegrees;

  // run motors until target is within 1/2 degree certainty
  while (!isAtTarget) {
    drivePower = pidCalculate(&pid, gyroGet(gyro),
                              targetReading); // calculate PD loop output

    // cap between min and max power
    drivePower =
        drivePower < minPower && drivePower > 0
            ? minPower
            : drivePower > -minPower && drivePower < 0 ? -minPower : drivePower;
    drivePower = drivePower > maxPower
                     ? maxPower
                     : drivePower < -maxPower ? -maxPower : drivePower;

    driveSetChannel(YAW, -drivePower);

    // printf("Gyro Value: %d\tError: %d\r\n", gyroGet(gyro), error);

    // check for finish
    if (abs(pid.error) < 5 && !isTimerOn) { // if robot is within 1 degree of
                                            // target and timer flag is off
      timeDelta = millis() - timePrevious;
      isTimerOn = true; // set timer flag to indicate timer is running
      timePrevious = millis();
    } else if (abs(pid.error) > 5) // if robot is not within 1 degree of target
      isTimerOn = false;           // timer flag is reset

    if (timeDelta > 1000 &&
        isTimerOn)       // if the timer is over 250ms and timer flag is true
      isAtTarget = true; // set boolean to complete while loop

    delay(20);
  }

  // driveStop();
}
