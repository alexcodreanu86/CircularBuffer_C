#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
}

TEST_GROUP(CircularBuffer)
{
  CircularBuffer * buffer;

  void setup() {
    buffer = CircularBuffer_Create();
  }

  void teardown() {
    CircularBuffer_Destroy(buffer);
  }
};

TEST(CircularBuffer, whenCreated_isEmpty)
{
  CHECK_TEXT(CircularBuffer_isEmpty(buffer), "Not empty when created");
}

TEST(CircularBuffer, whenCreated_isNotFull)
{
  CHECK_FALSE_TEXT(CircularBuffer_isFull(), "Is full on creation");
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
