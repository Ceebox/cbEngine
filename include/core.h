#ifndef CORE_H
#define CORE_H

///////////////////////////////////////////////
// Contains important core stuff for the engine
///////////////////////////////////////////////

#include "glad.h"
#include "glfw3.h"

typedef void (*StartFn) ();
typedef void (*UpdateFn) (float deltaTime);
typedef void (*FinishFn) ();

struct Core
{
    static GLFWwindow *window;
};

#endif
