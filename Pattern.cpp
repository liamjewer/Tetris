#include "Pattern.h"

Pattern::Pattern(int colour, const char pattern[4][4][2]){
      this -> colour = colour;
      this -> pattern = pattern;
      rotation = 0;
      calcMinX();
      calcMaxX();
      calcMinY();
      calcMaxY();
};

void Pattern::calcMinX(){
      int min = 5;
      for(int i = 0; i < 4; i++){
            if(pattern[rotation][i][0] < min){
                  min = pattern[rotation][i][0];
            }
      }
      minX = min;
}

void Pattern::calcMaxX(){
      int max = -5;
      for(int i = 0; i < 4; i++){
            if(pattern[rotation][i][0] > max){
                  max = pattern[rotation][i][0];
            }
      }
      maxX = max;
}

void Pattern::calcMinY(){
      int min = 5;
      for(int i = 0; i < 4; i++){
            if(pattern[rotation][i][1] < min){
                  min = pattern[rotation][i][1];
            }
      }
      minY = min;
}

void Pattern::calcMaxY(){
      int max = -5;
      for(int i = 0; i < 4; i++){
            if(pattern[rotation][i][1] > max){
                  max = pattern[rotation][i][1];
            }
      }
      maxY = max;
}

void Pattern::rotate(){
      if(rotation < 3){
            rotation++;
      }else{
            rotation = 0;
      }
      calcMinX();
      calcMaxX();
      calcMinY();
      calcMaxY();
}