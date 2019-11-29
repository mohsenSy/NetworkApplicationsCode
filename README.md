Network Application Course code
======

Here is a description for the contents of each file:

* `server.c` and `client.c` are two typical TCP server and client.
* `fork.c` and `thread.c` contain code for creating a new process and many threads.
* `server.fork.c` and `server.thread.c` these two servers use multi-processing and
  multi-threading to handle multiple connections.

File Server
===========

This folder contains code for the FileServer protocol, here are the files:

* `file.h` and `file.c` a header file for the functions and structures defined in file.h
  with their implementation found in `file.c`
* `test.c` and `test.txt` A main program to test functions defined in `file.h`.
