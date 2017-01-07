#ifndef ARM_H_
#define ARM_H_

#include "main.h"

extern int armHold;
extern int armPos;

int armGetPosition();
void armTask(void* ignore);
int armLowerLimitGetStatus();


#endif
