#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define RCVBUFSIZE 32  /* Size of receive buffer */
char echoBuffer[RCVBUFSIZE]; 

int main (int argc, char *argv[])
{
	int servSock, clientSock, clntLen, recvMsgSize; 
	struct sockaddr_in  echoServAddr, echoClientAddr;
	
	void DieWithError(char* error){ 
		perror(error);
		exit(1);
	}


if ((/*Create Socket*/) < 0)  
       DieWithError("socket() failed");


/*Set echoServAddr*/


if ( /*Bind*/ < 0)
		DieWithError("bind() failed");

for (;;){ /* Run forever */
    int clientAddrLen = sizeof(echoClientAddr); 
    memset(echoBuffer,'\0',sizeof(echoBuffer));
	if ((recvMsgSize = /*Recieve*/ < 0))
		DieWithError("recvfrom() failed");
		puts(echoBuffer);
	if ( /*Send*/ != recvMsgSize)
		DieWithError("sendto() failed");
    }  
}












