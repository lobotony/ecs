#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "array.h"
#include "log.h"

typedef struct
{
  Array objectIds;
} ObjectIdPool;

ObjectIdPool* ObjectIdPoolInit(ObjectIdPool* obj)
{
  ArrayInit(&(obj->objectIds), sizeof(u16), 16);
  memset(obj->objectIds.data, 0, obj->objectIds.elementSize*obj->objectIds.numElements);
  return obj;
}


// tries to find/allocate a new ObjectId slot
// returns the number of the free slot found and sets its value to "true"
// "false/zero" slots are considered empty
// if no slot could be found, the pool size is increased

typedef u16 ObjectId;

ObjectId ObjectIdPoolAlloc(ObjectIdPool* obj)
{
  s32 result = -1;
  // try to find a free slot in the current pool
  for(int i=1; i<obj->objectIds.numElements; ++i)
  {
    if(ArrayElement(&(obj->objectIds), ObjectId, i) == 0)
    {
      result = i;
      break;
    }
  }
  
  // if none could be found, increase the pool by a certain amount
  if(result == -1)
  {
    printf("resizing oid pool\n");
    size_t oldNum = obj->objectIds.numElements;
    size_t newNum = obj->objectIds.numElements+16; // hardcoded for now, needs either strategy or be accessible as parameter
    size_t oldSize = oldNum * obj->objectIds.elementSize;
    size_t newSize = newNum * obj->objectIds.elementSize;
    ArrayRealloc(&(obj->objectIds), newNum);
    memset(obj->objectIds.data+oldSize, 0, newSize-oldSize); // zero the newly created space, leaving old values untouched
    result = (s32)oldNum;
  }
  assert(result != -1);
  assert(ArrayElement(&(obj->objectIds), ObjectId, result) == 0);

  printf("found iod at slot %d\n", result);
  ArrayElement(&(obj->objectIds), ObjectId, result) = 1; // mark as "in use"
  
  return (u16)result;
}

typedef struct
{
  u16 objectId;
  // init func
  // ? deinit func
} Component;

int main(int argc, const char * argv[])
{
  //t0();
  ObjectIdPool idpool;
  ObjectIdPoolInit(&idpool);
  
  for(int i=0; i<33; ++i)
  {
    printf("allocated %d\n", ObjectIdPoolAlloc(&idpool));
  }
  
  
  return 0;
}
