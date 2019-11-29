#include <stdio.h> // perror, printf
#include <stdlib.h> // exit, atoi
#include <unistd.h> // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h> // memset

#define BUF_SIZE 1024

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
    int n = fork();
    if (n < 0) {
      perror("fork failed");
      continue;
    }
    else if (n > 0) {
      memset(buf, 0, BUF_SIZE);
      if(read(clientFd, buf, BUF_SIZE) < 0) {
        perror("read() failed");
        close(clientFd);
        exit(1);
      }
      printf("From client %s\n", buf);
      char send_buffer[BUF_SIZE];
      sprintf(send_buffer, "client sent %s", buf);
      if (write(clientFd, send_buffer, strlen(send_buffer)) < 0) {
        perror("write() failed");
        close(clientFd);
        exit(1);
      }
      close(clientFd);
    }
  }

  return 0;
}
