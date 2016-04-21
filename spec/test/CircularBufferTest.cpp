#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
}

TEST_GROUP(CircularBuffer)
{
  CircularBuffer * buffer;

  void setup() {
    buffer = CircularBuffer_Create(3);
  }

  void teardown() {
    CircularBuffer_Destroy(buffer);
  }

  void fillBuffer() {
    CircularBuffer_Put(buffer,1);
    CircularBuffer_Put(buffer,2);
    CircularBuffer_Put(buffer,3);
  }

  void takeElementsOutOfBuffer(int numberOfElements) {
    for (int i = 0; i < numberOfElements; i++)
      CircularBuffer_Get(buffer);
  }
};

TEST(CircularBuffer, whenCreated_isEmpty)
{
  CHECK_TEXT(CircularBuffer_isEmpty(buffer), "Not empty when created");
}

TEST(CircularBuffer, canBeCreatedWithDynamicSize)
{
  CircularBuffer * buffer = CircularBuffer_Create(2);
  CircularBuffer_Put(buffer, 1);
  CircularBuffer_Put(buffer, 2);

  CHECK_TEXT(CircularBuffer_isFull(buffer), "Not empty when created");

  CircularBuffer_Destroy(buffer);
}

TEST(CircularBuffer, whenCreated_isNotFull)
{
  CHECK_FALSE_TEXT(CircularBuffer_isFull(buffer), "Is full on creation");
}

TEST(CircularBuffer, get_retunsInvalidElementWhenEmpty)
{
  CHECK_EQUAL(CircularBuffer_Get(buffer), INVALID_ELEMENT);
}

TEST(CircularBuffer, whenAddingAnElement_isNotEmpty)
{
  CircularBuffer_Put(buffer, 1);
  CHECK_FALSE_TEXT(CircularBuffer_isEmpty(buffer), "Empty after adding an element");
}

TEST(CircularBuffer, get_returnsAddedElement)
{
  CircularBuffer_Put(buffer, 1);
  CHECK_EQUAL(1, CircularBuffer_Get(buffer))
}

TEST(CircularBuffer, isFullWhenAddingElements)
{
  fillBuffer();

  CHECK_TEXT(CircularBuffer_isFull(buffer), "Buffer not full");
}

TEST(CircularBuffer, isNotFullAfterGettingElementFromFullBuffer)
{
  fillBuffer();

  CircularBuffer_Get(buffer);

  CHECK_FALSE_TEXT(CircularBuffer_isFull(buffer), "Buffer is full");
}

TEST(CircularBuffer, getsElementsIn_FIFO_Order)
{
  fillBuffer();

  CHECK_EQUAL(1, CircularBuffer_Get(buffer));
  CHECK_EQUAL(2, CircularBuffer_Get(buffer));
  CHECK_EQUAL(3, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, doesNotWriteOutOfBounds)
{
  fillBuffer();
  CircularBuffer_Put(buffer,4);
  takeElementsOutOfBuffer(3);

  CHECK_EQUAL(INVALID_ELEMENT, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, doesNotReadOutOfBounds)
{
  fillBuffer();
  takeElementsOutOfBuffer(3);

  CHECK_EQUAL(INVALID_ELEMENT, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, Put_addsElementsAsSlotsAreEmptied)
{
  fillBuffer();
  takeElementsOutOfBuffer(3);
  CircularBuffer_Put(buffer, 5);

  CHECK_EQUAL(5, CircularBuffer_Get(buffer));
}
