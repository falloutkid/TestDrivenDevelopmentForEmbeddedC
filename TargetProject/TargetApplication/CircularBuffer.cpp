#include "stdafx.h"
#include "CircularBuffer.h"
#include "Utils.h"
#include <stdlib.h>
#include <string.h>

typedef struct CircularBufferStruct
{
	int count;
	int index;
	int outdex;
	int capacity;
	int * values;
} CircularBufferStruct;

const int BUFFER_GUARD = -999;

CircularBuffer CircularBuffer_Create(int capacity)
{
	CircularBuffer self = (CircularBuffer)calloc(capacity, sizeof(CircularBufferStruct));
	self->capacity = capacity;
	self->values = (int*)calloc(capacity + 1, sizeof(int));
	self->values[capacity] = BUFFER_GUARD;
	return self;
}

void CircularBuffer_Destroy(CircularBuffer self)
{
	free(self->values);
	free(self);
}

void CircularBuffer_Print(CircularBuffer self)
{
	int i;
	int currentValue;

	currentValue = self->outdex;

	FormatOutput("Circular buffer content:\n<");

	for (i = 0; i < self->count; i++) {
		if (i != 0)
			FormatOutput(", ");
		FormatOutput("%d", self->values[currentValue++]);
		if (currentValue >= self->capacity)
			currentValue = 0;
	}

	FormatOutput(">\n");
}
