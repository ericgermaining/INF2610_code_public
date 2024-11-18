#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  if(fork()==0)
    {
      printf("ici fils pid=%d de pere=%d\n", getpid(), getppid());
      _exit(0);
    }
  
  if(fork()==0)
    {
      printf("ici fils pid=%d de pere=%d\n", getpid(), getppid());
      _exit(0);
    }
  
  while(wait(NULL)>0);
  
  printf("ici pere pid=%d, fin de tous mes fils\n", getpid());
  return 0;
}
