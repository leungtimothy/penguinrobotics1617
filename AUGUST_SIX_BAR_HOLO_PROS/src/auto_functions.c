#include "auto_functions.h"
#include "drive.h"
#include "main.h"
#include "pid.h"
#include <math.h>

void driveHolo(int distance, int power) {
  encoderReset(BL_encoder);
  encoderReset(BR_encoder);
  encoderReset(FL_encoder);
  encoderReset(FR_encoder);

  PID FLBR_pid;
  pidInit(&FLBR_pid, 2, 0.0, 0.0, 0, 0);

  PID FRBL_pid;
  pidInit(&FRBL_pid, 2, 0.0, 0.0, 0, 0);

  PID overall_pid;
  pidInit(&overall_pid, 0.2, 0.0, 0.0, 0, 0);

  // finish check variables
  int timeDelta = 0;
  int timePrevious = 0;
  bool isAtTarget = false;
  bool isTimerOn = false;

  while (!isAtTarget) {
    int FLBR =
        pidCalculate(&FLBR_pid, encoderGet(FL_encoder), encoderGet(BR_encoder));
    int FRBL =
        pidCalculate(&FRBL_pid, encoderGet(FR_encoder), encoderGet(BL_encoder));

    int overall_pid_error = pidCalculate(
        &overall_pid, (FLBR_pid.error + FRBL_pid.error) / 2, distance);

    driveSetPower(FRONT_LEFT, power + FLBR + overall_pid_error);
    driveSetPower(BACK_RIGHT, power - FLBR + overall_pid_error);

    driveSetPower(FRONT_RIGHT, power + FRBL - overall_pid_error);
    driveSetPower(BACK_LEFT, power - FRBL - overall_pid_error);

    // check for finish
    if (abs(overall_pid.error) < 10 && !isTimerOn) { // if robot is within 10
                                                     // ticks of target and
                                                     // timer flag is off
      timeDelta = millis() - timePrevious;
      isTimerOn = true; // set timer flag to indicate timer is running
      timePrevious = millis();
    } else if (abs(overall_pid.error) >
               10)       // if robot is not within 1 degree of target
      isTimerOn = false; // timer flag is reset

    if (timeDelta > 1000 &&
        isTimerOn)       // if the timer is over 250ms and timer flag is true
      isAtTarget = true; // set boolean to complete while loop

    delay(20);
  }
}

#define ANGLE_OFFSET 45

// PASS DESIRED DISTANCES IN CARTESIAN COORDINATES
void driveHoloTest(int targetY, int targetX) {
  // reset encoders
  encoderReset(BL_encoder);
  encoderReset(BR_encoder);
  encoderReset(FL_encoder);
  encoderReset(FR_encoder);

  int FLBR;
  int FRBL;

  int currY;
  int currX;

  PID pidY;
  pidInit(&pidY, 0.5, 0.0, 0.0, 0, 0);
  int outputY;

  PID pidX;
  pidInit(&pidX, 0.5, 0.0, 0.0, 0, 0);
  int outputX;

  // finish check variables
  int timeDelta = 0;
  int timePrevious = 0;
  bool isAtTarget = false;
  bool isTimerOn = false;

  while (!isAtTarget) {
    // average out enocder ticks of the two sets of wheels
    FLBR = (encoderGet(FL_encoder) + encoderGet(BR_encoder)) / 2;
    FRBL = (encoderGet(FR_encoder) + encoderGet(BL_encoder)) / 2;

    // get the current X, Y position relative to its initial position
    currY = FLBR * cos(ANGLE_OFFSET) + FRBL * cos(-ANGLE_OFFSET);
    currX = FLBR * sin(ANGLE_OFFSET) + FRBL * sin(-ANGLE_OFFSET);

    // calculate p controller output
    outputY = pidCalculate(&pidY, currY, targetY);
    outputX = pidCalculate(&pidX, currX, targetX);

    // FOR DEBUGGING
    printf("Y: %d\t X: %d\r\n", outputY, outputX);

    // set drive channels
    driveSetChannel(Y, outputY);
    driveSetChannel(X, outputX);

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
    if (timeDelta > 250 && isTimerOn)
      isAtTarget = true; // set boolean to complete while loop

    // don't kill cortex
    delay(20);
  }

  // turn drive motors off
  driveSetChannel(Y, 0);
  driveSetChannel(X, 0);
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
