#include <stdio.h>
#include "FakeMicroTime.h"

/*****************************************
 * Data containers and accessors
 *****************************************/
static int s_time;
static int s_increment;
static int s_totalDelay;
int FakeMicroTime_init(int start, int incr)
{
	s_time = start;
	s_increment = incr;
	s_totalDelay = 0;
}

/*****************************************
 * Mock functions
 *****************************************/
int MicroTime_get()
{
	int t = s_time;
	s_time += s_increment;
	return t;
}
