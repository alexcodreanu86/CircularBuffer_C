#include "CircularBuffer.h"

typedef struct CircularBuffer Buffer;
struct CircularBuffer
{
  int containerSize;
  int * container;
  int getIndex;
  int putIndex;
  bool isFull;
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

Buffer * CircularBuffer_Create() {
  Buffer * self = (Buffer *) calloc(1, sizeof (Buffer));
  self->container = emptyContainer(3);
  self->containerSize = 3;
  self->getIndex = 0;
  self->putIndex = 0;
  self->isFull = false;
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
  return self->isFull;
}

int nextIndex(int currentIndex, int containerSize);
int nextIndex(int currentIndex, int containerSize)
{
  return currentIndex + 1 == containerSize ? 0 : currentIndex + 1;
}

void CircularBuffer_Put(Buffer * self, int element)
{
  if (!CircularBuffer_isFull(self)) {
    self->isEmpty = false;
    self->container[self->putIndex] = element;
    self->putIndex = nextIndex(self->putIndex, self->containerSize);

    if (self->getIndex == self->putIndex)
      self->isFull = true;
  }
}

int CircularBuffer_Get(Buffer * self)
{
  int element;
  if (CircularBuffer_isEmpty(self)) {
    element = INVALID_ELEMENT;
  } else {
    self->isFull = false;
    element = self->container[self->getIndex];
    self->getIndex = nextIndex(self->getIndex, self->containerSize);

    if (self->getIndex == self->putIndex)
      self->isEmpty = true;
  }

  return element;
}
