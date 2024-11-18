#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define N 3

void * f (void *x)
{
  long c=0, i= (long)x;
  while(1) { // un cycle de Ti
    printf("Cycle %lu de T%lu \n", c, i);
    c=c+1;
  }
  return NULL;
}

int main()
{
  pthread_t T[N];
  for(long i=0; i<N;i++)
    pthread_create (&T[i],NULL,f,(void *)i);
  sleep(1);
  for(i=0; i<N;i++) pthread_cancel (T[i]);
  for(i=0; i<N;i++) pthread_join (T[i],NULL);
  return 0;
}
