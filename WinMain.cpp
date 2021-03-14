#include <windows.h>
#include "Window.h"
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <time.h>

#include <iostream>
#include "Pattern.h"
#include "Patterns.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20


const float COLOURS[7][3] = {
    {1.0f, 0.4f, 0.4f},
    {0.4f, 1.0f, 0.4f},
    {0.4f, 0.4f, 1.0f},
    {0.4f, 1.0f, 1.0f},
    {1.0f, 0.4f, 1.0f},
    {1.0f, 1.0f, 0.4f},
    {1.0f, 0.4f, 0.2f},
};
const Pattern PATTERNS[7] = {Pattern(0, Patterns::SQUARE_ORIENTATION), Pattern(1, Patterns::LINE_ORIENTATION), Pattern(2, Patterns::T_ORIENTATION), Pattern(3, Patterns::L_ORIENTATION), Pattern(4, Patterns::RL_ORIENTATION), Pattern(5, Patterns::S_ORIENTATION), Pattern(6, Patterns::Z_ORIENTATION)};
const float BOARD_Y_UNIT (2.0f/BOARD_HEIGHT);
const float BOARD_X_UNIT (1.0f/BOARD_WIDTH);

int board[BOARD_WIDTH][BOARD_HEIGHT] = {0};

Pattern active = PATTERNS[0];
int activePos[2] = {0,0};

float GetBoardX(int boardX){
    return (boardX/(float)BOARD_WIDTH) - 0.5;
}
float GetBoardY(int boardY){
    return (boardY/(float)BOARD_HEIGHT)*2 - 1;
}

void Tick() {
    
}

void FixedTick() {

}

void LateTick() {

}

void Render() {
    //board outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(-0.5, 1, 0.5, -1);
    //render board
    for(int x = 0; x < BOARD_WIDTH; x++){
        for(int y = 0; y < BOARD_HEIGHT; y++){
            if(board[x][y] > 0){
                glColor3f(COLOURS[board[x][y] - 1][0], COLOURS[board[x][y] - 1][1], COLOURS[board[x][y] - 1][2]);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glRectf(GetBoardX(x), GetBoardY(y), GetBoardX(x) + BOARD_X_UNIT, GetBoardY(y) + BOARD_Y_UNIT);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glColor3f(0.0f, 0.0f, 0.0f);
                glRectf(GetBoardX(x), GetBoardY(y), GetBoardX(x) + BOARD_X_UNIT, GetBoardY(y) + BOARD_Y_UNIT);
            }
        }
    }
    //render falling piece
    for(int i = 0; i < 4; i++){
        glColor3f(COLOURS[active.colour][0],  COLOURS[active.colour][1], COLOURS[active.colour][2]);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glRectf(GetBoardX(activePos[0] + active.pattern[i][0]), GetBoardY(activePos[1] + active.pattern[i][1]), GetBoardX(activePos[0] + active.pattern[i][0]) + BOARD_X_UNIT, GetBoardY(activePos[1] + active.pattern[i][1]) + BOARD_Y_UNIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(0.0f, 0.0f, 0.0f);
        glRectf(GetBoardX(activePos[0] + active.pattern[i][0]), GetBoardY(activePos[1] + active.pattern[i][1]), GetBoardX(activePos[0] + active.pattern[i][0]) + BOARD_X_UNIT, GetBoardY(activePos[1] + active.pattern[i][1]) + BOARD_Y_UNIT);
    }
}

void Init(){
    glLineWidth(4);
    srand (time(NULL));
    int random = rand() % 7;
    active = PATTERNS[6];
}


INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    Jewer2D::Init(640, 640, "Tetris", &Tick, &FixedTick, &LateTick, &Render);
    Jewer2D::backgroundR = 0.1f;
    Jewer2D::backgroundG = 0.1f;
    Jewer2D::backgroundB = 0.1f;
    Init();
    Jewer2D::BeginLoop();

    return 0;
}