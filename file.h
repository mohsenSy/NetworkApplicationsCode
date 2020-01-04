#ifndef __FILE_H
#define __FILE_H

#define FILL_NAME(m, n) m.file_name = malloc(strlen(n)); \
  strcpy(m.file_name, n);

char *read_file(const char *, int *);
void write_file(const char*, const char*, int);
void print_hex(char*, int);

struct message {
  int code;
  char* file_name;
  int size;
  char* data;
};

#define CODE_DOWNLOAD 1
#define CODE_UPLOAD 2
#define CODE_REMOVE 3

#define CODE_DATA 100
#define CODE_OK 101

char *serialize_message(const struct message*, int*);
void deserialize_message(struct message*, char*);
void process_message(struct message*, struct message*);
void process_download(char*, struct message*);
void process_data(struct message*);
void process_ok(struct message*);
void process_remove(struct message*, struct message*);
#endif /* end of include guard: __FILE_H */
