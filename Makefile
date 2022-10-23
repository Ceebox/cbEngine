libraryTest:
	g++ -c ./src/engine.cpp -O3 -Wall -Wno-missing-braces -I ./include/glad/ -I ./include/KHR/ -I ./include/GLFW/ -I ./include/ -L ./lib/ -lglfw3 -lglad -lopengl32 -lgdi32 -lwinmm

default:
	g++ ./src/*.cpp ./src/*.c -o game.exe -O3 -Wall -Wno-missing-braces -I ./include/glad/ -I ./include/KHR/ -I ./include/GLFW/ -I ./include/ -L ./lib/ -lglfw3 -lglad -lopengl32 -lgdi32 -lwinmm