#include "drive.h"
#include "main.h"
#include "util.h"

/**
 * Use this function to set the individual drive motors of the holonomic drive.
 *
 * @param motor_location Choose one of FRONT_LEFT, FRONT_RIGHT, BACK_LEFT and BACK_RIGHT to set the speed of.
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 *
 */
void driveSetPower(Motor_Positions motor_location, int value) {
	// Verify motor value is between -127 and 127;
	value = motorCap(value);

	// Choose the motor port(s) to set
	switch(motor_location)
	{
		case FRONT_LEFT:
			motorSet(FRONT_LEFT_DRIVE_MOTOR,value*MOTOR_1_DIR);
			break;

		case FRONT_RIGHT:
			motorSet(FRONT_RIGHT_DRIVE_MOTOR,value*MOTOR_10_DIR);
			break;

		case BACK_LEFT:
			motorSet(BACK_LEFT_DRIVE_MOTOR,value*MOTOR_5_DIR);
			break;

		case BACK_RIGHT:
			motorSet(BACK_RIGHT_DRIVE_MOTOR,value*MOTOR_2_DIR);
			motorSet(BACK_RIGHT_DRIVE_MOTOR_2,value*MOTOR_3_DIR);
			break;

		default:
			break;
	}
}

/**
 * Use this function to set a drive channel of the holonomic drive.
 *
 * @param channel Choose one of X, Y, or YAW to set the speed of.
 * @param value the new signed speed; -127 is full reverse and 127 is full forward, with 0
 * being off. If the value is > 127 or < -127, it will be rounded.
 */
void driveSetChannel(Drive_Channels channel, int value) {
	value = motorCap(value);

	switch(channel) {
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

	driveSetPower(FRONT_LEFT,  driveChannels.powerY + driveChannels.powerX + driveChannels.powerYaw);
	driveSetPower(FRONT_RIGHT, driveChannels.powerY - driveChannels.powerX - driveChannels.powerYaw);
	driveSetPower(BACK_LEFT,   driveChannels.powerY - driveChannels.powerX + driveChannels.powerYaw);
	driveSetPower(BACK_RIGHT,  driveChannels.powerY + driveChannels.powerX - driveChannels.powerYaw);
}

/**
 * Use this function to stop all drive motors.
 */
void driveStop() {
	driveSetPower(FRONT_LEFT,	0);
	driveSetPower(FRONT_RIGHT,	0);
	driveSetPower(BACK_LEFT,	0);
	driveSetPower(BACK_RIGHT,	0);
}
