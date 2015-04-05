#include "stdafx.h"
#include "Utils.h"
#include <stdio.h>

#if 0
static int FormatOutput_Impl(const char * format, ...)
{
	/* snip */
	return 0;
}

int(*FormatOutput)(const char * format, ...) = FormatOutput_Impl;

#else

int(*FormatOutput)(const char * format, ...) = printf;
#endif