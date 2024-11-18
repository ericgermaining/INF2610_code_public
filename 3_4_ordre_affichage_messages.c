#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  printf("message0\n");
  
  if (vfork()) {
    printf("message1\n");
    if (vfork()) {
      printf("message2\n");
    }
    else { _exit(0); }
  }
  else { printf("message3\n"); }
  
  while(wait(NULL)>0);
  
  _exit(0);
}
