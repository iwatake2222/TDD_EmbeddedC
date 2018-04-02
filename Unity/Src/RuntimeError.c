#include <stdio.h>
#include "RuntimeError.h"

void RuntimeError(const char * message, int parameter, const char * file, int line)
{
	printf("[%s:%d] %s (%d)\n", file, line, message, parameter);
}

