task driverMotorControl()
{
	//Motor Controller
		motor[RightFrontDrive] = motor[RightFrontDrive2] = RFrontDrive;
		motor[RightBackDrive] = motor[RightBackDrive2]= RBackDrive;
		motor[LeftFrontDrive] = LFrontDrive;
		motor[LeftBackDrive] = motor[LeftBackDrive2] = LBackDrive;
		motor[LeftArm] = motor[RightArm] = ArmPower;

}

task autoMotorControl()
{
		//Motor Controller
		motor[RightFrontDrive] = motor[RightFrontDrive2] = RFrontDrive;
		motor[RightBackDrive] = motor[RightBackDrive2]= RBackDrive;
		motor[LeftFrontDrive] = LFrontDrive;
		motor[LeftBackDrive] = motor[LeftBackDrive2] = LBackDrive;
		motor[LeftArm] = motor[RightArm] = ArmPower;

		RFrontDrive = motorCap(-(autoDriveYaw)+(autoDriveY)-(autoDriveX));
		RBackDrive 	= motorCap(-(autoDriveYaw)+(autoDriveY)+(autoDriveX));
		LFrontDrive = motorCap( (autoDriveYaw)+(autoDriveY)+(autoDriveX));
		LBackDrive 	= motorCap(	(autoDriveYaw)+(autoDriveY)-(autoDriveX));
}


