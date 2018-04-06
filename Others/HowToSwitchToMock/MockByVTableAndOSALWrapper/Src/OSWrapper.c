#include <stdint.h>
#include "OS.h"
#include "OSWrapper.h"

static int OSWrapper_getTime_impl()
{ 
	time_t time;
	OS_getTime(&time);
	return (int)time;
}

static int OSWrapper_sendMsg_impl(int queue, void* msg)
{
	return OS_sendMsg(queue, msg);
}

static int OSWrapper_recvMsg_impl(int queue, void* msg)
{
	return OS_sendMsg(queue, msg);
}

OS_FUNC os = {
	.getTime = OSWrapper_getTime_impl,
	.sendMsg = OSWrapper_sendMsg_impl,
	.recvMsg = OSWrapper_recvMsg_impl,
};
