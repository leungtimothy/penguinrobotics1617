#include "main.h"
//~~~~~~~~~~~ Functions to control motors ~~~~~~~~~
void rightDrive(int speed){
	motorSet(rightFront, speed*rightFrontD);
	motorSet(rightBack, speed*rightBackD);
}

void leftDrive(int speed){
	motorSet(leftDriveFB, speed*leftDriveFBD);
	//motorSet(rightBack*rightBackD, speed);
}

void armSetValue(int speed){
	motorSet(rightArm, speed*rightArmD);
	motorSet(rightArm2, speed*rightArm2D);
	motorSet(leftArm, speed*leftArmD);
	//motorSet(rightArm*rightArmD, speed);
}

void strafe(int speed){
	motorSet(leftStrafe,speed*leftStrafeD);
	motorSet(rightStrafe,speed*rightStrafeD);
}
