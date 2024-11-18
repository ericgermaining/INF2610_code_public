#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int glob=100;

int main()
{
  if(fork()==0)
    {
      glob=glob-1;
      printf("ici fils pid=%d, glob=%d\n", getpid(), glob);
      _exit(0);
    }
  wait(NULL);
  glob=glob+1;
  printf("ici pere pid=%d, glob=%d\n", getpid(), glob);
  return 0;
}
