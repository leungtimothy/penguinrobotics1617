#pragma config(Sensor, dgtl1,  PClaw,          sensorDigitalOut)
#pragma config(Motor,  port1,           LeftBackDrive, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           RightArm,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LeftArm,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           RightBackDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           RightBackDrive2, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RightFrontDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           RightFrontDrive2, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LeftFrontDrive, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          LeftBackDrive2, tmotorVex393_HBridge, openLoop, reversed)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Constants.c"
#inc

//global variable
//Drive Variables
int driveDirectionF = 0;
int driveDirectionT = 0;
int driveDirectionH = 0;

int RFrontDrive	= 0;
int RBackDrive	= 0;
int LFrontDrive	= 0;
int LBackDrive	= 0;

int ArmPower = 0;
int last_Btn5U_Value = 0;

//Autonomous Variables

int autoDriveY = 0;
int autoDriveX = 0;
int autoDriveYaw = 0;


#include "Functions.c"
#include "Tasks.c"
#include "Autonomous.c"
/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	startTask(autoMotorControl);
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	startTask(driverMotorControl);
	while(true){



		//~~~~~~~~~~~~~~~~~~ Drive direction for Truespeed ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if(vexRT[Ch3] > 10)
		{
			driveDirectionF = 1;
		}
		else if (vexRT[Ch3] < 10)
		{
			driveDirectionF = -1;
		}
		if(vexRT[Ch4] > 10)
		{
			driveDirectionH = 1;
		}
		else if (vexRT[Ch4] < 10)
		{
			driveDirectionH = -1;
		}
		if (vexRT[Ch1]>10)
		{
			driveDirectionT = 1;
		}
		else if (vexRT[Ch1]<10)
		{
			driveDirectionT = -1;
		}
		//~~~~~~~~~Drive Controls~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		RFrontDrive = motorCap(-(TrueSpeed[abs(vexRT[Ch1])]*driveDirectionT)+(TrueSpeed[abs(vexRT[Ch3])]*driveDirectionF)
		- (TrueSpeed[abs(vexRT[Ch4])]*driveDirectionH));
		RBackDrive = motorCap(-(TrueSpeed[abs(vexRT[Ch1])]*driveDirectionT)+(TrueSpeed[abs(vexRT[Ch3])]*driveDirectionF)
		+ (TrueSpeed[abs(vexRT[Ch4])]*driveDirectionH));
		LFrontDrive = motorCap((TrueSpeed[abs(vexRT[Ch1])]*driveDirectionT)+(TrueSpeed[abs(vexRT[Ch3])]*driveDirectionF)
		+ (TrueSpeed[abs(vexRT[Ch4])]*driveDirectionH));
		LBackDrive = motorCap((TrueSpeed[abs(vexRT[Ch1])]*driveDirectionT)+(TrueSpeed[abs(vexRT[Ch3])]*driveDirectionF)
		- (TrueSpeed[abs(vexRT[Ch4])]*driveDirectionH));

		//~~~~~~~~~~~~ ARM CONTROL~~~~~~~~~~

		if(vexRT[Btn5U])
			ArmPower = 127;
		else if (vexRT[Btn5D])
			ArmPower = -60;
		else
			ArmPower = 0;


		//~~~~~~~~~~~~~~~~~~~~~~CLAW FOR MOTORS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if(vexRT[Btn6U])
			motor[Claw] = 127;
		else if(vexRT[Btn6D])
			motor[Claw] = -127;
		else if(vexRT[Btn8U])
			motor[Claw] = 15;
		else
			motor[Claw] = 0;

		//~~~~~~~~~~~~~~~~~~~~~~~~~CLAW~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		int curr_Btn5U_Value = vexRT[Btn8D];
		if (vexRT[Btn8D] ==1 && curr_Btn5U_Value != last_Btn5U_Value && SensorValue[PClaw] ==0)
		{
			SensorValue[PClaw] = 1;
		}
		else if (vexRT[Btn8D] ==1 && curr_Btn5U_Value != last_Btn5U_Value && SensorValue[PClaw] == 1)
		{
			SensorValue[PClaw] = 0;
		}
		last_Btn5U_Value = curr_Btn5U_Value;
	}
}
