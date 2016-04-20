#include "CircularBuffer.h"

typedef struct CircularBuffer Buffer;
struct CircularBuffer
{
  int addedElement;
};

Buffer * CircularBuffer_Create() {
  Buffer * self = (Buffer *) calloc(1, sizeof (Buffer));
  self->addedElement = INVALID_ELEMENT;
  return self;
}

void CircularBuffer_Destroy(Buffer * self) {
  free(self);
}

bool CircularBuffer_isEmpty(Buffer * self)
{
  return self->addedElement == INVALID_ELEMENT;
}

bool CircularBuffer_isFull()
{
  return false;
}

void CircularBuffer_Put(Buffer * self, int element)
{
  self->addedElement = element;
}

int CircularBuffer_Get(Buffer * self)
{
  return self->addedElement;
}
