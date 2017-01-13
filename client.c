#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "network.h"


int main(){
  int sd;
  char *host = "127.0.0.1";
  
  sd = client_connect( host );
 
  printf("Sending Foo.\n");
  char buff[128];
  strncpy(buff, "Foo", sizeof(buff));

  write( sd, buff, sizeof(buff) );
  read ( sd, buff, sizeof(buff) );

  printf("Recieved: %s\n", buff);
	
  // while loop

  // clear terminal window
  // reading data from server
  // input request (rps)
  
  // write input to server
  // read data (won rock paper scissors or nah?)

  // change display to chopstics + output on who won
  // give choice (fgets + write)  or wait (read)

  // update display, then wait 2-3 seconds before loop

}

void display(int ohl, int ohr, int mhl, int mhr){
}
