#ifndef __FILE_H
#define __FILE_H

char *read_file(const char *, int *);
void write_file(const char*, const char*, int);
void print_hex(char*, int);

#define CODE_DOWNLOAD 1
#define CODE_UPLOAD 2

#define CODE_OK 100
#define CODE_S_ERR 101
#define CODE_C_ERR 102
#define CODE_DATA 103

struct message {
  int code;
  char* file_name;
  int size;
  char* data;
};

char *serialize_message(struct message*, int *);
void deserialize_message(struct message*, char*);
void print_message(struct message*);

#endif /* end of include guard: __FILE_H */
