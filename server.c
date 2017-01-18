#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "network.h"

int main(){
   int sd;
 
   sd = server_setup();
   while(1){
  	int connection = server_connect( sd );

	int f = fork();
	if(f == 0){
   	 char buff[128];
 	 while(read(connection, buff, sizeof(buff))){
	  printf("Received message: %s", buff);
   	  strncpy(buff, "Thanks for the foo", sizeof(buff));
   	  write(connection, buff, sizeof(buff));
   	 }
	 exit(0);
        }
   }
   return 0;
}

