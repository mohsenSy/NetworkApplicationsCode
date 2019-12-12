#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

#include <netdb.h>
#define BUF_SIZE 500


int main(int argc, char *argv[]){ 
	
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s;
	struct sockaddr_in peer_addr;
	socklen_t peer_addr_len;
	ssize_t nread;
	char buf[BUF_SIZE];
     
  if (argc != 2) {
      
    fprintf(stderr, "Usage: %s port\n", argv[0]);
	exit(EXIT_FAILURE);
    }

        
/* Reset hints structure */

/* Set hints structure values to look for any address type UDP socket, don't forget
	to set all fields here, set UNKNOWN fields to NULL */
   


      
 s = /* getaddrinfo*/;
   
 if (s != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(EXIT_FAILURE);
 }

   
 /* getaddrinfo() returns a list of address structures.Try each address until
   we successfully bind(2).
 If socket(2) (or bind(2)) fails,
   we (close the socket
 and) try the next address. */


for (rp = result; rp != NULL; rp = rp->ai_next){
             
	sfd = /*Socket*/);
	if (sfd == -1)
		continue;
	
	if (/*Bind*/ == 0)
		break; /* You are Successful */

	close(sfd);
 
}

 
if (rp == NULL) {   
  /* No address succeeded */
 fprintf(stderr, "Could not bind\n");
 exit(EXIT_FAILURE);

 }

freeaddrinfo(result); /* No longer needed */


/* Read datagrams and echo them back to sender */

 
for (;;) {

  peer_addr_len = sizeof(struct sockaddr_in);

  nread = /*recvfrom*/;
	if (nread == -1) continue; 
	/* Ignore failed request */


 char host[NI_MAXHOST], service[NI_MAXSERV];


 s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);

 if (s == 0)
	printf("Received %ld bytes from %s:%s\n",(long) nread, host, service);
 else
	fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));


 if (/*sendto*/!= nread)
	fprintf(stderr, "Error sending response\n");
 }
 
}



