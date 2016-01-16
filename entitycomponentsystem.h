#pragma once

#include "types.h"
#include "objectidpool.h"
#include "componentpool.h"
#include "stringhash.h"

#define ECS_MAXCOMPONENTS 16

// componentHash is simply a unique id per component type
// you can eitehr choose these yourself or use the stringhash function
// to derive one from your component type name
// hash must never be 0 since that is used to denote an empty ComponentPoolEntry
typedef struct
{
  u32 hash;
  ComponentPool componentPool;
} ComponentPoolEntry;

typedef struct
{
  ObjectIdPool objectIdPool;
  ComponentPoolEntry componentPoolEntries[ECS_MAXCOMPONENTS];
} EntityComponentSystem;

#define ComponentHash(type) stringhash(#type)

EntityComponentSystem* ECSInit(EntityComponentSystem* obj);
void ECSComponentRegister(EntityComponentSystem* obj,
                          u32 hash,
                          u32 componentSize,
                          ComponentInitFunc initFunc,
                          ComponentDeinitFunc deinitFunc);
ComponentPoolEntry* ECSComponentPoolEntryForHash(EntityComponentSystem* obj,
                                                 u32 hash);
ObjectId    ECSObjectAlloc      (EntityComponentSystem* obj);
void        ECSObjectDealloc    (EntityComponentSystem* obj, ObjectId oid);
ComponentId ECSComponentAlloc   (EntityComponentSystem* obj, ObjectId oid, u32 componentHash);
void        ECSComponentDealloc (EntityComponentSystem* obj, u32 componentHash, ComponentId cid);