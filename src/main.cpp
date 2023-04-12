#include "engine.h"

//Called before the first update
void Start()
{
    std::cout << "Start" << std::endl;

    SetVsync(false);

    SetPixel(1, 1, 255, 255, 255);
    SetPixel(64, 64, 255, 255, 255);

    Pixel pixel = GetPixel(1, 1);
    std::cout << pixel.r << std::endl; //255
}

//Called every frame
void Update(float deltaTime)
{
    std::cout << 1 / deltaTime << std::endl;

    if (IsKeyPressed(KEY_SPACE))
    {
        std::cout << "Pressed" << std::endl;
    }
}

//Called once the window has closed
void Finish()
{
    std::cout << "Finish" << std::endl;
}

//Init the engine here
int main()
{
    InitWindow(&Start, &Update, &Finish);
   
    return 0;
}
