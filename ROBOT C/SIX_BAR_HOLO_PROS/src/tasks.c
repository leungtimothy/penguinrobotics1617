#include "main.h"

void motorControlTask(void* ignore)
{
	while(isEnabled())
	{
		printf("Hey");
		taskDelay(20);
	}
}
