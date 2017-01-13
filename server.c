#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "network.h"

int main(){
   int sd;
 
   sd = server_setup();
   int connection = server_connect( sd );
 
   char buff[128];
   read(connection, buff, sizeof(buff));
     
   strncpy(buff, "Thanks for the foo", sizeof(buff));
   write(connection, buff, sizeof(buff));

   return 0;
}

