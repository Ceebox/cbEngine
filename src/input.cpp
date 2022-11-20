#include "input.h"

bool IsKeyPressed(int key)
{
    return (glfwGetKey(Core::window, key) == GLFW_PRESS);
}

bool IsKeyDown(int key)
{
    return (glfwGetKey(Core::window, key) == GLFW_REPEAT);
}