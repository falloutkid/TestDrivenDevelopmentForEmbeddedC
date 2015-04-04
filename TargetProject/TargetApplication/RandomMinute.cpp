#include "stdafx.h"
#include "RandomMinute.h"
#include <stdlib.h>
#include <memory.h>

static int bound = 0;

void RandomMinute_Create(int b)
{
	bound = b;
	srand(10);
}

int RandomMinute_GetImpl(void)
{
	return bound - rand() % (bound * 2 + 1);
}

// int(*RandomMinute_Get)(void) = RandomMinute_GetImpl;

#if 1
int RandomMinute_Get(void)
{
	return bound - rand() % (bound * 2 + 1);
}
#endif 