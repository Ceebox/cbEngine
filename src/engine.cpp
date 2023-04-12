#include "engine.h"

void InitWindow(StartFn start, UpdateFn update, FinishFn finish)
{
    Renderer renderer;
    renderer.Init(start, update);

    finish();
}

void SetTitle(std::string title)
{
    glfwSetWindowTitle(Core::window, title.c_str());
}

void SetWindowSize(int size)
{
    glfwSetWindowSize(Core::window, size, size);
}

void SetVsync(bool enabled)
{
    glfwSwapInterval(enabled);
}

void CloseWindow()
{
    glfwSetWindowShouldClose(Core::window, true);
}

double GetTime()
{
    return glfwGetTime();
}

std::string ReadFromFile(const char *pathToFile)
{
    std::ifstream input_file(pathToFile);
    if (!input_file.is_open())
    {
        std::cerr << "Could not open the file - '"
                  << pathToFile << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string output = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>()).data();
    input_file.close();

    return output;
}
