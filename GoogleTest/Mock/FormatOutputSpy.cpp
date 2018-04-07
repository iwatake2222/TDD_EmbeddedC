#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "FormatOutputSpy.h"

/*****************************************
 * Data containers and accessors
 *****************************************/
static char * s_buffer = NULL;
static size_t s_bufferSize   = 0;
static int    s_bufferOffset = 0;
static int    s_bufferUsed   = 0;

void formatOutputSpy_create(int size)
{
	formatOutputSpy_destroy();
	s_bufferSize = size;
	s_buffer = (char*)calloc(s_bufferSize, sizeof(char));
	s_bufferOffset = 0;
	s_bufferUsed = 0;
	s_buffer[0] = '\0';

}

void formatOutputSpy_destroy()
{
	if (s_buffer == NULL) return;

	free(s_buffer);
	s_buffer = NULL;
}

char* formatOutputSpy_getOutput()
{
	return s_buffer;
}


/*****************************************
 * Mock functions
 *****************************************/
int formatOutputSpy(const char* format, ...)
{
	int writtenSize;
	va_list arguments;
	va_start(arguments, format);
	writtenSize = vsnprintf(s_buffer + s_bufferOffset, s_bufferSize - s_bufferUsed, format, arguments);
	s_bufferOffset += writtenSize;
	s_bufferUsed += writtenSize;
	va_end(arguments);
	return 1;
}

