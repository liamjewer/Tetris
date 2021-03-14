#include <windows.h>
#include "Window.h"
#include <GL/glu.h>
#include <GLFW/glfw3.h>

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

int board[BOARD_WIDTH][BOARD_HEIGHT] = {0};

//Pattern active;
//int activePos[2];

void Tick() {
    
}

void FixedTick() {

}

void LateTick() {

}

void Render() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(-0.5, 1, 0.5, -1);
    for(int x = 0; x < BOARD_WIDTH; x++){
        for(int y = 0; y < BOARD_HEIGHT; y++){
            if(board[x][y] > 0){
                glColor3f(COLOURS[board[x][y] - 1][0], COLOURS[board[x][y] - 1][1], COLOURS[board[x][y] - 1][2]);
                float drawX = (x/(float)BOARD_WIDTH) - 0.5;
                float drawY = (y/(float)BOARD_HEIGHT)*2 - 1;
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glRectf(drawX, drawY, drawX + (1.0f/BOARD_WIDTH), drawY + (2.0f/BOARD_HEIGHT));
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glColor3f(0.0f, 0.0f, 0.0f);
                glRectf(drawX, drawY, drawX + (1.0f/BOARD_WIDTH), drawY + (2.0f/BOARD_HEIGHT));
            }
        }
    }
}

void Init(){
    board[0][0] = 1;
    board[1][0] = 2;
    board[2][0] = 3;
    board[3][0] = 4;
    board[4][0] = 5;
    board[5][0] = 6;
    board[6][0] = 7;
    glLineWidth(4);
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