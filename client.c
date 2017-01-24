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
  char uplay[128];
  char oplay[128];
  
  int ur,ul,or,ol;
	
  //starting to match make for a player
  printf("Waiting for a player to join...\n");
  //read for a response for the server to search for another player
  read(sd,buff,sizeof(buff) );
  //allow the user to start playing the other user
  printf("You have successfully connected with another player!\n");

  while(read(sd,buff,sizeof(buff)) != 0){

    clear();
    if(!strcmp(buff,"Choose rock, paper, scissors\n")){
      read(sd, uplay, sizeof(uplay) );
      read(sd, oplay, sizeof(oplay) );
      
	  char * user = strstr(uplay,"have");
	  user += 5;
	  ul = *user - 48;
	  user = strstr(uplay,"and ");
	  user += 4;
	  ur = *user - 48;
	  char * op = strstr(oplay,"has");
	  op += 4;
	  ol = *op - 48;
	  op = strstr(oplay,"and ");
	  op += 4;
	  or = *op - 48;
	  
	  if(!(or + ol) || !(ul + ur)){
		  clear();
		  if(!(or + ol)) printf("You have won the match of ChopRock! We hope you enjoyed playing!\n");
		  else if(!(ul+ur)) printf("Your opponent has won the match of ChopRock... Come back next time to try again!\n");
		  return 0;
	  }
	  
      printf("%s",uplay);
      printf("%s",oplay);
      printf("[SERVER]: %s", buff);
      fgets(buff, sizeof(buff), stdin);
      while( error(buff,"rps") ){
	     printf("Incorrect input. Please choose: rock, paper or scissors\n");
	     fgets(buff,sizeof(buff),stdin);
      }      
      write( sd, buff, sizeof(buff));
    }    

    if(!strcmp(buff,"It is your turn to go\n")){
    int ctr = 0;
    char choice[128];
    char *proc;
    while( ctr != 5 ){
	if (ctr == 0){
	  clear();

	  printf("%s",uplay);
	  printf("%s",oplay);
	  printf("Do you wish to attack or move fingers?\n");
	  fgets(buff,sizeof(buff),stdin);

	  //printf("%s\n", buff);
	  while( error(buff,"move") ){
	    printf("Incorrect input. Please choose: attack or move\n");
	    fgets(buff,sizeof(buff),stdin);
	  }
	  proc = strstr(buff,"\n");
	  *proc = 0;
	  strncpy(choice,buff,sizeof(choice));
	  if(!strncmp(buff,"attack",sizeof(buff))) ctr = 1;
	  else if(!strncmp(buff,"move",sizeof(buff))) ctr = 3;
	}
	
	else if(ctr == 1){
	  printf("\nDo you wish to use your left hand or right hand?\nType back to go back.\n");
	  fgets(buff,sizeof(buff),stdin);
	  
	  while(error(buff,"movea") ){
		  printf("Incorrect input. Please choose: left or right\n");
		  fgets(buff,sizeof(buff),stdin);
	  }
	  proc = strstr(buff, "\n");
	  *proc = 0;
	  if(*buff == 'l' && !ul) printf("You do not have any fingers on your left hand\n");
	  else if(*buff == 'r' && !ur) printf("You do not have any fingers on your right hand\n");
	  else if(!strncmp(buff,"back",sizeof(buff))){
	    ctr = 0;
	    //strncpy(buff,"",sizeof(buff));
	    strncpy(choice,"",sizeof(choice));
	  }
	  else{
	    strncat(choice,buff,sizeof(choice));
	    ctr = 2;
	  }
	}
	
	else if (ctr == 2){
	  printf("\nDo you wish to attack the opponent's left or right hand?\nType back to go back.\n");
	  fgets(buff,sizeof(buff),stdin);
	  
	  while( error(buff,"movea") ){
	    printf("Incorrect input. Please choose: left or right\n");
	    fgets(buff,sizeof(buff),stdin);
	  }
	  proc = strstr(buff,"\n");
	  *proc = 0;
	  
	  if(*buff == 'l' && !ol) printf("The opponent doesn't have any fingers on the left hand!\n");
	  else if(*buff == 'r' && !or) printf("The opponent doesn't have any fingers on the right hand!\n");
	  else if(!strncmp(buff,"back",sizeof(buff))){
	    ctr = 0;
	    //strncpy(buff,"",sizeof(buff));
	    strncpy(choice,"",sizeof(choice));
	  }
	  else{
	    strncat(choice,buff,sizeof(choice));
	    ctr = 5;
	  }
	}

	else if (ctr == 3){
	  printf("\nDo you wish to move fingers from your left hand or right hand?\nType back to go back.\n");
	  fgets(buff,sizeof(buff),stdin);
	  
	  while( error(buff,"movea") ){
	    printf("Incorrect input. Please choose: left or right\n");
	    fgets(buff,sizeof(buff),stdin);
	  }
	  proc = strstr(buff,"\n");
	  *proc = 0;
	  
	  if(*buff == 'l' && !ul) printf("You don't have any fingers on your left hand!\n");
	  else if(*buff == 'r' && !ur) printf("You don't have any fingers on your right hand!\n");
	  else if(!strncmp(buff,"back",sizeof(buff))){
	    ctr = 0;
	    //strncpy(buff,"",sizeof(buff));
	    strncpy(choice,"",sizeof(choice));
	  }
	  else{
	    strncat(choice,buff,sizeof(choice));
	    ctr = 4;
	  }
	}

	else if (ctr == 4){
	  printf("\nHow many?\nType back to go back.\n");
	  fgets(buff,sizeof(buff),stdin);
	  
	  while( error(buff,"num") ){
	    printf("Incorrect input. Please choose a valid number.\n");
	    fgets(buff,sizeof(buff),stdin);
	  }
	  proc = strstr(buff,"\n");
	  *proc = 0;
	  char * dir = strstr(choice,"t");
	  dir--;
	  if(!strncmp(buff,"back",sizeof(buff))){
	    ctr = 0;
	    //strncpy(buff,"",sizeof(buff));
	    strncpy(choice,"",sizeof(choice));
	  }
	  else if(*dir == 'f' && ul < *buff - 48) printf("You do not have enough fingers to move from your left hand!\n");
	  else if(*dir == 'h' && ur < *buff - 48) printf("You do not have enough fingers to move from your right hand\n");
	  else if(*dir == 'f' && ((ur + *buff - 48) > 4)) printf("You are moving too many fingers to your right hand!\n");
	  else if(*dir == 'h' && ((ul + *buff - 48) > 4)) printf("You are moving too many fingers to your left hand\n");
	  else{
	    strncat(choice,buff,sizeof(choice));
	    ctr = 5;
	  }
	}
    }
    write( sd, choice, sizeof(choice));
    strncpy(choice,"",sizeof(choice));
    }

    if(!strncmp(buff,"It is the other player's turn, please wait...\n",sizeof(buff))){
	clear();
	printf("%s",uplay);
	printf("%s",oplay);
	printf("%s", buff);
    }
  }
}

void display(int ohl, int ohr, int mhl, int mhr){    }

int error(char * buff,char * phase){
  char* rps[5] = {"rock\n","paper\n","scissors\n","back\n",0};   
  char* move[4] = {"attack\n","move\n","back\n",0};
  char* movea[4] = {"left\n","right\n","back\n",0};
  char* num[5] = {"1\n","2\n","3\n","back\n",0};

  int c = 0;
  
  if (!strncmp(phase,"rps",sizeof(phase))){
    while(rps[c]){
      if (!strncmp(buff,rps[c],sizeof(buff))){
	//printf("comp: %s and %s\n",rps[c],buff);
	return 0;
      }
      c++;
    }
    return -1;
  }

  else if (!strncmp(phase,"move", sizeof(phase))){
    while(move[c]){
      if (!strncmp(buff,move[c],sizeof(buff))){	
	//printf("comp: %s and %s\n",rps[c],buff);
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
