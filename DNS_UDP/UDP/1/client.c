#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

#define RCVBUFSIZE 32  /* Size of send buffer */
char echoBuffer[RCVBUFSIZE]; 

int main (int argc, char *argv[] )
{

struct sockaddr_in echoServAddr;
struct sockaddr_in echoClientAddr;

int clientSock, recvMsgSize, sendMsgSize;

void DieWithError(char* error)
  { perror(error);
    exit(1); }


 if (( /*Create Socket*/ ) < 0)
    DieWithError("socket() failed");

 
/*Set echoClientAddr*/

if(/*bind*/ < 0)
DieWithError("binding() failed");


/*Set echoServAddr*/


int servAddrLen = sizeof(echoServAddr);
memset(echoBuffer,'\0', sizeof(echoBuffer));
gets(echoBuffer);


if (sendMsgSize = /*Send*/ != strlen(echoBuffer))
DieWithError("sendto() sent a different number of bytes than expected");



if ((/*Receive*/) != sendMsgSize)
DieWithError("recvfrom() failed");

printf("message is %s\n", echoBuffer);
close(clientSock);
}






