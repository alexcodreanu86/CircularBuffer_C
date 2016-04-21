#include "CircularBuffer.h"

typedef struct CircularBuffer Buffer;
struct CircularBuffer
{
  int containerSize;
  int * container;
  int getIndex;
  int putIndex;
  bool isEmpty;
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

Buffer * CircularBuffer_Create(int containerSize) {
  Buffer * self = (Buffer *) calloc(1, sizeof (Buffer));
  self->container = emptyContainer(containerSize);
  self->containerSize = containerSize;
  self->getIndex = 0;
  self->putIndex = 0;
  self->isEmpty = true;
  return self;
}

void CircularBuffer_Destroy(Buffer * self) {
  free(self->container);
  free(self);
}

bool CircularBuffer_isEmpty(Buffer * self)
{
  return self->isEmpty;
}

bool CircularBuffer_isFull(Buffer * self)
{
  return !self->isEmpty && self->putIndex == self->getIndex;
}

int nextIndex(int currentIndex, int containerSize);
int nextIndex(int currentIndex, int containerSize)
{
  return currentIndex + 1 == containerSize ? 0 : currentIndex + 1;
}

void CircularBuffer_Put(Buffer * self, int element)
{
  if (CircularBuffer_isFull(self))
    return;

  self->isEmpty = false;
  self->container[self->putIndex] = element;
  self->putIndex = nextIndex(self->putIndex, self->containerSize);
}

int CircularBuffer_Get(Buffer * self)
{
  if (CircularBuffer_isEmpty(self))
    return INVALID_ELEMENT;

  int element = self->container[self->getIndex];
  self->getIndex = nextIndex(self->getIndex, self->containerSize);

  if (self->getIndex == self->putIndex)
    self->isEmpty = true;

  return element;
}
