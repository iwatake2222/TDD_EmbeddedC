#include <stdio.h>
#include <stdint.h>
#include "OSMock.h"


void test()
{
	printf("This is test code.\n");

	/* starting test */
	OSMock_create();
	OSMock_initTime(500, 2);

	/* test */
	printf("getMicroTime = %d\n", os.getTime());
	int msg = 5;
	os.sendMsg(10, &msg);
	os.recvMsg(12, &msg);
	printf("msg = %08X\n", msg);
	printf("getMicroTime = %d\n", os.getTime());

	/* exiting test */
	OSMock_destroy();

	printf("End of test.\n\n");
}


