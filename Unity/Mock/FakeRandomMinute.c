#include <stdio.h>
#include "FakeRandomMinute.h"

/*****************************************
 * Data containers and accessors
 *****************************************/
static int s_value;
static int s_delta;
void FakeRandomMinute_setFirstandIncrement(int initialValue, int delta)
{
	s_value = initialValue;
	s_delta = delta;
}

/*****************************************
 * Mock functions
 *****************************************/
int FakeRandomMinute_get()
{
	int retValue = s_value;
	s_value += s_delta;
	return retValue;
}