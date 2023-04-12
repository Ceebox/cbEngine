SOURCES = src/engine.cpp src/input.cpp src/pixel.cpp src/renderer.cpp src/glad.c
LIBTEST_SOURCES = src/main.cpp

LIB_OUT = libcbengine
LIB_EXT = .a
LIBTEST_OUT = cbenginetest
LIBTEST_EXT =

CXX_FLAGS = -O3 -Wall -Wno-missing-braces -I ./lib/ -I ./include/
CXX = g++

# Only use if not on Windows but you need to compile for Windows
ifdef TARGETWIN
	ifneq ($(OS),Windows_NT)
		OS = Windows_NT
		CXX = x86_64-w64-mingw32-g++
		CXX_FLAGS += -static -static-libgcc -static-libstdc++
	endif
endif

ifeq ($(OS),Windows_NT)
	# Windows specific compile flags
	CXX_FLAGS += -L ./lib/ -lglfw3 -lglfw3dll -lopengl32 -lgdi32 -lwinmm -luser32 -lkernel32
	LIB_EXT = .lib
	LIBTEST_EXT = .exe
else ifeq ($(OS),Darwin)
	CXX = clang++
	CXX_FLAGS += $$(pkg-config --cflags glfw3) $$(pkg-config --libs glfw3)
else
	CXX_FLAGS += $$(pkg-config --cflags glfw3) $$(pkg-config --libs glfw3)
endif

test: library
	$(CXX) $(LIBTEST_SOURCES) $(LIB_OUT)$(LIB_EXT) -o $(LIBTEST_OUT)$(LIBTEST_EXT) $(CXX_FLAGS)

library:
	$(CXX) -c -fPIC $(SOURCES) $(CXX_FLAGS)
	ar rcs $(LIB_OUT)$(LIB_EXT) *.o
	rm *.o
