#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define N 3
/*0*/ // déclarer les sémaphores, etc.

void Trajet_au_cinema(long i)
{
  printf(" Ami %lu arrive au cinéma \n", i);
}

void Acces_au_cinema(long i)
{
  printf(" Ami %lu rentre au cinéma \n", i);
}

void* ami (void * x)
{
  long i=(long)x;
  Trajet_au_cinema(i);
  /* 1*/ // attendre tous les amis
  Acces_au_cinema(i);
}

int main() {
  pthread_t tid[N];
  long i;
  /* 2 */ // initialiser des sémaphores
  // création des threads ami
  for(i=0; i<N; i++) pthread_create(&tid[i], NULL, ami, (void *)i);
  // attente de la fin des threads
  for(i=0; i<N; i++) pthread_join(tid[i], NULL);
  return 0;
}
