#include "CppUTest/TestHarness.h"

extern "C"
{
#include "CircularBuffer.h"
}

TEST_GROUP(CircularBuffer)
{
  void setup() {}
  void teardown() {}
};

TEST(CircularBuffer, isEmptyByDefault)
{
  CHECK_TEXT(CircularBuffer_isEmpty(), "Not empty when created");
}
