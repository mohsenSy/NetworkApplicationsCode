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
	if((check= gethostname(hostname, MAXHOSTNAMELEN))==-1){
		herror("gethostname");
		exit(2);
	}	
	printf("Host name  using gethostname: %s\n", hostname);
	if ((h=gethostbyname(hostname)) == NULL) {
		herror("gethostbyname");
		exit(1);
	}
  printf("Host name  using gethostbyname: %s\n", h->h_name);
  printf("IP Address using gethostbyname: %s\n",inet_ntoa(*((struct in_addr *)h->h_addr)));
   return 0;
}