#include "componentpool.h"
#include "array.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

ComponentPool* ComponentPoolInit(ComponentPool* obj,
                                 size_t componentSize,
                                 ComponentInitFunc initfunc,
                                 ComponentDeinitFunc deinitfunc)
{
  int minSize = 1;
  ArrayInit(&(obj->components), componentSize, minSize);
  obj->initFunc = initfunc;
  obj->deinitFunc = deinitfunc;
  
  // unused components have their objectId set to zero
  // so initialize all objectIds of the components in this pool to 0
  // FIXME: memset 0 for now
  ArrayZero(&(obj->components));
  return obj;
}

// tries to find an unused component slot and returns its id
// the objectId of the component is set to the provided ObjectId
// in order to denote the object it belongs to
// componentIds range from 0 to n-1. Only objectIds start at 1, with 0 meaning "no object".
ComponentId ComponentPoolAlloc(ComponentPool* obj, ObjectId oid)
{
  s32 result = -1;
  for(int i=0; i<obj->components.numElements; ++i)
  {
    Component* component = (Component*)(ArrayElementPointer(&(obj->components), i));
    if(component->objectId == 0)
    {
      result = i;
      break;
    }
  }
  
  // if no component could be found, grow the array
  if(result == -1)
  {
    size_t oldNum = obj->components.numElements;
    size_t newNum = oldNum + 3;
    printf("resizing componentpool to %zu\n", newNum);
    size_t oldSize = obj->components.elementSize * oldNum;
    size_t newSize = obj->components.elementSize * newNum;
    ArrayRealloc(&(obj->components), newNum); // FIXME: growing needs strategy or value that can be specified
    memset(obj->components.data+oldSize, 0, newSize-oldSize); // zero the newly created space, leaving old values untouched
    result = (s32)oldNum;
  }
  
  assert(result > -1);

  printf("found component %d\n", result);
  // setup new component
  Component* component = ArrayElementPointer(&(obj->components), result);
  component->objectId = oid; // mark it as owned by object with given id
  if(obj->initFunc != NULL) // call optional init
  {
    obj->initFunc(component);
  }
  
  return (ComponentId)result;
}

void ComponentPoolDealloc(ComponentPool* obj, ComponentId cid)
{
  Component* component = (Component*)ArrayElementPointer(&(obj->components), cid);
  if(obj->deinitFunc)
  {
    obj->deinitFunc(component);
  }
  component->objectId = 0;
  printf("deallocated component %d\n", cid);
}
