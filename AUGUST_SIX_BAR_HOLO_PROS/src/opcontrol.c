/**
 * File for operator control code.
 *
 * This file should contain the user operatorControl() function and any
 *functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 *modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 *list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
 *this list of conditions and the following disclaimer in the documentation
 *and/or other materials provided with the distribution.
 * Neither the name of Purdue University ACM SIG BOTS nor the names of its
 *contributors may be used to endorse or promote products derived from this
 *software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 *DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source
 *code may be obtained from http://sourceforge.net/projects/freertos/files/ or
 *on request.
 ********************************************************************************/

#include "arm.h"
#include "claw.h"
#include "drive.h"
#include "main.h"
#include "util.h"

/**
 * Runs the user operator control code.
 *
 * This function will be started in its own task with the default priority and
 * stack size whenever the robot is enabled via the Field Management System or
 * the VEX Competition Switch in the operator control mode. If the robot is
 * disabled or communications is lost, the operator control task will be stopped
 * by the kernel. Re-enabling the robot will restart the task, not resume it
 * from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the
 * VEX Cortex will run the operator control task. Be warned that this will also
 * occur if the VEX Cortex is tethered directly to a computer via the USB A to A
 * cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is
 * available and the scheduler is operational. However, proper use of delay() or
 * taskDelayUntil() is highly recommended to give other tasks (including system
 * tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop,
 * even if empty.
 */
void operatorControl() {
  while (true) {
    /* --- Holonomic Drive --- */
    // Get joystick values
    int joystick_1_1 = joystickGetAnalog(1, 1);
    int joystick_1_3 = joystickGetAnalog(1, 3);
    int joystick_1_4 = joystickGetAnalog(1, 4);

    if (abs(joystick_1_3) > JOYSTICK_DEADZONE)
      driveSetChannel(Y, joystick_1_3);
    else
      driveSetChannel(Y, 0);

    if (abs(joystick_1_4) > JOYSTICK_DEADZONE)
      driveSetChannel(X, joystick_1_4);
    else
      driveSetChannel(X, 0);

    if (abs(joystick_1_1) > JOYSTICK_DEADZONE)
      driveSetChannel(YAW, joystick_1_1);
    else
      driveSetChannel(YAW, 0);

    /*driveSetPower(FRONT_LEFT, joystick_1_3 + joystick_1_4 + joystick_1_1);
    driveSetPower(FRONT_RIGHT, joystick_1_3 - joystick_1_4 - joystick_1_1);
    driveSetPower(BACK_LEFT, joystick_1_3 - joystick_1_4 + joystick_1_1);
    driveSetPower(BACK_RIGHT, joystick_1_3 + joystick_1_4 - joystick_1_1);*/

    /* --- End Holonomic Drive --- */

    if (joystickGetDigital(1, 7, JOY_DOWN))
      odometryReset();

    // bool joystickGetDigital(unsigned char joystick, unsigned char
    // buttonGroup, unsigned char button);
    // * @param buttonGroup one of 5, 6, 7, or 8 to request that button as
    // labelled on the joystick
    //* @param button one of JOY_UP, JOY_DOWN, JOY_LEFT, or JOY_RIGHT;
    // requesting JOY_LEFT or
    if (joystickGetDigital(1, 8, JOY_UP))
      armSetTarget(OUTSIDE_FENCE_SCORING_HEIGHT);
    else if (joystickGetDigital(1, 8, JOY_RIGHT))
      armSetTarget(OUTSIDE_FENCE_PUSH_HEIGHT);
    else if (joystickGetDigital(1, 8, JOY_LEFT))
      armSetTarget(MIDDLE_FENCE_PUSH_HEIGHT);
    else if (joystickGetDigital(1, 8, JOY_DOWN))
      armSetTarget(GROUND_HEIGHT);

    if (joystickGetDigital(1, 5, JOY_UP) || joystickGetDigital(2, 5, JOY_UP))
      armSetManual(UP);
    else if (joystickGetDigital(1, 5, JOY_DOWN) ||
             joystickGetDigital(2, 5, JOY_DOWN))
      armSetManual(DOWN);
    else
      armSetManual(AUTO);

    if (joystickGetDigital(1, 6, JOY_UP))
      clawSetPower(80);
    // clawSetting(OPEN);

    else if (joystickGetDigital(1, 6, JOY_DOWN))
      clawSetPower(-60);
    // clawSetting(CLOSE);
    else
      clawSetPower(0);
    // clawSetting(HOLD);

    /*if(joystickGetDigital(1,8,JOY_DOWN))
    {
            digitalWrite(CLAW_PISTON_PORT, HIGH);
    }
    else if(joystickGetDigital(1,8,JOY_RIGHT))
    {
            digitalWrite(CLAW_PISTON_PORT, LOW);
    }*/

    if (joystickGetDigital(2, 8, JOY_DOWN)) {
      digitalWrite(CLAW_PISTON_PORT, HIGH);
    } else if (joystickGetDigital(2, 8, JOY_RIGHT)) {
      digitalWrite(CLAW_PISTON_PORT, LOW);
    }

    delay(20);
  }
}
