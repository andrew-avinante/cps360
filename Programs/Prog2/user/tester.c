// Do not modify this file. It will be replaced by the grading scripts
// when checking your project.

#include "types.h"
#include "stat.h"
#include "user.h"

void loop()
{
    int count = 0;
    for(;;)
  {
    count++;
  }
  exit();
}

int
main(int argc, char *argv[])
{
  printf(1, "%s", "** Placeholder program for grading scripts **\n");
    settickets(10);
  if(fork() == 0)
  {
    settickets(20);
    loop();
  }
   if(fork() == 0)
  {
    settickets(30);
       loop();
  }
     loop();
}
