#include "main.h"


// ** GYRO TURN **
// target (in degrees) is added/subtracted from current gyro reading to get a target gyro reading
// run PD loop to turn to target
// checks if target has been reached AND is at target for over 250ms before moving on
void gyroTurn (int turnDirection, int targetDegrees) {
	// initialize PD loop variables
	float kp = 0.25; 													// CHANGE CONSTANTS
	float kd = 0.5;
	int error = targetDegrees;
	int previousError = targetDegrees;
	int deltaError = 0;
	int drivePower = 0;

	// min/max power
	int maxPower = 90;
	int minPower = 20;

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

	printf("Gyro Value: %i\r\n", gyroGet(gyro));

	// run motors until target is within 1/2 degree certainty
	while (!isAtTarget)
	{
		error = targetReading - gyroGet(gyro); 		// calculate error
		deltaError = error - previousError;			// calculate deltaError
		drivePower = error * kp + deltaError * kd;	// calculate PD loop output
		previousError = error;						// set new previous error

		// cap between min and max power
		drivePower = drivePower < minPower && drivePower > 0 ? minPower : drivePower > -minPower && drivePower < 0 ? -minPower : drivePower;
		drivePower = drivePower > maxPower ? maxPower : drivePower < -maxPower ? -maxPower : drivePower;

		driveSetChannel(YAW, -drivePower);

		// check for finish
		if (abs(error) < 5 && !isTimerOn) 			// if robot is within 0.5 degrees of target and timer flag is off
		{
			timeDelta = micros() - timePrevious;
			isTimerOn = true;						// set timer flag to indicate timer is running
			timePrevious = micros();
		}
		else if (abs(error) > 5)					// if robot is not within 0.5 degrees of target
			isTimerOn = false;						// timer flag is reset

		if (timeDelta > 250 && isTimerOn)			// if the timer is over 250ms and timer flag is true
			isAtTarget = true;						// set boolean to complete while loop
	}

	driveStop();
}
