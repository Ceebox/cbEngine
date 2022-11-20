#ifndef RENDERER_H
#define RENDERER_H

#include <cmath>
#include <iostream>
#include <fstream>

#include "core.h"

#include "input.h"
#include "pixel.h"

class Renderer
{
    public:
        int Init(void(&Start)(), void (&Update)(float deltaTime));
        void SetWindow(GLFWwindow *newWindow);

    private:
        GLFWwindow *window;

        struct StringToGL
        {
            const char *p;
            StringToGL(const std::string &s) : p(s.c_str()) {}
            operator const char **() { return &p; }
        };
};

Pixel GetPixel(int x, int y);
void SetPixel(int x, int y, Pixel pixel);
void SetPixel(int x, int y, uint_fast8_t r, uint_fast8_t g, uint_fast8_t b);
void FillScreen(Pixel pixel);
void FillScreen(uint_fast8_t r, uint_fast8_t g, uint_fast8_t b);

int GetWindowHeight();
int GetWindowWidth();

void OnWindowChanged(GLFWwindow *window, int width, int height);

#endif