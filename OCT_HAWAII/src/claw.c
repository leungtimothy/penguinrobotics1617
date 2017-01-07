#include "claw.h"
#include "arm.h"

/**
 * Use this function to set the7 speed of the claw motor.
 *
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void setClawMotors(int value)
{
	value = motorCap(value,127);

	motorSet(CLAW_MOTOR_2, value*MOTOR_9_DIR);
	motorSet(CLAW_MOTOR, value * MOTOR_2_DIR);
}

int clawGetPosition(){
	if (isClawPotFlipped)
		return abs(4095 - analogRead(CLAW_POT));
	else
		return analogRead(CLAW_POT);
}

void waitUntilClawPos(int pos)
{
	while(clawGetPosition()>pos)
	{
		delay(20);
	}
}

void clawTask(void *ignore)
{
  //Just in case

  claw.holdTarget = clawGetPosition();
  claw.status = HOLDING;

  // Use to prevent redundant writes!
  int lastSetMotorValue = 0;



	while(true)
	{
		//	printf("CLAW  POs: %d\n",clawGetPosition());
		if(claw.status == HOLDING || claw.status == SETPOINT )
		{
			int error = claw.holdTarget - clawGetPosition();
			int motorValue;

			if(claw.status == HOLDING)
      	motorValue = motorCap(error*CLAW_HOLD_KP,127);
			else if(claw.status == SETPOINT)
				motorValue = motorCap(error*CLAW_MOVE_KP,127);

      if(motorValue != lastSetMotorValue)
      {
          if(claw.status == HOLDING)
          {
              if(motorValue >0 && motorValue > MAX_HOLD_POWER)
                motorValue = MAX_HOLD_POWER;
              else if(motorValue < 0 && motorValue < -MAX_HOLD_POWER)
                motorValue = -MAX_HOLD_POWER;
          }
					else if(claw.status == SETPOINT)
					{
						if(motorValue >0 && motorValue > MAX_SETPOINT_MOVE_POWER)
							motorValue = MAX_SETPOINT_MOVE_POWER;
						else if(motorValue < 0 && motorValue < -MAX_SETPOINT_MOVE_POWER)
							motorValue = -MAX_SETPOINT_MOVE_POWER;
					}



          //setClawMotors(motorValue);
          lastSetMotorValue = motorValue;

					if(claw.autoOpenTrigger != -1)
					{
						if(armGetPosition() > claw.autoOpenTrigger )
						{
							claw.holdTarget = claw.autoOpenPos;
							claw.autoOpenTrigger = -1;
						}
					}

      }
		}

		delay(20);
	}
}
