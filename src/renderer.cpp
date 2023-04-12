#include "renderer.h"

#define WIDTH 64
#define HEIGHT 64

const int windowWidth = WIDTH;
const int windowHeight = HEIGHT;

GLFWwindow* Core::window;

//The main pixel array
GLubyte pixels[WIDTH * HEIGHT * 3]; // Array size is width * height * 3 (1 byte per channel)

int Renderer::Init(void (&Start)() ,void (&Update)(float deltaTime))
{
    // Set up the main window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a main window object
    window = glfwCreateWindow(800, 800, "CbEngine", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, OnWindowChanged);

    //Set input window so the rest of the engine can access it
    Core::window = window;

    // Initialise GLAD and load all function pointers
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Generate shaders
    const char *vertexSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec3 aColor;\n"
        "layout(location = 2) in vec2 aTexCoord;\n"
        "out vec3 ourColor;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos, 1.0);\n"
        "    TexCoord = aTexCoord;\n"
        "}\n";

    const char *fragSource =
        "#version 330 core \n"
        "out vec4 FragColor; \n"
        "in vec3 ourColor; \n"
        "in vec2 TexCoord; \n"
        "uniform sampler2D ourTexture; \n"
        "void main() \n"
        "{\n"
        "  FragColor = texture(ourTexture, TexCoord);\n"
        "}\n";

    // Define vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Compile the shader
    glShaderSource(vertexShader, 1, Renderer::StringToGL(vertexSource), NULL);
    glCompileShader(vertexShader);

    // Define fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Compile fragment shader
    glShaderSource(fragmentShader, 1, StringToGL(fragSource), NULL);
    glCompileShader(fragmentShader);

    // Create a shader program to combine the fragment and the vertex shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    // Link shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete no longer needed shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Vertex buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                            (void *)0);
    glEnableVertexAttribArray(0);

    // Assign verticies
    float vertices[] = {
        // positions // colors // texture coords
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first Triangle
        1, 2, 3, // second Triangle
    };

    // Generate objects
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //Set up main texture that is rendered
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Call the start function now everything is initialised 
    Start();

    // Time variables
    float lastTime = 0.0f;
    float deltaTime = 0.0f;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        if (window != NULL)
        {
            Update(deltaTime);
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();
    }

    // De-allocate rescources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void Renderer::SetWindow(GLFWwindow *newWindow)
{
    window = newWindow;
}

// Returns pixel information from a given co-ordinate
Pixel GetPixel(int x, int y)
{
    Pixel pixel = Pixel(0, 0, 0);

    int pixelIndex = ((y * windowHeight) + (x - windowWidth - 1)) * 3;

    pixel.r = (int)pixels[pixelIndex];
    pixel.g = (int)pixels[pixelIndex + 1];
    pixel.b = (int)pixels[pixelIndex + 2];

    return pixel; // Return blank
}

//Sets pixel on texture based on co-ordinates
void SetPixel(int x, int y, uint_fast8_t r, uint_fast8_t g, uint_fast8_t b)
{
    if (x > windowWidth || y > windowHeight)
    {
        return;
    }

    uint_fast32_t pixelIndex = ((y * windowHeight) + (x - windowWidth - 1)) * 3;

    pixels[pixelIndex] = r;
    pixels[pixelIndex + 1] = g;
    pixels[pixelIndex + 2] = b;
}

void SetPixel(int x, int y, Pixel pixel)
{
    SetPixel(x, y, pixel.r, pixel.g, pixel.b);
}

void FillScreen(uint_fast8_t r, uint_fast8_t g, uint_fast8_t b)
{
    for (u_int64_t i = 0; i < sizeof(pixels); i+= 3)
    {
        pixels[i] = r;
        pixels[i + 1] = g;
        pixels[i + 2] = b;
    }
}

void FillScreen(Pixel pixel)
{
    FillScreen(pixel.r, pixel.g, pixel.b);
}

// glfw does not accept member classes
void OnWindowChanged(GLFWwindow *window, int width, int height)
{
    width = height; // Force screen to be square
    glfwSetWindowSize(window, width, height);

    glViewport(0, 0, width, height);
}
