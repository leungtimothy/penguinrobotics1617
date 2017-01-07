#include "arm.h"

int armGetPosition() {
  if (isArmPotFlipped)
    return abs(4095 - analogRead(ARM_POT));
  else
    return analogRead(ARM_POT);
}

int armLowerLimitGetStatus(){
  return !digitalRead(LOWER_ARM_LIMIT_BUTTON);
}

/**
 * Use this function to set the speed of all of the arm motors.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void setArmMotors(int value)
{
	value = motorCap(value,127);

	motorSet(LEFT_ARM_MOTOR, value*MOTOR_4_DIR);
	motorSet(RIGHT_ARM_INSIDE_MOTOR, value*MOTOR_8_DIR);
	motorSet(RIGHT_ARM_OUTSIDE_MOTOR, value*MOTOR_1_DIR);
	motorSet(LEFT_ARM_MOTOR_INSIDE_TOP, value*MOTOR_10_DIR);
	motorSet(RIGHT_ARM_INSIDE_MOTOR_TOP, value*MOTOR_3_DIR);
}

int armHold = 0;
int armPos = 0;

void armTask(void *ignore)
{
	armHold = 1;
	armPos = armGetPosition();
	float kp = 0.2;
	while(true)
	{
		if(armHold)
		{
			int errorArm = armPos - armGetPosition();
			errorArm = motorCap(errorArm*kp,127);
			setArmMotors(errorArm);
		  //printf("armpot: %d\n",armGetPosition());
			//printf("lowerlimitstatus:%d \n",armLowerLimitGetStatus());
		}
		delay(20);
	}
}
