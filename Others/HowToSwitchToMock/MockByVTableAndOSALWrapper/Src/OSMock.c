#include <stdio.h>
#include "OSMock.h"

OS_FUNC s_savedOs;

static int s_timeStart;
static int s_timeIncrement;

/******************************************
 * Mock Functions
 ******************************************/
static int OSWrapper_getTime_mock()
{ 
	int ret = s_timeStart;
	s_timeStart += s_timeIncrement;
	return ret;
}

static int OSWrapper_sendMsg_mock(int queue, void* msg)
{
	printf("send(queue = %d, msg = %p)\n", queue, msg);
	return 0;
}

static int OSWrapper_recvMsg_mock(int queue, void* msg)
{
	printf("recv(queue = %d, msg = %p)\n", queue, msg);
	*(int*)msg = 0xABCD0123;
	return 0;
}

/******************************************
 * Additional Functions
 ******************************************/
void OSMock_create()
{
	/* store functions */
	s_savedOs = os;

	/* override functions */
	os.getTime = OSWrapper_getTime_mock;
	os.sendMsg = OSWrapper_sendMsg_mock;
	os.recvMsg = OSWrapper_recvMsg_mock;
}

void OSMock_destroy()
{
	/* restore functions */
	os = s_savedOs;
}

void OSMock_initTime(int start, int increment)
{
	s_timeStart = start;
	s_timeIncrement = increment;
}


