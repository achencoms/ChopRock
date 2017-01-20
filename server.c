#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "network.h"

// need to add in the server taking in the requests of the user
// i.e. Which hand would you like to use?, Which hand would you like to attack?
// The loser is the one who has both hands = 0

int main(){
   int sd;
   char buff[128];
   char turn[] = "It is your turn to go\n";
   char notturn[] = "It is the other player's turn, please wait...\n";

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
  	 int choose = 0;
	while(1){
	//while(read(connection1, buff, sizeof(buff)) || read(connection2, buff, sizeof(buff))){
         if(choose == 0){
	  strcpy(buff,turn);
	  write(connection1, buff, sizeof(buff));
	  strcpy(buff,notturn);
	  write(connection2, buff, sizeof(buff));
 	  read(connection1, buff, sizeof(buff));
	  printf("Message from Player 1: %s", buff);
	  choose = 1;
   	 }
	 else{
	  strcpy(buff,turn);
	  write(connection2, buff, sizeof(buff));
	  strcpy(buff,notturn);
	  write(connection1, buff, sizeof(buff));
	  read(connection2, buff, sizeof(buff));
	  printf("Message from Player 2: %s", buff);
	  choose = 0;
	 }
	}
	 exit(0);
        }
   }
   return 0;
}

