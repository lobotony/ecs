#pragma once

#include "array.h"

typedef u16 ObjectId;

typedef struct
{
  Array objectIds;
} ObjectIdPool;

ObjectIdPool* ObjectIdPoolInit(ObjectIdPool* obj);

// tries to find/allocate a new ObjectId slot
// returns the number of the free slot found and sets its value to "true"
// "false/zero" slots are considered empty
// if no slot could be found, the pool size is increased
// will NEVER return 0 as this is used to denote "no object"
ObjectId ObjectIdPoolAlloc(ObjectIdPool* obj);

void ObjectIdPoolDealloc(ObjectIdPool* obj, ObjectId oid);
