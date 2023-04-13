#include <glad/glad.h>

#include "window.h"


namespace cbengine {
    Window::Window(const std::string& _title, int _width, int _height):
        _title(_title), _width(_width), _height(_height), _isOpen(false),
        _win(nullptr) {}

    Window::Window() {}

    Window::~Window() {
        glfwDestroyWindow(this->_win);
    }

    void Window::create() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__) || defined(__MACH__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__ || _MACH__
        this->_win = glfwCreateWindow(this->_width,
                                        this->_height,
                                        this->_title.c_str(),
                                        nullptr,
                                        nullptr);
        if(!this->_win) {
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwSetWindowSizeCallback(this->_win, &this->onSizeChange);
        glfwSetFramebufferSizeCallback(this->_win,
                                        &this->onFrameBufferSizeChange);
        glfwMakeContextCurrent(this->_win);
        this->_isOpen = true;
    }

    void Window::destroy() {
        if(!this->_isOpen) return;

        glfwSetWindowShouldClose(this->_win, false);
        this->_isOpen = false;
    }

    bool Window::shouldClose() const {
        return glfwWindowShouldClose(this->_win);
    }

    void Window::setTitle(const std::string& _title) {
        this->_title = _title;
        glfwSetWindowTitle(this->_win, _title.c_str());
    }

    void Window::setSize(int _width, int _height) {
        this->_width = _width;
        this->_height = _height;
        glfwSetWindowSize(this->_win, _width, _height);
    }

    const std::string& Window::getTitle() const {
        return this->_title;
    }

    void Window::getSize(int* _width, int* _height) const {
        *_width = this->_width;
        *_height = this->_height;
    }

    GLFWwindow* Window::getWindow() const {
        return this->_win;
    }

    void Window::onSizeChange(GLFWwindow *_win, int _width, int _height) {
        (void) _height;
        // makes window size square
        glfwSetWindowSize(_win, _width, _width);
    }

    void Window::onFrameBufferSizeChange(GLFWwindow *_win,
                                            int _width,
                                            int _height) {
        (void) _win;
        glViewport(0, 0, _width, _height);
    }
}
