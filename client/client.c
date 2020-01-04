#include <stdio.h> // perror, printf
#include <stdlib.h> // exit, atoi
#include <unistd.h> // write, read, close
#include <arpa/inet.h> // sockaddr_in, AF_INET, SOCK_STREAM, INADDR_ANY, socket etc...
#include <string.h> // strlen, memset
#include "../file.h"

int main(int argc, char const *argv[]) {

  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  int serverFd;
  struct sockaddr_in server;
  int len;
  int port = atoi(argv[1]);
  char *server_ip = "127.0.0.1";
  if (argc == 3) {
    server_ip = argv[1];
    port = atoi(argv[2]);
  }
  serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFd < 0) {
    perror("Cannot create socket");
    exit(1);
  }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(server_ip);
  server.sin_port = htons(port);
  len = sizeof(server);
  if (connect(serverFd, (struct sockaddr *)&server, len) < 0) {
    perror("Cannot connect to server");
    exit(2);
  }

  struct message req;
  req.code = CODE_DOWNLOAD;
  req.file_name = malloc(strlen("test.txt"));
  strcpy(req.file_name, "test.txt");
  req.size = 0;
  int s = 0;
  char *buffer = serialize_message(&req, &s);

  if (write(serverFd, buffer, s) < 0) {
    perror("Cannot write");
    exit(3);
  }
  char recv[1024];
  memset(recv, 0, sizeof(recv));
  int r = read(serverFd, recv, sizeof(recv));
  if ( r < 0) {
    perror("cannot read");
    exit(4);
  }
  print_hex(recv, r);
  struct message res;
  deserialize_message(&res, recv);
  process_message(&res, NULL);
  //print_message(&res);
  printf("Received %s from server\n", recv);
  close(serverFd);
  return 0;
}
