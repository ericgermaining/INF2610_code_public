#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define MAX 5
#define ITERATIONS 4
#define NB_THREADS 1

int tampon[MAX];
int ip = 0;
int ic = 0;
int compteur = 0;

pthread_cond_t nplein, nvide;
pthread_mutex_t mutex;

void produire(int val)
{
  tampon[ip] = val;
  ip = (ip + 1) % MAX;
  compteur++;
}

int consommer()
{
  int tmp = tampon[ic];
  ic = (ic + 1) % MAX;
  compteur--;
  return tmp;
}

void * producteur(void * arg)
{
  pthread_mutex_lock(&mutex);
  int i;
  for(i = 0; i < ITERATIONS; i++) {
    while(compteur == MAX)
      pthread_cond_wait(&nplein, &mutex);
    produire(i + *((int *)arg));
    pthread_cond_signal(&nvide);
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void * consommateur(void * arg)
{
  pthread_mutex_lock(&mutex);
  int i;
  for(i = 0; i < ITERATIONS; i++) {
    while(compteur == 0)
      pthread_cond_wait(&nvide, &mutex);
    int tmp = consommer();
    pthread_cond_signal(&nplein);
    printf("%d\n", tmp);
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main()
{
  pthread_cond_init(&nplein, NULL);
  pthread_cond_init(&nvide, NULL);
  pthread_mutex_init(&mutex, NULL);
  pthread_t p[NB_THREADS], c[NB_THREADS];
  int tab100[3] = {0, 100, 200};
  for(int i=0; i<NB_THREADS; i++)
    pthread_create(&p[i], NULL, &producteur, (void *)(tab100 + i));
  for(int i=0; i<NB_THREADS; i++)
    pthread_create(&c[i], NULL, &consommateur, NULL);
  for(int i=0; i<NB_THREADS; i++)
    pthread_join(p[i], NULL);
  for(int i=0; i<NB_THREADS; i++)
    pthread_join(c[i], NULL);
}

