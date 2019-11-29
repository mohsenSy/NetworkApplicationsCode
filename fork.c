#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

  int n = fork();
  int x = 0;
  if (n < 0) {
    perror("fork failed");
    exit(1);
  }
  else if (n == 0) {
    printf("Parent process\n");
    printf("x is %d, address of x is %p\n", x, &x);
  }
  else {
    printf("Child process\n");
    x = 9;
    printf("x is %d, address of x is %p\n", x, &x);
  }

  return 0;
}
