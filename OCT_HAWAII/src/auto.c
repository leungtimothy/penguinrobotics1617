
/**
* File for autonomous code.
*
* This file should contain the user autonomous() function and any functions related to it.
*
* Copyright (c) 2011-2014, Purdue University ACM SIG BOTS. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* Neither the name of Purdue University ACM SIG BOTS nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be obtained from http://sourceforge.net/projects/freertos/files/ or on request.
********************************************************************************/

#include "main.h"
#include "claw.h"
#include "drive.h"
#include "arm.h"

/**
* Runs the user autonomous code.
*
* This function will be started in its own task with the default priority and stack size whenever the robot is enabled via the Field Management System or the VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart the task, not re-start it from where it left off.
*
* Code running in the autonomous task cannot access information from the VEX Joystick. However, the autonomous function can be invoked from another task if a VEX Competition Switch is not available, and it can access joystick information if called in this way.
*
* The autonomous task may exit, unlike operatorControl() which should never exit. If it does so, the robot will await a switch to another mode or disable/enable cycle.
*/
void autonomous() {
  //analogCalibrate(3);

  claw.status = SETPOINT;
  claw.holdTarget = 1800;
  driveDP(-1, 190, 127, 5000,0.4);
  delay(1500);
  driveADP(1,100,70,5000,1.5,1.5);
  delay(1500);
  claw.status = SETPOINT;
  claw.holdTarget = 1050;
  delay(1000);
  armPos = 1000;
  delay(500);
  armPos = 2300;
  driveADP(-1,850,127,5000,1.5,1.5);

    claw.autoOpenPos = 2800;
    claw.autoOpenTrigger = 1550;

  //driveAP(int dir, int distance, int maxPower, int timeout,float acclerationConst = 0.3);;
  //claw.autoOpenPos = 1750;
  //claw.autoOpenTrigger = 2000;
  delay(20000);

/*
  claw.status = SETPOINT;
  armHold = 1;
  drive(BACKWARD,200,60);
  delay(500);
  claw.holdTarget=1500;
  delay(900);
  claw.holdTarget=3050;
  delay(700);
  armPos = 900;
  delay(500);
  armPos = 2850;
  claw.autoOpenPos = 1750;
  claw.autoOpenTrigger = 2000;
  drive(BACKWARD,600,127);
  delay(1000);
  armPos = 800;
  delay(1000);
  drive(FORWARD,500,70);
  delay(500);
  claw.holdTarget = 2750;//cube
  delay(700);
  armPos = 900;
  delay(500);
  armPos = 2850;
  claw.autoOpenPos = 1750;
  claw.autoOpenTrigger = 2000;
  drive(BACKWARD,600,127);
  delay(1500);
  armPos = 800;
  delay(1000);
  drive(FORWARD,500,70);
  delay(500);
  claw.holdTarget = 2750;//cube 2
  delay(700);
  armPos = 900;
  delay(500);
  armPos = 2850;
  claw.autoOpenPos = 1750;
  claw.autoOpenTrigger = 2000;
  drive(BACKWARD,600,127);
  delay(1500);
  armPos = 800;
  delay(1000);
  drive(FORWARD,500,70);
  delay(500);
  claw.holdTarget = 3000;//stars
  delay(700);
  armPos = 900;
  delay(500);
  armPos = 2850;
  claw.autoOpenPos = 1750;
  claw.autoOpenTrigger = 2000;
  drive(BACKWARD,600,127);
  delay(1500);
  armPos = 800;
  delay(1000);
  drive(FORWARD,500,70);
  delay(500);

*/
  /*
  claw.holdTarget = 1500;
  waitUntilClawPos(1600);
  drive(FORWARD,150,70);
  delay(500);
  claw.holdTarget = 2500;
  delay(500);
  drive(FORWARD,420,60);
  delay(500);
  claw.holdTarget = 3050;
  delay(100);
  drive(BACKWARD,195,60);
  delay(250);
  turn(TURN_LEFT,50,50);
  delay(500);
  armPos = 2000;
  delay(500);
  drive(FORWARD,400,70);
  delay(500);//  claw
  claw.holdTarget = 2000; // Dump 2
  delay(500);
  drive(BACKWARD,150,80); // Backup
  delay(500);
  armPos = 2000;
  delay(500);
  claw.holdTarget = 1600; // Go flat and push
  delay(1000);
  drive(FORWARD,250,90);
  delay(500);
  armPos = 2300;
  claw.holdTarget = 2300;
  delay(500);
  drive(BACKWARD,500,70);
  delay(500);
  armPos = 800;
  delay(500);
  turn(TURN_LEFT,400,60);
  */
}
