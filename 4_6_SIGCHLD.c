#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
  if (fork()==0) { // fils
    printf(" Fils : je vais dormir pendant 2s\n");
    sleep(2);
    printf(" Fils : je vais terminer mon exécution.\n");
    _exit(0);
  }

  // Pere
  printf(" Père : je vais rentrer dans une boucle infinie\n");

  while(1); // attente active

  return 0;
}
