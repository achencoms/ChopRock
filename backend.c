int rps(char * c1, char * c2){ // 0 = rock. 1 = paper. 2 = scissor
   int p1,p2;
   //convert user1 string choice
   if(!strcmp(c1,"rock\n")) p1 = 0;
   else if(!strcmp(c1,"paper\n")) p1 = 1;
   else if(!strcmp(c1, "scissor\n")) p1 = 2;
   else return 3;
   //convert user2 string choice
   if(!strcmp(c2,"rock\n")) p2 = 0;
   else if(!strcmp(c2,"paper\n")) p2 = 1;
   else if(!strcmp(c2, "scissor\n")) p2 = 2;
   else return 3;

  //calculate who wins 
  int diff = p1 - p2;
   if (!diff){
      return 0; //tie.
   }

   if (diff > 0){
      if (diff == 2){
          return 2; //p2 win
      }
      return 1; //p1 win
   }

   else if (diff < 0){
      if (diff == -2){
          return 1; //p1 win 
      }
      return 2; //p2 win
   } 
}

void csmove(int *p1lh, int *p1rh, int *p2lh, int *p2rh, char m, int num, int player){
  //m - move choice (a for attack, s for switch)
  //num- number of fingers moved | (-) means move towards left, (+) means move towards right.
  //player making move. - 1 for p1, 2 for p2

  if (m == 'a'){
    if (player == 1){
      if (num < 0){ //player1 attacking left or right
	*p2lh -= num;}
      else{
	*p2rh += num;}
    }

    else{
      if (num < 0){ // player2 attacking left or right
	*p1lh -= num;}
      else{
	*p1rh += num;}
    }
  }

  else {
    if (player == 1){ //player1 moving fingers.
      *p1lh -= num;
      *p1rh += num;
    }

    else{ //player2 moving fingers
      *p2lh -= num;
      *p2rh += num;
    }
  }
}
