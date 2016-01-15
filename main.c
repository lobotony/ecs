#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "array.h"
#include "log.h"
#include "objectidpool.h"
#include "test.h"

typedef struct
{
  ObjectId objectId;
  // init func
  // ? deinit func
} Component;

int main(int argc, const char * argv[])
{
  oidtest();
  
  return 0;
}
