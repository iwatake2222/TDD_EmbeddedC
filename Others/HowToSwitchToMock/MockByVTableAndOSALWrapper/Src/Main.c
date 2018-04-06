#include <stdio.h>
#include <stdint.h>
#include "OSWrapper.h"


int main()
{
	extern void test();
	test();
	
	printf("This is product code.\n");
	printf("getMicroTime = %d\n", os.getTime());
}