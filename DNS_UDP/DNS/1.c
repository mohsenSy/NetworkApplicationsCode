#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAXHOSTNAMELEN 25	
int main(int argc, char *argv[])
{
	struct hostent *h;
	char hostname[MAXHOSTNAMELEN];
	int check;
	if (argc != 2) {  
		fprintf(stderr,"usage: getip address\n");
		exit(1);
	}
	if ((h=gethostbyname(argv[1])) == NULL) {  
		herror("gethostbyname");
		exit(1);
	}
  printf("Host name  using gethostbyname: %s\n", h->h_name);
  printf("IP Address using gethostbyname: %s\n",inet_ntoa(*((struct in_addr *)h->h_addr))); 	
   return 0;
}