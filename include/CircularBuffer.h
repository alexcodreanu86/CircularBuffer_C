#include <stdbool.h>

struct CircularBuffer;

enum { INVALID_ELEMENT = -1 };

struct CircularBuffer * CircularBuffer_Create(int);
void CircularBuffer_Destroy(struct CircularBuffer *);

bool CircularBuffer_isEmpty(struct CircularBuffer *);
bool CircularBuffer_isFull(struct CircularBuffer *);

void CircularBuffer_Put(struct CircularBuffer *, int);
int CircularBuffer_Get(struct CircularBuffer *);
