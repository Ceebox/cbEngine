#include <GLFW/glfw3.h>

#include "app.h"


namespace cbengine {
    App::App():
        _win("CBEngine", 800, 800) {
        if(!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
    }

    App::~App() {
        glfwTerminate();
    }
}
