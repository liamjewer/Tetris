#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include <math.h>

namespace Jewer2D {

    namespace Time {
        double unscaledDeltaTime=0, deltaTime=0, fixedDeltaTime=0.016f, timeScale=1;
    }


    void (*Tick)();
    void (*FixedTick)();
    void (*LateTick)();
    void (*Render)();

    GLFWwindow *window;
    float ratio=1;
    float borderR=0, borderG=0, borderB=0, borderA=1;
    float backgroundR=0, backgroundG=0, backgroundB=0, backgroundA=1;

    void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        float fullRatio = (float)width / (float)height;
        float borderWidth=0, borderHeight=0;

        if (ratio > fullRatio) {
            // horizontal bars

            borderWidth = 0;
            borderHeight = (height - width/ratio) / 2.0f;
        } else {
            // vertical bars

            borderWidth = (width - height*ratio) / 2.0f;
            borderHeight = 0;
        }

        glViewport(borderWidth, height/2-(width-(borderWidth*2))/2, width-(borderWidth*2), width-(borderWidth*2));
        glScissor(borderWidth, borderHeight, width-(2*borderWidth), height-(2*borderHeight));
    }

    int Init(int width, int height, const char *title, void (*TickFuncPtr)(), void (*FixedTickFuncPtr)(), void (*LateTickFuncPtr)(), void (*RenderFuncPtr)()) {

        if(!TickFuncPtr || !FixedTickFuncPtr || !LateTickFuncPtr || !RenderFuncPtr) {
            return NULL_ON_TICK;
        } else {
            Tick = TickFuncPtr;
            FixedTick = FixedTickFuncPtr;
            LateTick = LateTickFuncPtr;
            Render = RenderFuncPtr;
        }
    
        /* Initialize the library */
        if (!glfwInit()) {
            return GLFW_FAIL_INIT;
        }

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window) {
            glfwTerminate();
            return GLFW_FAIL_CREATE_WINDOW;
        }
        
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        framebuffer_size_callback(window, width, height);
        
        return NONE;
    }

    void BeginLoop() {

        double previousTime = glfwGetTime();
        double currentTime;
        double previousPhysicsTime = glfwGetTime();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {

            /* Poll for and process events */
            glfwPollEvents();

            currentTime = glfwGetTime();
            Time::unscaledDeltaTime = currentTime-previousTime;
            Time::deltaTime = Time::unscaledDeltaTime*Time::timeScale;
            previousTime = glfwGetTime();

            Tick();

            for(int i=0; i<floor((currentTime-previousPhysicsTime)/Time::fixedDeltaTime*Time::timeScale); i++) {
                if(i==0) {
                    previousPhysicsTime = glfwGetTime();
                }
                FixedTick();
            }

            LateTick();

            glDisable(GL_SCISSOR_TEST);
            glClearColor(borderR, borderG, borderB, borderA);
            glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
            glEnable(GL_SCISSOR_TEST);
            glClearColor(backgroundR, backgroundG, backgroundB, backgroundA);
            glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

            Render();
            glfwSwapBuffers(Jewer2D::window);
        }

        glfwTerminate();

    }

}