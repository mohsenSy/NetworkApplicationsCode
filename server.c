#include <stdio.h> // perror, printf
#include <stdlib.h> // exit, atoi
#include <unistd.h> // read, write, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h> // memset
#include "file.h"

#include <pthread.h>

void* process_client(void* v) {
  int clientSocket = *((int *)v);
  char buffer[1024];
  memset(buffer, 0, sizeof(buffer));
  if (read(clientSocket, buffer, sizeof(buffer)) < 0) {
    perror("read() failed");
    return NULL;
  }
  printf("read client request\n");
  struct message rq;
  struct message rs;
  deserialize_message(&rq, buffer);
  process_message(&rq, &rs);
  printf("process_message\n");
  int s = 0;
  char *res = serialize_message(&rs, &s);
  printf("message serialized\n");
  //print_message(&rs);

  if (write(clientSocket, res, s) < 0) {
    perror("write() failed");
    return NULL;
  }
  free(v);
}

int main(int argc, char const *argv[]) {

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  int serverSocket, clientSocket;
  struct sockaddr_in serverAddr, clientAddr;
  int clientAddrLen = sizeof(clientAddr);
  char buffer[1024];

  if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket() failed");
    exit(1);
  }
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(atoi(argv[1]));
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    perror("bind() failed");
    exit(1);
  }
  if (listen(serverSocket, 10) < 0) {
    perror("listen() failed");
    exit(1);
  }
  while(1) {
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
      perror("accept() failed");
      continue;
    }
    pthread_t th;
    int *socket = malloc(4);
    *socket = clientSocket;
    if (pthread_create(&th, NULL, process_client, (void *)socket) < 0) {
      perror("thread create failed");
      continue;
    }
  }
  close(serverSocket);

  return 0;
}
