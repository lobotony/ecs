#include "test.h"
#include "array.h"

void t0(void)
{
  Array objectIds;
  size_t sz0 = 256;
  ArrayInit(&objectIds, sizeof(s8), sz0);
  
  for(int i=0; i<sz0; ++i)
  {
    ArrayElement(&objectIds, s8, i) = 127;
  }

  size_t sz1 = 2* sz0;
  ArrayRealloc(&objectIds, sz1);

  for(int i=0; i<sz1; ++i)
  {
    ArrayElement(&objectIds, s8, i) = 127;
  }
}
