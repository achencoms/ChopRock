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
    clear();
    printf("[SERVER]: %s", buff);
    if(!strcmp(buff,"It is your turn to go\n")){
            int ctr = 0;
      char choice[15];
      char *proc;
      while( ctr != 4 ){
	if (ctr == 0){
	  clear();
	  printf("Do you wish to attack or move fingers?\n");
	  fgets(buff,sizeof(buff),stdin);

	  while( error(buff,"move") ){
	    printf("Incorrect input. Please choose: attack or move\n");
	    fgets(buff,sizeof(buff),stdin);
	  }
	  proc = strstr(buff,"\n");
	  *proc = 0;
	  strcat(choice,buff);
	  ctr++;
	  if(!strncmp(buff,"attack",sizeof(buff))) ctr = 1;
	  else if(!strncmp(buff,"move",sizeof(buff))) ctr = 2;
	}
	
	else if (ctr == 1){
	  clear();
	  printf("Do you wish to attack left or right?\n");
	  fgets(buff,sizeof(buff),stdin);
	  
	  while( error(buff,"movea") ){
	    printf("Incorrect input. Please choose: left or right\n");
	    fgets(buff,sizeof(buff),stdin);
	  }
	  proc = strstr(buff,"\n");
	  *proc = 0;
	  strcat(choice,buff);
	  ctr = 4;
	}

	else if (ctr == 2){
	  clear();
	  printf("Do you wish to move left or right?\n");
	  fgets(buff,sizeof(buff),stdin);
	  
	  while( error(buff,"movea") ){
	    printf("Incorrect input. Please choose: left or right\n");
	    fgets(buff,sizeof(buff),stdin);
	  }
	  proc = strstr(buff,"\n");
	  *proc = 0;
	  strcat(choice,buff);
	  ctr = 3;
	}

	else if (ctr == 3){
	  clear();
	  printf("How many?\n");
	  fgets(buff,sizeof(buff),stdin);
	  
	  while( error(buff,"movea") ){
	    printf("Incorrect input. Please choose a valid number.\n");
	    fgets(buff,sizeof(buff),stdin);
	  }
	  proc = strstr(buff,"\n");
	  *proc = 0;
	  strcat(choice,buff);
	  ctr = 4;
	}
      }
      write( sd, choice, sizeof(choice));
    }
    
    if(!strcmp(buff,"Choose rock, paper, scissors\n")){
      fgets(buff, sizeof(buff), stdin);
      while( error(buff,"rps") ){
	printf("Incorrect input. Please choose: rock, paper or scissors\n");
	fgets(buff,sizeof(buff),stdin);
      }      
      write( sd, buff, sizeof(buff));
    }
  }
}

void display(int ohl, int ohr, int mhl, int mhr){    }

int error(char * buff,char * phase){
  char* rps[3] = {"rock\n","paper\n","scissors\n"};   
  char* move[2] = {"attack\n","move\n"};
  char* movea[2] = {"left\n","right\n"};
  char* num[3] = {"1\n","2\n","3\n"};
  char* f;

  int c = 0;
  
  if (!strncmp(phase,"rps",sizeof(phase))){
    while(rps[c]){
      if (!strncmp(buff,rps[c],sizeof(buff))){
	return 0;
      }
      c++;
    }
    return -1;
  }

  else if (!strncmp(phase,"move", sizeof(phase))){
    while(move[c]){
      if (!strncmp(buff,move[c],sizeof(buff))){
	return 0;
      }
      c++;
    }
    return -1;
  }

  else if (!strncmp(phase,"movea", sizeof(phase))){
    while(movea[c]){
      if (!strncmp(buff,movea[c],sizeof(buff))){
	return 0;
      }
      c++;
    }
    return -1;
  }

  else if (!strncmp(phase,"num", sizeof(phase))){
    while(num[c]){
      if (!strncmp(buff,num[c],sizeof(buff))){
	return 0;
      }
      c++;
    }
    return -1;
  }
}
