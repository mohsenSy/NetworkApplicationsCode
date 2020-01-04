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

void print_hex(char *b, int s) {
  char *c = b;
  int i = 0;
  while(i < s) {
    printf("%#x\t", *c);
    c++;
    i++;
    if (i % 10 == 0) {
      printf("\n");
    }
  }
  printf("\n");
}

char *serialize_message(const struct message* m, int *s) {
  int codeLen = (int)(floor(log10(m->code)) + 1);
  int sizeLen = (int)(floor(log10(m->size)) + 1);
  if (m->code == 0) {
    codeLen = 1;
  }
  if (m->size == 0) {
    sizeLen = 1;
  }
  int total_size = codeLen + 1 + strlen(m->file_name) + 1 + sizeLen + 2 + m->size;
  if (s) {
    *s = total_size;
  }
  char *buf = malloc(total_size);
  sprintf(buf, "%d %s %d\r\n", m->code, m->file_name, m->size);
  if (m->size > 0) {
    printf("serialize_message %d\n", m->size);
    memcpy(buf + codeLen + 1 + strlen(m->file_name) + 1 + sizeLen + 3, m->data, m->size);
  }
  return buf;
}

void deserialize_message(struct message *m, char *b) {
  char *c = strtok(b, " ");
  m->code = atoi(c);
  c = strtok(NULL, " ");
  m->file_name = malloc(strlen(c));
  strcpy(m->file_name, c);
  c = strtok(NULL, "\r\n");
  m->size = atoi(c);
  if (m->size > 0) {
    m->data = malloc(m->size);
    memcpy(m->data, c + strlen(c) + 3, m->size);
  }
  else {
    m->data = NULL;
  }
}

void process_data(struct message* m) {
  write_file(m->file_name, m->data, m->size);
}

void process_download(char* name, struct message* m) {
  m->code = CODE_DATA;
  m->file_name = name;
  m->data = read_file(name, &m->size);
}

void process_message(struct message* req, struct message* res) {
  if (req->code == CODE_DOWNLOAD) {
    process_download(req->file_name, res);
  }
  else if (req->code == CODE_DATA) {
    process_data(req);
  }
  else if (req->code == CODE_REMOVE) {
    process_remove(req, res);
  }
  else if (req->code == CODE_OK) {
    process_ok(req);
  }
}

void process_remove(struct message* req, struct message* res) {
  remove(req->file_name);
  res->code = CODE_OK;
  res->size = 0;
  res->file_name = req->file_name;
}

void process_ok(struct message* m) {
  printf("Operation completed on file %s\n", m->file_name);
}
