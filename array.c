#include "array.h"
#include <string.h>

Array* ArrayInit(Array* array, size_t elementSize, size_t num)
{
  array->elementSize = elementSize;
  array->numElements = num;
  array->data = malloc(elementSize*num);

  return array;
}

void ArrayDeinit(Array* array)
{
  free(array->data);
}

void ArrayRealloc(Array* array, size_t newNum)
{
  array->data = realloc(array->data, array->elementSize*newNum);
  array->numElements = newNum;
}

void ArrayZero(Array* array)
{
  memset(array->data, 0, array->elementSize*array->numElements);
}
