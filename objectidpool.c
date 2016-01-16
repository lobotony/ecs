#include "objectidpool.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef uint64_t ObjectIdStorageType;

ObjectIdPool* ObjectIdPoolInit(ObjectIdPool* obj)
{
  ArrayInit(&(obj->objectIds), sizeof(ObjectIdStorageType), 16);
  memset(obj->objectIds.data, 0, obj->objectIds.elementSize*obj->objectIds.numElements);
  return obj;
}

ObjectId ObjectIdPoolAlloc(ObjectIdPool* obj)
{
  s32 result = -1;
  // try to find a free slot in the current pool
  for(int i=1; i<obj->objectIds.numElements; ++i)
  {
    if(ArrayElement(&(obj->objectIds), ObjectIdStorageType, i) == 0)
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
  assert(ArrayElement(&(obj->objectIds), ObjectIdStorageType, result) == 0);

  printf("found oid at slot %d\n", result);
  ArrayElement(&(obj->objectIds), ObjectIdStorageType, result) = 1; // mark as "in use"
  
  return (ObjectId)result;
}

void ObjectIdPoolDealloc(ObjectIdPool* obj, ObjectId oid)
{
  assert((oid > 0) && (oid < obj->objectIds.numElements));
  ArrayElement(&(obj->objectIds), ObjectIdStorageType, oid) = 0;
}
