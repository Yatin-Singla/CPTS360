#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>


#define MAX   256
#define PORT 1234
  
char line[MAX];
int n;

int main(int argc, char *argv[]) 
{ 
    int sfd, cfd, len, num1, num2; 
    struct sockaddr_in saddr, caddr; 
  
    printf("1. create a TCP socket\n");
    sfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sfd < 0) { 
        printf("socket creation failed\n"); 
        exit(1); 
    }

    printf("2. fill in [localhost IP port=1234] as server address\n");
    bzero(&saddr, sizeof(saddr)); 
    saddr.sin_family = AF_INET; 
    saddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    saddr.sin_port = htons(PORT); 
  
    printf("3. bind socket with server address\n");
    if ((bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr))) != 0) { 
        printf("socket bind failed\n"); 
        exit(2); 
    }
      
    printf("4. server listens\n");
    if ((listen(sfd, 5)) != 0) { 
        printf("Listen failed\n"); 
        exit(3); 
    }

    len = sizeof(caddr);
    while(1){
       printf("server accepting connection\n");
       cfd = accept(sfd, (struct sockaddr *)&caddr, &len); 
       if (cfd < 0) { 
          printf("server acccept failed\n"); 
          exit(4); 
       }
       printf("server acccepted a client connection\n"); 

       // server Processing loop
       while(1){
          printf("server: ready for next request\n");
	  n = read(cfd, line, MAX);
          if (n==0){
             printf("server: client died, server loops\n");
             close(cfd);
             break;
          }
	  sscanf(line, "%d %d", &num1, &num2);      
          // show the line contents
          printf("server: read  n=%d bytes; line=[%s]\n", n, line);
	  sprintf(line, "%d", num1+num2);
          strcat(line, " ECHO");

          // send the echo line to client 
          n = write(cfd, line, MAX);
          printf("server: wrote n=%d bytes; ECHO=[%s]\n", n, line);
       }
    }
} 
