#pragma once

class GLFWwindow;

namespace Jewer2D {

    namespace Time {
        extern double unscaledDeltaTime, deltaTime, fixedDeltaTime, timeScale;
    }

    enum ERRORS {
        NULL_ON_TICK=-1,
        GLFW_FAIL_INIT=-2,
        GLFW_FAIL_CREATE_WINDOW=-3,
        NONE=0
    };


    extern void (*Tick)();
    extern void (*FixedTick)();
    extern void (*LateTick)();
    extern void (*Render)();
    extern float ratio;
    extern float borderR, borderG, borderB, borderA;
    extern float backgroundR, backgroundG, backgroundB, backgroundA;
    extern GLFWwindow *window;

    int Init(int width, int height, const char *title, void (*Tick)(), void (*FixedTick)(), void (*LateTick)(), void (*Render)());
    void BeginLoop();
};