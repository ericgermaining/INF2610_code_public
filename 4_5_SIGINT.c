#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
  printf(" Je me mets en pause. Réveillez-moi en tapant CTRL+C.\n");
  pause();
  printf(" fin de ma pause \n");
  return 0;
}
