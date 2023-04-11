SOURCES = src/engine.cpp src/input.cpp src/pixel.cpp src/renderer.cpp src/glad.c
LIBTEST_SOURCES = src/main.cpp

CXX_FLAGS = -O3 -Wall -Wno-missing-braces -I ./include/glad/ -I ./include/

ifeq ($(OS),Windows_NT)
	# Windows specific compile flags
	CXX_FLAGS += -I ./include/KHR/ -I ./include/GLFW/ -lopengl32 -lgdi32 -lwinmm -L ./lib/
else
	CXX_FLAGS += -lGL -lX11 -ldl
endif

CXX_FLAGS += -lglfw -lglad

test: lib
	g++ $(CXX_FLAGS) $(LIBTEST_SOURCES) libcbengine.a -o cbenginetest

lib:
	g++ -c -fPIC $(SOURCES) $(CXX_FLAGS)
	ar rcs libcbengine.a *.o
	rm *.o


