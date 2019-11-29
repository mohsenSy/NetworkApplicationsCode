#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

int main(int argc, char const *argv[]) {
  int s;
  char *data = read_file("test.txt", &s);
  printf("size of file is %d\n", s);
  printf("%s\n", data);
  char d[] = "hello world";
  write_file("test.txt", d, strlen(d));
  free(data);
  data = read_file("test.txt", NULL);
  free(data);

  struct message m1;
  m1.code = 100;
  m1.file_name = malloc(strlen("test.txt"));
  strcpy(m1.file_name, "test.txt");
  m1.size = 0;

  data = serialize_message(&m1, &s);
  printf("%s\n", data);
  print_hex(data, s);
  struct message m2;
  strcpy(data, "200 test.tx 4\r\n\x01\x02\x03\x30");
  deserialize_message(&m2, data);
  print_message(&m2);
  free(data);

  return 0;
}
