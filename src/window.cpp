#include "window.h"


namespace cbengine {
    Window::Window(const std::string& _title, int _width, int _height):
        _title(_title), _width(_width), _height(_height), _isOpen(false),
        _win(nullptr) {}

    Window::Window() {}

    Window::~Window() {
        glfwDestroyWindow(this->_win);
    }
}
