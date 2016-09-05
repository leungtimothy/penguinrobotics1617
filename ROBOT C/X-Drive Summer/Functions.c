// Autonomous Functions

int motorCap(int motorPowervalue)
{

	if (motorPowervalue >= 127)
	{
		return (127);
	}
	else if (motorPowervalue <= -127)
	{
		return (-127);
	}
	return (motorPowervalue);
}

void drive(int degrees, int power)
{
	//AutoDriveX
	//AutoDriveY
	//AutoDriveYaw
	while(/*not there yet*/0)
	{
		AutoDriveY = cosDegrees(degrees)*power;
		AutoDriveX = sinDegrees(degrees)*power;

		// AutoDriveYaw = SensorValue[Gyro];
	}
}

/*

// rive function, corrects for rotation
void drive(int degrees, int power, int encoderTicks) {
	int targetGyroReading = SensorValue[Gyro];

	int gyroError = 0;
	int translationalError = 0;

	float kp = 0;
	while (true //!isTime) {
		gyroError = targetGyroReading - SensorValue[Gyro];
		translationalError = (SensorValue[FrontLeft]+SensorValue[BackRight])-(SensorValue[FrontRight]+SensorValue[BackLeft]);

		AutoDriveY = cosDegrees(degrees) * power - abs(tranlastionalError)*translateKp;
		AutoDriveX = sinDegrees(degrees) * power - traslationalError*translateKp;
		AutoDriveYaw = gyroError * yawKp;
	}
}

void turn(int degrees, int power)
{


}
*/

// Driver Control Functions
