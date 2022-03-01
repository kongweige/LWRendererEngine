#include "controller/engine.h"

#include <stdio.h>

int main()
{
  Engine EGE;
  if (EGE.startUp())
  {
    EGE.run();
  }
  else
  {
    printf("EGE could not initialize successfully. Shutting down.\n");
  }
  EGE.shutDown();
  return 0;
}