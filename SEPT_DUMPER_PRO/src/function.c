#include "main.h"
//~~~~~~~~~~~ Functions to control motors ~~~~~~~~~
void rightDrive(int speed){
	motorSet(rightDrive1, speed*rightDriveD);
}

void leftDrive(int speed){
	motorSet(leftDriveF, speed*leftDriveFD);
	motorSet(leftDriveB, leftDriveBD*speed);
}

void armSetValue(int speed){
	motorSet(leftArmT, speed*leftArmTD);
	motorSet(leftArmB, speed*leftArmBD);
	motorSet(rightArm, speed*rightArmD);
	//motorSet(rightArm*rightArmD, speed);
}

void strafe(int speed){
	motorSet(leftStrafe,speed*leftStrafeD);
	motorSet(rightStrafe,speed*rightStrafeD);
}

