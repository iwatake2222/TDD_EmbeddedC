#include <stdlib.h>
#include <Util/CircularBuffer.h>
#include <Util/Utils.h>

struct CircularBuffer_t{
	int* p;
	int size;
	int inIndex;
	int outIndex;
	int contentCnt;
};

CircularBuffer CircularBuffer_create(int size)
{
	CircularBuffer buffer = (CircularBuffer) calloc(1, sizeof(struct CircularBuffer_t));
	buffer->p = (int*) calloc(size, sizeof(int));
	buffer->size = size;
	buffer->inIndex = 0;
	buffer->outIndex = 0;
	buffer->contentCnt = 0;
	return buffer;
}

void CircularBuffer_destroy(CircularBuffer buffer)
{
	if (buffer != NULL){
		if (buffer->p != NULL){
			free(buffer->p);
		}
		free(buffer);
	}
}

void CircularBuffer_print(CircularBuffer buffer)
{
	formatOutput("Circular buffer content:\n");
	formatOutput("<");
	if (buffer->inIndex > buffer->outIndex) {
		for(int i = 0; i < buffer->contentCnt; i++) {
			if (i != 0)formatOutput(", ");
			formatOutput("%d", buffer->p[buffer->outIndex + i]);
		}
	} else {
		for(int i = 0; i < buffer->contentCnt; i++) {
			if (i != 0)formatOutput(", ");
			formatOutput("%d", buffer->p[(buffer->outIndex + i)%buffer->size]);
		}
	}
	formatOutput(">\n");
}

void CircularBuffer_put(CircularBuffer buffer, int value)
{
	buffer->contentCnt++;
	buffer->p[buffer->inIndex] = value;
	buffer->inIndex = (buffer->inIndex + 1) % buffer->size;
}

int CircularBuffer_get(CircularBuffer buffer)
{
	buffer->contentCnt--;
	int ret = buffer->p[buffer->outIndex];
	buffer->outIndex = (buffer->outIndex + 1) % buffer->size;
	return ret;
}
