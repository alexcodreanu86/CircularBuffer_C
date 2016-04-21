#include "CircularBuffer.h"

typedef struct CircularBuffer Buffer;
struct CircularBuffer
{
  int containerSize;
  int * container;
  int getIndex;
  int putIndex;
};

int * emptyContainer(int);
int * emptyContainer(int numberOfElements)
{
  int * container = calloc((size_t) numberOfElements, sizeof (int));
  for(int i = 0; i < numberOfElements; i++)
  {
    container[i] = INVALID_ELEMENT;
  }

  return container;
}

Buffer * CircularBuffer_Create() {
  Buffer * self = (Buffer *) calloc(1, sizeof (Buffer));
  self->container = emptyContainer(3);
  self->containerSize = 3;
  self->getIndex = 0;
  self->putIndex = 0;
  return self;
}

void CircularBuffer_Destroy(Buffer * self) {
  free(self->container);
  free(self);
}

bool CircularBuffer_isEmpty(Buffer * self)
{
  return self->putIndex == self->getIndex;
}

bool CircularBuffer_isFull(Buffer * self)
{
  return ((self->putIndex - self->getIndex) == self->containerSize) ||
    (self->putIndex == self->getIndex && self->getIndex != 0);
}

void CircularBuffer_Put(Buffer * self, int element)
{
  if (self->putIndex >= self->containerSize)
    self->getIndex = 0;

  if (self->container[self->putIndex] == INVALID_ELEMENT)
    self->container[self->putIndex++] = element;
}

int CircularBuffer_Get(Buffer * self)
{
  int element;
  if (self->getIndex >= self->containerSize) {
    self->getIndex = 0;
    element = self->container[self->getIndex];
  }
  element = self->container[self->getIndex];
  if (element != INVALID_ELEMENT) {
    self->container[self->getIndex] = INVALID_ELEMENT;
    self->getIndex++;
  }

  return element;
}
