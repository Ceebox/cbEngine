#ifndef CBENGINE_WINDOW_H
#define CBENGINE_WINDOW_H


#include <string>

#include <GLFW/glfw3.h>


namespace cbengine {
    class Window {
    public:
        Window(const std::string& _title, int _width, int _height);
        Window(const Window& _win) = delete;
        Window();
        ~Window();

        Window& operator =(const Window& _win) = delete;
    private:
        std::string _title;
        int _width;
        int _height;
        bool _isOpen;
        GLFWwindow* _win;
    };
}

#endif // CBENGINE_WINDOW_H
