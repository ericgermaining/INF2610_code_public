#include <unistd.h> // pour fork, execl, _exit
#include <stdio.h> // pour printf
#include <sys/wait.h> // pour wait
#include <fcntl.h> // pour open
#include <sys/types.h> // pour mkfifo
#include <sys/stat.h> // pour mkfifo

int main( ) {
  
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
