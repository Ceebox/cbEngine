# cbEngine

### A small, experimental 64x64 pixel based game engine made using C++ and OpenGL.

#

## *Info*
cbEngine was inspired when I thought about creating a custom engine for [LowRezJam](https://itch.io/jam/lowrezjam-2022), I wanted it to be very simple and low level, in this case - literally just providing a graphics window and drawing a custom pixel array to the screen, along with a few other functions to improve usability.

cbEngine is not architectured very well - it was made over the course of a few days as I learnt OpenGL and more about C++. I intended to turn it into a C++ static library but have not gotten round to it - doing that would improve the workflow significantly.

To learn about OpenGL I used [LearnOpenGL](https://learnopengl.com/), a really useful tool for understanding the library. It also has instructions on how to install the required libraries - although I used MinGW for this project so some steps are slightly different.
#
##  *Getting Started*

To get the engine working correctly, there are some additional libraries that need to be installed.  

Requirements:
- [GLAD](https://glad.dav1d.de/) (GL 3.3 and KHR)
- [GLFW 3](https://www.glfw.org/)

Put the main glad.c file in the /src folder.

Place the library files in a folder called /lib - they should be called libglad.a, libglfw3.a and libglfw3dll.a.

Then place the header files in folders in the include directory.
Place the GLAD header in /include/glad/, then the GLFW one in GLFW include/GLFW/, then KHR in /include/KHR/.

Place the glfw3.dll file in the main folder, where the output .exe file will be located.

From there, to build the sample code simply run build.bat or the makefile on default.
#
## Sample Code

    #include "engine.h"
    
    //Called before the first update
    void Start()
    {
        std::cout << "Start" << std::endl;
    
        SetVsync(false);
    
        SetPixel(1, 1, 255, 255, 255);
        SetPixel(64, 64, 255, 255, 255);
          

	    Pixel  pixel  =  GetPixel(1,  1);
	    std::cout  <<  pixel.r  <<  std::endl; //255
	    
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
        InitWindow(Start, Update, Finish);
       
        return 0;
    }
