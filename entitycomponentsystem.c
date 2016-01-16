#include "entitycomponentsystem.h"
#include <string.h>
#include <assert.h>

EntityComponentSystem* ECSInit(EntityComponentSystem* obj)
{
  memset(obj, 0, sizeof(EntityComponentSystem)); // clear all entries
  ObjectIdPoolInit(&(obj->objectIdPool)); // init object id pool. component pools will be initialized during registration
  return obj;
}

void ECSComponentRegister(EntityComponentSystem* obj,
                          u32 hash,
                          u32 componentSize,
                          ComponentInitFunc initFunc,
                          ComponentDeinitFunc deinitFunc)
{
  s32 index = -1;
  
  for(int i=0; i<ECS_MAXCOMPONENTS; ++i)
  {
    if(obj->componentPoolEntries[i].hash == 0)
    {
      index = i;
      break;
    }
  }
  assert(index != -1);
  ComponentPoolEntry* entry = &(obj->componentPoolEntries[index]);
  entry->hash = hash; // hash != 0 means the entry is taken
  ComponentPoolInit(&(entry->componentPool), componentSize, initFunc, deinitFunc);
}

ComponentPoolEntry* ECSComponentPoolEntryForHash(EntityComponentSystem* obj,
                                                 u32 hash)
{
  s32 index = -1;
  for(int i=0; i<ECS_MAXCOMPONENTS; ++i)
  {
    if(obj->componentPoolEntries[i].hash == hash)
    {
      index = i;
      break;
    }
  }
  assert(index != -1);
  return &(obj->componentPoolEntries[index]);
}

ObjectId ECSObjectAlloc(EntityComponentSystem* obj)
{
  return ObjectIdPoolAlloc(&(obj->objectIdPool));
}

void ECSObjectDealloc(EntityComponentSystem* obj, ObjectId oid)
{
  ObjectIdPoolDealloc(&(obj->objectIdPool), oid);
}

ComponentId ECSComponentAlloc(EntityComponentSystem* obj, ObjectId oid, u32 componentHash)
{
  ComponentPoolEntry* entry = ECSComponentPoolEntryForHash(obj, componentHash);
  return ComponentPoolAlloc(&(entry->componentPool), oid);
}

void ECSComponentDealloc(EntityComponentSystem* obj, u32 componentHash, ComponentId cid)
{
  ComponentPoolEntry* entry = ECSComponentPoolEntryForHash(obj, componentHash);
  ComponentPoolDealloc(&(entry->componentPool), cid);
}

