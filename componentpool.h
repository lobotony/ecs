#pragma once

#include "array.h"

typedef struct
{
  ObjectId objectId;
} Component;

typedef void(*ComponentInitFunc)(void*);
typedef void(*ComponentDeinitFunc)(void*);


typedef struct
{
  Array               components; // implicitly contains component size
  ComponentInitFunc   initFunc;
  ComponentDeinitFunc deinitFunc;
} ComponentPool;

ComponentPool* ComponentPoolInit(ComponentPool* obj,
                                 size_t componentSize,
                                 ComponentInitFunc initfunc,
                                 ComponentDeinitFunc deinitfunc);

// tries to find an unused component slot and returns its id
// the objectId of the component is set to the provided ObjectId
// in order to denote the object it belongs to
// componentIds range from 0 to n-1. Only objectIds start at 1, with 0 meaning "no object".
ComponentId ComponentPoolAlloc(ComponentPool* obj, ObjectId oid);
void ComponentPoolDealloc(ComponentPool* obj, ComponentId cid);
