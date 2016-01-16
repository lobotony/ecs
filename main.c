#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "array.h"
#include "log.h"
#include "objectidpool.h"
#include "test.h"
#include "componentpool.h"


int main(int argc, const char * argv[])
{
  testArray0();
  testArray1();
  testObjectIdPool();
  testComponentPool();
  return 0;
}
