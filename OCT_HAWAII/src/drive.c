#include "drive.h"

/**
 * Use this function to set the individual drive motors of the holonomic drive.
 *
 * @param motor_location Choose one of FRONT_LEFT, FRONT_RIGHT, BACK_LEFT and BACK_RIGHT to set the speed of.
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void setDrive(int motor_location, int value)
{
	// Verify motor value is between -127 and 127;
	value = motorCap(value);

	// Choose the motor port(s) to set
	switch(motor_location)
	{
		case RIGHT:
			motorSet(RIGHT_DRIVE_MOTOR,value*MOTOR_5_DIR);
			motorSet(RIGHT_DRIVE_MOTOR_2,value*MOTOR_6_DIR);
			break;
		case LEFT:
			motorSet(LEFT_DRIVE_MOTOR,value*MOTOR_7_DIR);
			break;

		case STRAFE:
			motorSet(STRAFE_FRONT,value*MOTOR_3_DIR);
			motorSet(STRAFE_REAR,value*MOTOR_10_DIR);
			break;

		default:
			break;
	}
}

int drive(Direction dir, int distance, int power)
{
  encoderReset(leftEncoder);
  encoderReset(rightEncoder);



    float kPa = 0.1;
    float kPd = 0.1;

  while(abs((encoderGet(leftEncoder)+encoderGet(rightEncoder))/2) <  distance/2)
  {
    int leftRightError = encoderGet(leftEncoder) - encoderGet(rightEncoder);
    //int acceleration = (abs(encoderGet(leftEncoder)+encoderGet(rightEncoder)/2)*kPa*dir;
    int acceleration = 0;

    int leftMotorValue = /* MIN_MOVE_POWER*dir + acceleration*/ power*dir - leftRightError*STRAIGHT_CONSTANT;
    int rightMotorValue = /*MIN_MOVE_POWER*dir + acceleration*/ power*dir + leftRightError*STRAIGHT_CONSTANT;
/*
    if(leftMotorValue > power)
      leftMotorValue = power;

    if(rightMotorValue > power)
      rightMotorValue = power;
*/
    setDrive(LEFT, leftMotorValue);
    setDrive(RIGHT, rightMotorValue);
  }

  while(abs((encoderGet(leftEncoder)+encoderGet(rightEncoder))/2) <  distance)
  {
    int leftRightError = encoderGet(leftEncoder) - encoderGet(rightEncoder);
    //int acceleration = (abs(encoderGet(leftEncoder)+encoderGet(rightEncoder)/2)*kPa*dir;
    int decceleration = 0;

		int leftMotorValue = /* MIN_MOVE_POWER*dir + acceleration*/ power*dir - leftRightError*STRAIGHT_CONSTANT;
		int rightMotorValue = /*MIN_MOVE_POWER*dir + acceleration*/ power*dir + leftRightError*STRAIGHT_CONSTANT;

/*    if(leftMotorValue > power)
      leftMotorValue = power;

    if(rightMotorValue > power)
      rightMotorValue = power;
*/
    setDrive(LEFT, leftMotorValue);
    setDrive(RIGHT, rightMotorValue);

  }

	setDrive(LEFT, 10*dir);
	setDrive(RIGHT, 10*dir);


  return 0;
}

int turn(Direction dir, int distance, int power)
{
	encoderReset(leftEncoder);
  encoderReset(rightEncoder);

	if(dir == TURN_RIGHT)
	{
			while(encoderGet(leftEncoder) < distance )
			{
				setDrive(LEFT, power);
				setDrive(RIGHT, -power);
			}
	}
	else if(dir == TURN_LEFT)
	{
		while(encoderGet(rightEncoder) < distance )
		{
			setDrive(LEFT, -power);
			setDrive(RIGHT, power);
			printf("help: %d, \n",encoderGet(rightEncoder));
			delay(20);
		}

	}
	setDrive(LEFT, 0);
	setDrive(RIGHT, 0);

	return 1;
}
