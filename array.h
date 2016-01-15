#pragma once

#include <stdlib.h>

typedef struct
{
  void*   data;
  size_t  elementSize;
  size_t  numElements;
} Array;

Array* ArrayInit(Array* array, size_t elementSize, size_t num);
void ArrayDeinit(Array* array);
void ArrayRealloc(Array* array, size_t newNum);

#define ArrayElement(arrayp, type, idx) ((type*)((arrayp)->data))[idx]
