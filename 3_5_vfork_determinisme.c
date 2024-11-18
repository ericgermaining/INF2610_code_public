#include <stdio.h>
#include <unistd.h>

long a=0;

void* increment(void *x)
{
  for(int i=0; i<1000000; i++)
    a=a+ (long) x;
  return NULL;
}

int main ()
{
  for(int i=0; i <3; i++)
    
    if (vfork() ==0) //Fi
      {
        increment( (void *)1);
        _exit(0);
      }
  
  printf(" a = %ld\n", a);
  
  return 0;
}
