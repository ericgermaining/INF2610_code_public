#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
  if (fork()==0) { // premier fils
    printf("fils de pid=%d se transforme en ls \n",getpid());
    execl("/bin/ls","ls",NULL);
    _exit(1);
  }
  
  if (fork()==0) { // second fils
    printf("fils de pid=%d se transforme en cat \n",getpid());
    execl("/bin/cat","cat", NULL);
    _exit(1);
  }
  
  int pid;
  while ((pid=wait(NULL)) > 0)
    printf("fin du fils de pid=%d\n", pid);
  
  return 0;
}
