#include "stringhash.h"

u32 stringhash(const char* data)
{
  u32 hash = 5381;
  s32 c;

  const unsigned char* str = (const unsigned char*)data;
  while ((c = *str++))
  {
      hash = ((hash << 5) + hash) + (u32)c;
  }

  return hash;  
}
