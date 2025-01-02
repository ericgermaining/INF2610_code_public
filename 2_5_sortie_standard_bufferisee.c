#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  printf("message0 ");
  // if (write(3,"xxxx",4)==-1)
  // perror("error");
  if (fork()) {
    printf("message1 ");
    printf("message2\n");
    wait(NULL);
  }
  else {
    printf("message3\n");
  }
  _exit(0);
}
