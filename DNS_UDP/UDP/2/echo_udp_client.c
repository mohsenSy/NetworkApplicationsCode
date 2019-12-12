#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUF_SIZE 500

  
int main(int argc, char *argv[]) {
	
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s, j;
	size_t len;
	ssize_t nread;
 
 char buf[BUF_SIZE];
 
 if (argc < 3){
    fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
	exit(EXIT_FAILURE);
	}


/* Reset hints structure */

/* Set hints structure values to look for IPv4 address UDP socket, don't forget
	other important fields */



s = /*Get addrinfo*/ ;
if (s != 0){
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
	exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
	Try each address until we successfully connect(2).
 
	If socket(2) (or connect(2)) fails,we (close the socket
	and) try the next address. */

    
for (rp = result; rp != NULL; rp = rp->ai_next){
 
	sfd = /*Socket*/;
	if (sfd == -1)
		continue;


	if ( /*Connect*/ != -1)
		break; /* Success */

	close(sfd);
}

 
if (rp == NULL) { /* No address succeeded */
 
	fprintf(stderr, "Could not connect\n");
	exit(EXIT_FAILURE);
 
}

 
 freeaddrinfo(result);
 /* No longer needed */


/* Send remaining command-line arguments as separate datagrams, and read responses from server */

        
  for (j = 3; j < argc; j++) {

    len = strlen(argv[j]) + 1;
    /* +1 for terminating null byte */


if (len + 1 > BUF_SIZE) {
	fprintf(stderr,"Ignoring long message in argument %d\n", j);
	continue;
	}

 
if (/*Write*/ != len) {
  fprintf(stderr, "partial/failed write\n");
  exit(EXIT_FAILURE);
 }


 nread = /*Read*/;

 if (nread == -1)
 {
  perror("read");
  exit(EXIT_FAILURE);
 }


printf("Received %ld bytes: %s\n", (long) nread, buf);
 }
exit(EXIT_SUCCESS);

 }


