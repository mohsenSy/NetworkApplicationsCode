#include <stdio.h> // perror, printf
#include <stdlib.h> // exit, atoi
#include <unistd.h> // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h> // memset
#include <pthread.h>

#define BUF_SIZE 1024

void *handle_client(void *v) {
  int clientFd = *((int *)v);
  char buf[BUF_SIZE];
  memset(buf, 0, BUF_SIZE);
  if(read(clientFd, buf, BUF_SIZE) < 0) {
    perror("read() failed");
    close(clientFd);
  }
  printf("From client %s\n", buf);
  strcpy(buf, "hello client");
  if (write(clientFd, buf, strlen("hello client")) < 0) {
    perror("write() failed");
    close(clientFd);
  }
}

int main(int argc, char const *argv[]) {

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  int serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFd < 0) {
    perror("socket() failed");
    exit(2);
  }
  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(argv[1]));
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(serverFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("bind() failed");
    exit(9);
  }
  if (listen(serverFd, 10) < 0) {
    perror("listen() failed");
    exit(3);
  }
  struct sockaddr_in clientAddr;
  int addrLen = sizeof(clientAddr);
  char buf[BUF_SIZE];
  while(1) {
    int clientFd = accept(serverFd, (struct sockaddr *)&clientAddr, &addrLen);
    if (clientFd < 0) {
      perror("accept() failed");
      continue;
    }
    int *fd = malloc(4);
    *fd = clientFd;
    pthread_t *th = malloc(sizeof(pthread_t));
    pthread_create(th, NULL, handle_client, (void *)fd);
  }

  return 0;
}
