#include <stdio.h>
#include <pthread.h>

void *func(void *x)
{
  printf("Thread %d de tid=%lu \n", * ((int *)x), pthread_self());
  return NULL;
}

int main ()
{
  pthread_t tid[3];
  
  for(int i=0; i <3; i++) {
    pthread_create(&tid[i], NULL, func, (void*) &i);
  }
  
  for(int i=0; i <3; i++) {
    pthread_join(tid[i],NULL);
  }
  
  return 0;
}
