#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "network.h"
#include "client.h"

#define clear() printf("\033[H\033[J")

int main(){
  int sd;
  char *host = "127.0.0.1";

  sd = client_connect( host );
  printf("Connected to the server...\n");

  char buff[128];
  /*while(fgets(buff,sizeof(buff), stdin) != "\n"){
 	 write( sd, buff, sizeof(buff) );
 	 read ( sd, buff, sizeof(buff) );
  	 printf("Recieved: %s\n", buff);
  }*/
	
  //starting to match make for a player
  printf("Waiting for a player to join...\n");
  //read for a response for the server to search for another player
  read(sd,buff,sizeof(buff) );
  //allow the user to start playing the other user
  printf("You have successfully connected with another player!\n");

  while(read (sd, buff, sizeof(buff)) != 0){
    printf("[SERVER]: %s", buff);
    if(!strcmp(buff,"It is your turn to go\n")){
      fgets(buff, sizeof(buff), stdin);
      write( sd, buff, sizeof(buff) );
    }
    
    if(!strcmp(buff,"Choose rock, paper, scissors\n")){
      fgets(buff, sizeof(buff), stdin);
      write( sd, buff, sizeof(buff));
    }
  }
}

void display(int ohl, int ohr, int mhl, int mhr){    }

int error(char * buff,char * phase){
  char* rps[3] = {"rock","paper","scissors"};   
  char* move[2] = {"attack","move"};
  char* movea[2] = {"left","right"};
  char* f;
  
  if (!strncmp(phase,"rps",sizeof(phase))){
      
    }

 else if (!strncmp(phase,"move",sizeof(phase))){
   }
    
}
