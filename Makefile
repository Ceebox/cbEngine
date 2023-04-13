# directories
inc_dir := include
src_dir := src
bin_dir := bin
lib_dir := libs
s_dir := $(bin_dir)/static
d_dir := $(bin_dir)/dynamic

# files
headers := $(wildcard $(inc_dir)/*.h)
sources := $(wildcard $(src_dir)/*.cpp)
main := $(src_dir)/main.cpp
s_objects := $(patsubst $(src_dir)/%.cpp, $(s_dir)/%.o, $(filter-out $(main), $(sources)))
d_objects := $(patsubst $(src_dir)/%.cpp, $(d_dir)/%.o, $(filter-out $(main), $(sources)))
lib_ext =

# c++ compiler
cpp_compiler =
cpp_std = -std=c++11
cpp_opt = -O2
cpp_warn = -Wall -Wextra -pedantic
cpp_defs =
cpp_includes = -I$(inc_dir) -I$(lib_dir) -I$(inc_dir)/$(project_name)
cpp_ldflags = -L./$(bin_dir)
cpp_flags = $(cpp_std) $(cpp_opt) $(cpp_warn)

# c compiler
c_compiler =
c_std = -std=c11
c_opt = -O3
c_warn = -Wall -Wextra -pedantic
c_includes = -I$(inc_dir)
c_flags = $(c_std) $(c_opt) $(c_warn)

# platform specific variable stuff
os := $(shell uname -s)
platform =
project_ext =

ifeq ($(os), Darwin)
	platform = MACOS
	cpp_compiler = clang++
	cpp_flags += $(shell pkg-config --cflags glfw3)
	cpp_ldflags += $(shell pkg-config --static --libs glfw3)
	c_compiler = clang
	lib_ext = dylib
endif # Darwin
ifeq ($(os), Windows_NT)
	platform = WINDOWS
	cpp_compiler = g++
	cpp_ldflags += -lglfw3 -lopengl32 -lgdi32 -lwinmm
	c_compiler = gcc
	project_ext = .exe
	lib_ext = dll
endif # Windows_NT
ifeq ($(os), Linux)
	platform = LINUX
	cpp_compiler = g++
	cpp_flags += $(shell pkg-config --cflags glfw3)
	cpp_ldflags += $(shell pkg-config --static --libs glfw3)
	c_compiler = gcc
	lib_ext = so
endif # Linux

project_name := cbengine
project = $(project_name)$(project_ext)

# library files
s_lib := $(bin_dir)/lib$(project_name).a
d_lib := $(bin_dir)/lib$(project_name).$(lib_ext)


.PHONY: all clean static dynamic glad project
all:
	@$(MAKE) glad
	@$(MAKE) static
	@$(MAKE) dynamic
	@$(MAKE) project
clean:
	-rm -rf $(bin_dir) $(lib_dir)/*.o *.o *.a *.$(lib_ext)
static:
	@$(MAKE) $(s_lib)
dynamic:
	@$(MAKE) $(d_lib)
glad:
	@$(MAKE) $(lib_dir)/glad.o
project:
	@$(MAKE) $(project)

$(s_lib): $(headers) $(s_dir) $(s_objects) glad
	ar rv $@ $(s_objects) $(lib_dir)/glad.o

$(s_objects): $(s_dir)/%.o: $(src_dir)/%.cpp
	$(cpp_compiler) $(cpp_flags) $(cpp_includes) -c $< -o $@

$(d_lib): $(headers) $(d_dir) $(d_objects) glad
	$(cpp_compiler) $(cpp_flags) -shared $(cpp_includes) $(d_objects) $(lib_dir)/glad.o -o $@ $(cpp_ldflags)

$(d_objects): $(d_dir)/%.o: $(src_dir)/%.cpp
	$(cpp_compiler) $(cpp_flags) -fPIC $(cpp_includes) -c $< -o $@

$(lib_dir)/glad.o: $(lib_dir)/glad.c $(lib_dir)/glad/glad.h
	$(c_compiler) $(c_flags) -I$(lib_dir) -c $< -o $@

$(project): $(headers) $(sources) $(main) $(d_lib)
	$(cpp_compiler) $(cpp_flags) $(cpp_includes) $(main) -o $@ -L$(bin_dir) -l$(project_name) $(cpp_ldflags)

$(bin_dir):
	-@mkdir $@

$(s_dir): $(bin_dir)
	-@mkdir $@

$(d_dir): $(bin_dir)
	-mkdir $@
