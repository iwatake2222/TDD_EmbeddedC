#include <stdio.h>
#include <stdarg.h>
#include <Util/Utils.h>

// int formatOutput(const char* format, ...)
// {
// 	va_list list;
// 	va_start(list, format);
// 	vprintf(format, list);
// 	va_end(list);
// }

static int formatOutput_impl(const char* format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	vprintf(format, arguments);
	va_end(arguments);
}

int (*formatOutput)(const char* format, ...) = formatOutput_impl;
