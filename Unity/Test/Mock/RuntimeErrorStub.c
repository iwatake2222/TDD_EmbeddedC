#include "RuntimeErrorStub.h"
#include "RuntimeError.h"

static const char * s_message = "No Error";
static int s_parameter = -1;
static const char * s_file = 0;
static int s_line = -1;

void RuntimeErrorStub_reset(void)
{
	s_message = "No Error";
	s_parameter = -1;
}

const char * RuntimeErrorStub_getLastError(void)
{
	return s_message;
}

void RuntimeError(const char * message, int parameter, const char * file, int line)
{
	s_message = message;
	s_parameter = parameter;
	s_file = file;
	s_line = line;
}

int RuntimeErrorStub_GetLastParameter(void)
{
	return s_parameter;
}