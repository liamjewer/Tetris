#include "Pattern.h"

Pattern::Pattern(int colour, const int pattern[4][2]){
      this -> colour = colour;
      this -> pattern = pattern;
};

int Pattern::getWidth(){
      int width = 0;
      for(int i = 0; i < 4; i++){
            if(pattern[i][0] + 1 > width){
                  width = pattern[i][0] + 1;
            }
      }
      return width;
}