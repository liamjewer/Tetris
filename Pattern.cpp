#include "Pattern.h"

Pattern::Pattern(int colour, const char pattern[4][4][2]){
      this -> colour = colour;
      this -> pattern = pattern;
      rotation = 0;
};

int Pattern::getWidth(){
      int width = 0;
      for(int i = 0; i < 4; i++){
            if(pattern[rotation][i][0] + 1 > width){
                  width = pattern[rotation][i][0] + 1;
            }
      }
      return width;
}

void Pattern::rotate(){
      if(rotation < 3){
            rotation++;
      }else{
            rotation = 0;
      }
}