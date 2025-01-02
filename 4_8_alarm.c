#include <unistd.h> /* pour write et _exit */
#include <stdio.h> /* pour printf */
#include <sys/wait.h> /* pour wait */
#define MaxJoueurs 4

void jouer (int i)
{
  while(1); // simule une partie de jeu
}

int main ()
{
  for (int i = 0; i < MaxJoueurs; i++) {
    if (fork () == 0) {
      jouer (i);
    }
  }

  while(wait(NULL)>0);
  
  return 0;
}
