#include <glad/glad.h>
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

    void App::run() {
        this->_win.create();
        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        while(!this->_win.shouldClose()) {
            glfwSwapBuffers(this->_win.getWindow());
            glfwPollEvents();
        }
    }
}
