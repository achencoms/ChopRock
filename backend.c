int rps(int p1, int p2){ // 0 = rock. 1 = paper. 2 = scissor
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


