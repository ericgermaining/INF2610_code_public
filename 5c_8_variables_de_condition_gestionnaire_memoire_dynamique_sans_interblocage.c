#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_HEAP_SIZE 1024
int bytesLeft = MAX_HEAP_SIZE;

pthread_cond_t c;
pthread_mutex_t m;

void * allouer(int size)
{
  pthread_mutex_lock(&m);
  while(bytesLeft < size)
    pthread_cond_wait(&c, &m);
  void * ptr = NULL; // remplacer par un pointeur approprié
  bytesLeft -= size;
  printf("Allocation de %d octets, reste %d octets libres\n", size, bytesLeft);
  pthread_mutex_unlock(&m);
  return ptr;
}

void liberer(void * ptr, int size)
{
  pthread_mutex_lock(&m);
  bytesLeft += size;
  pthread_cond_broadcast(&c);
  printf("Liberation de %d octets, reste %d octets libres\n", size, bytesLeft);
  pthread_mutex_unlock(&m);
}

void * prendre_et_liberer_100(void * arg)
{
  allouer(100);
  sleep(1);
  liberer(NULL, 100);
  return NULL;
}

void * prendre_25_et_liberer_100(void * arg)
{
  allouer(25);
  sleep(1);
  liberer(NULL, 100);
  return NULL;
}

int main()
{
  allouer(1020);

  pthread_t t1, t2;
  pthread_create(&t1, NULL, &prendre_et_liberer_100, NULL);
  sleep(1);
  pthread_create(&t2, NULL, &prendre_25_et_liberer_100, NULL);
  sleep(1);
  liberer(NULL, 50);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
    
