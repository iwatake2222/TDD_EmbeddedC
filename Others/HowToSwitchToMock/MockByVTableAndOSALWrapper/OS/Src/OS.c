#include <stdint.h>
#include <time.h>
#include "OS.h"

int OS_getTime(time_t* t)
{
	time_t _t = time(NULL);
	*t = _t;
	return 0;
}

int OS_sendMsg(int queue, void* msg)
{
	return 0;
}

int OS_recvMsg(int queue, void* msg)
{
	return 0;
}
