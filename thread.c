#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t lock;
void *do_work(void *v) {
  printf("I am running inside a thread\n");
  printf("v is %d\n", *(int *)v);
  for (int i = 0; i < 1000000; i++) {
    pthread_mutex_lock(&lock);
    (*(int *)v)++;
    pthread_mutex_unlock(&lock);
  }
}

int main(int argc, char const *argv[]) {

  pthread_t th1;
  pthread_t th2;
  int *x = malloc(sizeof(int));
  *x = 0;
  int n = pthread_create(&th1, NULL, do_work, (void *)x);
  if (n < 0) {
    perror("create thread failed");
    exit(1);
  }
  x = malloc(sizeof(int));
  *x = 24;
  n = pthread_create(&th2, NULL, do_work, (void *)x);
  if (n < 0) {
    perror("create thread failed");
    exit(1);
  }
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  printf("x is %d\n", *x);
  return 0;
}
