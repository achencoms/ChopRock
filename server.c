#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "network.h"
#include "backend.c"
// need to add in the server taking in the requests of the user
// i.e. Which hand would you like to use?, Which hand would you like to attack?
// The loser is the one who has both hands = 0

int main(){
  int sd,winner;
  char c1[128], c2[128];
  char buff[128];
  char turn[] = "It is your turn to go\n";
  char notturn[] = "It is the other player's turn, please wait...\n";
  char ask[] = "Choose rock, paper, scissors\n";
  char play1[128];
  char play2[128];
  char uplay1[128];
  char uplay2[128];
  
  sd = server_setup();
  while(1){
    int connection1 = server_connect( sd );
    printf("Player 1 connected to the server! Waiting for a match...\n");
    int connection2 = server_connect( sd );
    printf("Player 2 connected to the server! Match ready!\n");
    strcpy(buff, "You have found a match!\n");
    write(connection1, buff, sizeof(buff));
    write(connection2, buff, sizeof(buff));
    //hands
    int p1lh = 1;
    int p1rh = 1;
    int p2rh = 1;
    int p2lh = 1;    
    
    int f = fork();
    if(f == 0){
      while(1){	
	sprintf(play1,"Player 1 has %d fingers on his left hand, and %d fingers on his right hand!\n", p1lh, p1rh);
	sprintf(uplay1,"You have %d fingers on your left hand, and %d fingers on your right hand!\n", p1lh, p1rh);
	sprintf(play2,"Player 2 has %d fingers on his left hand, and %d fingers on his right hand!\n", p2lh, p2rh);
	sprintf(uplay2,"You have %d fingers on your left hand, and %d fingers on your right hand!\n", p2lh, p2rh);
	printf("%s", play1);
	printf("%s", play2);

	int choose = 0;

	//rps phase
	strcpy(buff,ask);//ask for rps choice
	while(choose == 0){
	  write(connection1, buff, sizeof(buff));
	  write(connection2, buff, sizeof(buff));

	  printf("cameltoe\n");
	  write(connection1,uplay1,sizeof(uplay1));
	  write(connection1,play2,sizeof(play2));
	  write(connection2,uplay2,sizeof(uplay2));
	  write(connection2,play1,sizeof(play1));
	  printf("moose\n");	  

	  //read user1 choice
	  read(connection1, c1, sizeof(c1));
	  read(connection2, c2, sizeof(c2));
	  printf("yes\n");
	  choose = rps(c1,c2);
	}
	
	//chopsticks phase
	if(choose == 1){
	  printf("moo\n");
	  strcpy(buff,turn);//notify user1
	  write(connection1, buff, sizeof(buff));
	  write(connection1, uplay1, sizeof(uplay1));
	  write(connection1, play2, sizeof(play2));
	  
	  strcpy(buff,notturn);//notify user2
	  write(connection2, buff, sizeof(buff));
	  write(connection2, uplay2, sizeof(uplay2));
	  write(connection2, play1, sizeof(play1));
	  
	  read(connection1, buff, sizeof(buff));//take user1 csmove
	  if(*buff == 'a') {
	    char * wich = strstr(buff, "k");
	    wich++;
	    if(*wich == 'l'){
	      char * sand = strstr(buff,"left");
	      sand += 4;
	      if(*sand == 'l'){
		csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'a', -1, -1, 1);
	      }
	      else csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'a', -1, 1, 1);
	    }
	    else {
	      char * sand = strstr(buff,"right");
	      sand += 5;
	      if(*sand == '1'){
		csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'a', 1, -1, 1);
	      }
	      else csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'a', 1, 1, 1);
	    }
	  }
	  else {
	    char * num = strstr(buff,"t");
	    num++;
	    char * yes = strstr(buff,"e");
	    yes++;
	    if(*yes == 'l'){
	      csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'm', -1, *num - 48, 1);
	    }
	    else csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'm', 1, *num - 48, 1);
	  }
	  printf("Message from Player 1: %s\n", buff);
	}
	
	else{
	  strcpy(buff,turn);//notify user2
	  write(connection2, buff, sizeof(buff));
	  write(connection2, uplay1,sizeof(uplay1));
	  write(connection2, play1, sizeof(play1));
	  
	  strcpy(buff,notturn);//notify user1
	  write(connection1, buff, sizeof(buff));
	  write(connection2, uplay2, sizeof(uplay2));
	  write(connection1, play2, sizeof(play2));
	  
	  read(connection2, buff, sizeof(buff));//take user2 csmove
	  if(*buff == 'a') {
	    char * wich = strstr(buff, "k");
	    wich++;
	    if(*wich == 'l'){
	      char * sand = strstr(buff,"left");
	      sand += 4;
	      if(*sand == 'l'){
		csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'a', -1, -1, 2);
	      }
	      else csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'a', -1, 1, 2);
	    }
	    else {
	      char * sand = strstr(buff,"right");
	      sand += 5;
	      if(*sand == '1'){
		csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'a', 1, -1, 2);
	      }
	      else csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'a', 1, 1, 2);
	    }
	  }
	  else {
	    char * num = strstr(buff,"t");
	    num++;
	    char * yes = strstr(buff,"e");
	    yes++;
	    if(*yes == 'l'){
	      csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'm', -1, *num - 48, 2);
	    }
	    else csmove(&p1lh, &p1rh, &p2lh, &p2rh, 'm', 1, *num - 48, 2);
	  }
	  printf("Message from Player 2: %s\n", buff);
	}
      }
      exit(0);
    }
  }
  return 0;
}

