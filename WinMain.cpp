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
    {1.0f, 0.4f, 0.2f}
};
const Pattern PATTERNS[7] = {Pattern(0, Patterns::SQUARE_ORIENTATION), Pattern(1, Patterns::LINE_ORIENTATION), Pattern(2, Patterns::T_ORIENTATION), Pattern(3, Patterns::L_ORIENTATION), Pattern(4, Patterns::RL_ORIENTATION), Pattern(5, Patterns::S_ORIENTATION), Pattern(6, Patterns::Z_ORIENTATION)};
const float BOARD_Y_UNIT (2.0f/BOARD_HEIGHT);
const float BOARD_X_UNIT (1.0f/BOARD_WIDTH);

int board[BOARD_WIDTH][BOARD_HEIGHT] = {0};
bool fast = false;

Pattern active = PATTERNS[0];
int activePos[2] = {4,20};

int ticks = 0;
int speed = 30;

float GetBoardX(int boardX){
    return (boardX/(float)BOARD_WIDTH) - 0.5;
}
float GetBoardY(int boardY){
    return (boardY/(float)BOARD_HEIGHT)*2 - 1;
}

void Tick() {
    
}

void FixedTick() {
    if(ticks%speed == 0 || (fast && ticks%(speed/6) == 0)){
        bool testBelow = false;
        for(int i = 0; i < 4; i++){
            if(board[activePos[0] + active.pattern[active.rotation][i][0]][activePos[1] + active.pattern[active.rotation][i][1] - 1] != 0 || activePos[1] + active.pattern[active.rotation][i][1] <= 0){
                testBelow = true;
                break;
            }
        }
        if(testBelow){
            //set the squares in place on the board
            for(int i = 0; i < 4; i++){
                board[activePos[0] + active.pattern[active.rotation][i][0]][activePos[1] + active.pattern[active.rotation][i][1]] = active.colour + 1;
            }

            for(int i = activePos[1] + active.maxY; i >= activePos[1] + active.minY; i--){
                std::cout << "dick" << std::endl;
                bool allFull = true;
                for(int n = 0; n < BOARD_WIDTH; n++){//check if the row is full at this y value
                    if(board[n][i] == 0){
                        allFull = false;
                        break;
                    }
                }
            
                if(allFull){
                    for(int y = i; y < BOARD_HEIGHT - 1; y++){
                        for(int n = 0; n < BOARD_WIDTH; n++){
                            board[n][y] = board[n][y + 1];
                        }
                    }
                }
            }
            //reset active to new random and to the top
            active = PATTERNS[rand()%7];
            activePos[0] = 4;
            activePos[1] = 20;
        }
        activePos[1]--;
    }
    ticks++;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if((key == GLFW_KEY_D && action == GLFW_PRESS) && activePos[0] + active.minX + (active.maxX - active.minX) < BOARD_WIDTH - 1){
        bool testRight = false;
        for(int i = 0; i < 4; i++){
            if(board[activePos[0] + active.pattern[active.rotation][i][0] + 1][activePos[1] + active.pattern[active.rotation][i][1]] != 0){
                testRight = true;
                break;
            }
        }
        if(!testRight)
            activePos[0]++;
    }
    if((key == GLFW_KEY_A && action == GLFW_PRESS)){
        bool testLeft = false;

        for(int i = 0; i < 4; i++){
            if(board[activePos[0] + active.pattern[active.rotation][i][0] - 1][activePos[1] + active.pattern[active.rotation][i][1]] != 0 || activePos[0] + active.pattern[active.rotation][i][0] <= 0){
                testLeft = true;
                break;
            }
        }

        if(!testLeft)
            activePos[0]--;
    }
    if(key == GLFW_KEY_W && action == GLFW_PRESS){
        bool canRotate = true;
        
        for(int i = 0; i < 4; i++){
            if(board[activePos[0] + active.pattern[active.rotation + 1 < 3?active.rotation + 1:0][i][0]][activePos[1] + active.pattern[active.rotation + 1 < 3?active.rotation + 1:0][i][1]] != 0 || activePos[0] + active.pattern[active.rotation + 1 < 3?active.rotation + 1:0][i][0] < 0 || activePos[0] + active.pattern[active.rotation + 1 < 3?active.rotation + 1:0][i][0] > BOARD_WIDTH){
                canRotate = false;
                break;
            }
        }

        if(canRotate)
            active.rotate();
    }
    if((key == GLFW_KEY_S && action == GLFW_PRESS) || (key == GLFW_KEY_S && action == GLFW_RELEASE)) fast = !fast;
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
        glRectf(GetBoardX(activePos[0] + active.pattern[active.rotation][i][0]), GetBoardY(activePos[1] + active.pattern[active.rotation][i][1]), GetBoardX(activePos[0] + active.pattern[active.rotation][i][0]) + BOARD_X_UNIT, GetBoardY(activePos[1] + active.pattern[active.rotation][i][1]) + BOARD_Y_UNIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(0.0f, 0.0f, 0.0f);
        glRectf(GetBoardX(activePos[0] + active.pattern[active.rotation][i][0]), GetBoardY(activePos[1] + active.pattern[active.rotation][i][1]), GetBoardX(activePos[0] + active.pattern[active.rotation][i][0]) + BOARD_X_UNIT, GetBoardY(activePos[1] + active.pattern[active.rotation][i][1]) + BOARD_Y_UNIT);
    }
}

void Init(){
    glLineWidth(4);
    
    srand (time(NULL));
    active = PATTERNS[rand()%7];
}


INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    Jewer2D::Init(640, 640, "Tetris", &Tick, &FixedTick, &LateTick, &Render);
    Jewer2D::backgroundR = 0.1f;
    Jewer2D::backgroundG = 0.1f;
    Jewer2D::backgroundB = 0.1f;

    glfwSetKeyCallback(Jewer2D::window, key_callback);

    Init();
    Jewer2D::BeginLoop();

    return 0;
}