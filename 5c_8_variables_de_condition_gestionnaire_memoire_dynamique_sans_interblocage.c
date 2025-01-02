#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 1024
#define MONTANT100 100
#define MONTANT25 25
int bytesLeft = MAX_HEAP_SIZE;

pthread_cond_t c;
pthread_mutex_t m;

int * allouer(int size)
{
  pthread_mutex_lock(&m);
  while(bytesLeft < size)
    pthread_cond_wait(&c, &m);
  int * ptr = malloc(sizeof(int));
  bytesLeft -= size;
  printf("Allocation de %d octets, reste %d octets libres\n", size, bytesLeft);
  pthread_mutex_unlock(&m);
  return ptr;
}

void liberer(int * ptr, int size)
{
  pthread_mutex_lock(&m);
  free(ptr);
  bytesLeft += size;
  pthread_cond_broadcast(&c);
  printf("Liberation de %d octets, reste %d octets libres\n", size, bytesLeft);
  pthread_mutex_unlock(&m);
}

void * prendre_et_liberer_100(void * arg)
{
  int * allocation = allouer(MONTANT100);
  liberer(allocation, MONTANT100);
  return allocation;
}

void * prendre_25_et_liberer_100(void * arg)
{
  int * allocation = allouer(MONTANT25);
  liberer(allocation, MONTANT100);
  return allocation;
}

int main(int argc, char *argv[])
{
  pthread_t t1, t2;
  int allocationDegagementInitial;

  if(argc == 2)
    allocationDegagementInitial = atoi(argv[1]);
  else
    allocationDegagementInitial = 0;
  
  allouer(1000);

  pthread_create(&t1, NULL, &prendre_et_liberer_100, NULL);
  sleep(1);
  pthread_create(&t2, NULL, &prendre_25_et_liberer_100, NULL);
  sleep(1);
  
  int * ptr = malloc(sizeof(int));
  liberer(ptr, allocationDegagementInitial);
  
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
