#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
  if(fork()==0) {
    printf("Fils : je vais rentrer dans une pause \n");
    pause();
    printf("Fils : je suis sorti de ma pause \n");
    return 0;
  }
  sleep(2);
  wait(NULL);

  return 0;
}
