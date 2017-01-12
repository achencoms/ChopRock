#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

void errorhandle(int i){
   if (i < 0){
      printf("Error: %s", strerror(errno));
   }
}

int server_setup(){
   int sd;
   int i;

   sd = socket( AF_INET, SOCK_STREAM, 0);
   errorhandle(sd);

   struct sockaddr_in sock;
   sock.sin_family = AF_INET;
   sock.sin_addr.s_addr = INADDR_ANY;
   sock.sin_port = htons(22);

   i = bind(sd, (struct sockaddr *)&sock, sizeof(sock));
   errorhandle(i);
   
   return sd;
}

int server_connect(int sd){
   int connection, i;
	
   i = listen(sd , 1);
   errorhandle(i);
   
   struct sockaddr_in sock1;
   unsigned int sock1_len = sizeof(sock1);
   connection = accept(sd, (struct sockaddr *)&sock1, &sock1_len);

   errorhandle( connection );
  
   printf("[server] connected to %s\n", inet_ntoa( sock1.sin_addr ) );
  
   return connection;
}

int client_connect( char *host ) {
   int sd, i;
  
   sd = socket( AF_INET, SOCK_STREAM, 0 );
   errorhandle( sd );
  
   struct sockaddr_in sock;
   sock.sin_family = AF_INET;
   inet_aton( host, &(sock.sin_addr));
   sock.sin_port = htons(9001);
  
   printf("[client] connecting to: %s\n", host );
   i = connect( sd, (struct sockaddr *)&sock, sizeof(sock) );
   errorhandle(i);
  
   return sd;
}
