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