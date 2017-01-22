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

   sd = server_setup();
   while(1){
  	int connection1 = server_connect( sd );
	printf("Player 1 connected to the server! Waiting for a match...\n");
        int connection2 = server_connect( sd );
	printf("Player 2 connected to the server! Match ready!\n");
	strcpy(buff, "You have found a match!\n");
	write(connection1, buff, sizeof(buff));
	write(connection2, buff, sizeof(buff));

	int f = fork();
	if(f == 0){
	    while(1){
	      int choose = 0;
	      printf("sloppy\n");
              //rps phase
	      strcpy(buff,ask);//ask for rps choice
	      while(choose == 0){
	        write(connection1, buff, sizeof(buff));
	        write(connection2, buff, sizeof(buff));
	        //read user1 choice
	        read(connection1, c1, sizeof(c1));
	        read(connection2, c2, sizeof(c2));
	        choose = rps(c1,c2);
		printf("%d\n",choose);
	      }
	      
	      //chopsticks phase
	      if(choose == 1){
		strcpy(buff,turn);//notify user1
		write(connection1, buff, sizeof(buff));
	  
		strcpy(buff,notturn);//notify user2
		write(connection2, buff, sizeof(buff));

		read(connection1, buff, sizeof(buff));//take user1 csmove
		printf("Message from Player 1: %s", buff);
	      }
	 
	      else{
		strcpy(buff,turn);//notify user2
		write(connection2, buff, sizeof(buff));

		strcpy(buff,notturn);//notify user1
		write(connection1, buff, sizeof(buff));

		read(connection2, buff, sizeof(buff));//take user2 csmove
		printf("Message from Player 2: %s", buff);
	      }
	    }
	 exit(0);
        }
   }
   return 0;
}

