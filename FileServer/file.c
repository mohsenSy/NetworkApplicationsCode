#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "file.h"

char *read_file(const char* name, int *size) {
  FILE* fp = fopen(name, "rb");
  fseek(fp, 0, SEEK_END);
  int len = ftell(fp);
  if (size) {
    *size = len;
  }
  rewind(fp);
  char *buf = malloc(len+1);
  fread(buf, len, 1 , fp);
  buf[len] = 0;
  fclose(fp);
  return buf;
}

void write_file(const char* name, const char* buf, int size) {
  FILE* fp = fopen(name, "wb");
  fwrite(buf, size, 1, fp);
  fclose(fp);
}

void print_hex(char* buf, int len) {
  char *c = buf;
  int i = 0;
  while(i < len) {
    printf("%#x\t", *c);
    c++;
    i++;
    if (i % 10 == 0) {
      printf("\n");
    }
  }
  printf("\n");
}

char *serialize_message(struct message *m, int *s) {
  int codeLen = (int)ceil(log10(m->code));
  int sizeLen = (int)ceil(log10(m->size));
  if (m->size == 0) {
    sizeLen = 1;
  }
  int total_size = codeLen + 5 + strlen(m->file_name) + sizeLen + m->size;
  if (s) {
    *s = total_size;
  }
  char *buf = malloc(total_size);
  sprintf(buf, "%d %s %d\r\n", m->code, m->file_name, m->size);
  if (m->size > 0) {
    memcpy(buf + codeLen + 5 + strlen(m->file_name) + sizeLen, m->data, m->size);
  }
  return buf;
}

char *find_data(char *b) {
  char *c = NULL;
  char *a = b;
  int max = 1000;
  int i = 0;
  while(1) {
    if (*a == '\r') {
      if (*(++a) == '\n') {
        c = ++a;
        break;
      }
    }
    else {
      a++;
    }
    i++;
    if (i == max) {
      break;
    }
  }
  return c;
}

void deserialize_message(struct message* m, char* data) {
  char *d = find_data(data);
  char *c = strtok(data, " ");
  m->code = atoi(c);
  c = strtok(NULL, " ");
  m->file_name = malloc(strlen(c));
  strcpy(m->file_name, c);
  c = strtok(NULL, " ");
  m->size = atoi(c);
  if (m->size > 0) {
    m->data = malloc(m->size);
    memcpy(m->data, d, m->size);
  }
}

void print_message(struct message* m) {
  printf("code is %d, file name is %s, size is %d\n", m->code, m->file_name, m->size);
  if (m->size > 0) {
    printf("data is\n");
    print_hex(m->data, m->size);
  }
}
