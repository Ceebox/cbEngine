#ifndef CBENGINE_WINDOW_H
#define CBENGINE_WINDOW_H


#include <string>

#include <GLFW/glfw3.h>

#include "renderer.h"


namespace cbengine {
    class Window {
    public:
        Window(const std::string& _title, int _width, int _height);
        Window(const Window& _win) = delete;
        Window();
        ~Window();

        Window& operator =(const Window& _win) = delete;

        void create();
        void destroy();
        bool shouldClose() const;
        void setTitle(const std::string& _title);
        void setSize(int _width, int _height);
        const std::string& getTitle() const;
        void getSize(int* _width, int* _height) const;
        GLFWwindow* getWindow() const;
    private:
        static void onSizeChange(GLFWwindow *_win, int _width, int _height);
        static void onFrameBufferSizeChange(GLFWwindow *_win,
                                            int _width,
                                            int _height);
    private:
        std::string _title;
        int _width;
        int _height;
        bool _isOpen;
        GLFWwindow* _win;
    };
}

#endif // CBENGINE_WINDOW_H
