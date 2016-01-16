#include <assert.h>

#include "test.h"
#include "array.h"
#include "objectidpool.h"
#include "componentpool.h"
#include "log.h"
#include "string.h"

void testArray0(void)
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

void testObjectIdPool(void)
{
  ObjectIdPool idpool;
  ObjectIdPoolInit(&idpool);
  
  for(int i=0; i<33; ++i)
  {
    ObjectIdPoolAlloc(&idpool);
  }
  
  ObjectIdPoolDealloc(&idpool, 13);
  assert(ObjectIdPoolAlloc(&idpool) == 13);
}

void testArray1(void)
{
  size_t arraySize = 13;
  Array s8array;
  ArrayInit(&s8array, sizeof(s8), arraySize);
  
  for(int i=0; i<arraySize; ++i)
  {
    ArrayElement(&s8array, s8, i) = i;
  
    void* p0 = &(((s8*)((&s8array)->data))[i]);
    void* p1 = ArrayElementPointer(&s8array, i);
    assert(p0 == p1);
    
    assert(*((s8*)p0) == *((s8*)p1));
  }
  
  Array u64array;
  ArrayInit(&u64array, sizeof(u64), arraySize);

  for(int i=0; i<arraySize; ++i)
  {
    ArrayElement(&u64array, u64, i) = i;

    void* p0 = &(((u64*)((&u64array)->data))[i]);
    void* p1 = ArrayElementPointer(&u64array, i);
    assert(p0 == p1);

    assert(*((u64*)p0) == *((u64*)p1));
  }

}


// ----------------------------

// payload for test transform component
typedef struct
{
  f32 data[16];
} Mat44;

// test component: holds the transform of an object
typedef struct
{
  Component base;
  Mat44     transform;
} TransformComponent;

void TransformComponentInit(void* o)
{
  LOG("TransformComponentInit");
  TransformComponent* obj = (TransformComponent*)o;
  memset(&(obj->transform), 0, sizeof(Mat44));
}

void TransformComponentDeinit(void* o)
{
  LOG("TransformComponentDeinit");
}

void testComponentPool(void)
{
  ComponentPool transformComponentPool;
  ComponentPoolInit(&transformComponentPool, sizeof(TransformComponent), TransformComponentInit, TransformComponentDeinit);
 
  ObjectId oid = 13;
  ComponentId c1 = ComponentPoolAlloc(&transformComponentPool, oid);
  ComponentId c2 = ComponentPoolAlloc(&transformComponentPool, oid);
 
  assert(c1 == 0);
  assert(c2 == 1);
  assert(transformComponentPool.components.numElements > 2);
  
  ComponentPoolDealloc(&transformComponentPool, c2);
  c2 = ComponentPoolAlloc(&transformComponentPool, oid);
  assert(c2 == 1);
}
