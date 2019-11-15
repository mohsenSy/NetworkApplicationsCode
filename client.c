#include <stdio.h> // perror, printf
#include <stdlib.h> // exit, atoi
#include <unistd.h> // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h> // memset

#define BUF_SIZE 1024

int main(int argc, char const *argv[]) {

  if (argc != 3) {
    printf("Usage: %s <ip> <port>\n", argv[0]);
    exit(1);
  }

  int clientFd = socket(AF_INET, SOCK_STREAM, 0);
  if (clientFd < 0) {
    perror("socket() failed");
    exit(2);
  }

  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(argv[2]));
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  if (connect(clientFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("connect() failed");
    exit(1);
  }
  char buf[BUF_SIZE];
  fgets(buf, BUF_SIZE, stdin);
  buf[strlen(buf)-1] = 0;
  if (write(clientFd, buf, strlen(buf)) < 0) {
    perror("write() failed");
    exit(2);
  }
  memset(buf, 0, BUF_SIZE);
  if(read(clientFd, buf, BUF_SIZE) < 0) {
    perror("read() failed");
    exit(1);
  }
  printf("From server %s\n", buf);
  close(clientFd);

  return 0;
}
