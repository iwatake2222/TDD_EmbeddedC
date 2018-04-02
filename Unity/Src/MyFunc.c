#include "MyFunc.h"

int MyFunc_2X(int a)
{
	// return 0;
	return a * 2;
}

int MyFunc_memset(char* buf, char ch, int n)
{
	// return 0;
	int i = 0;
	for ( i = 0; i < n; i++ ) {
		*buf++ = ch;
	}
	*buf = '\0';
	return i;
}
