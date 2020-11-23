# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dmitry/Courseproject-Modelling-road-traffic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmitry/Courseproject-Modelling-road-traffic

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dmitry/Courseproject-Modelling-road-traffic/CMakeFiles /home/dmitry/Courseproject-Modelling-road-traffic/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dmitry/Courseproject-Modelling-road-traffic/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

src/MDLParser.o: src/MDLParser.cpp.o

.PHONY : src/MDLParser.o

# target to build an object file
src/MDLParser.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/MDLParser.cpp.o
.PHONY : src/MDLParser.cpp.o

src/MDLParser.i: src/MDLParser.cpp.i

.PHONY : src/MDLParser.i

# target to preprocess a source file
src/MDLParser.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/MDLParser.cpp.i
.PHONY : src/MDLParser.cpp.i

src/MDLParser.s: src/MDLParser.cpp.s

.PHONY : src/MDLParser.s

# target to generate assembly for a file
src/MDLParser.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/MDLParser.cpp.s
.PHONY : src/MDLParser.cpp.s

src/ModelApplication.o: src/ModelApplication.cpp.o

.PHONY : src/ModelApplication.o

# target to build an object file
src/ModelApplication.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/ModelApplication.cpp.o
.PHONY : src/ModelApplication.cpp.o

src/ModelApplication.i: src/ModelApplication.cpp.i

.PHONY : src/ModelApplication.i

# target to preprocess a source file
src/ModelApplication.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/ModelApplication.cpp.i
.PHONY : src/ModelApplication.cpp.i

src/ModelApplication.s: src/ModelApplication.cpp.s

.PHONY : src/ModelApplication.s

# target to generate assembly for a file
src/ModelApplication.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/ModelApplication.cpp.s
.PHONY : src/ModelApplication.cpp.s

src/OpenglLayer.o: src/OpenglLayer.cpp.o

.PHONY : src/OpenglLayer.o

# target to build an object file
src/OpenglLayer.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/OpenglLayer.cpp.o
.PHONY : src/OpenglLayer.cpp.o

src/OpenglLayer.i: src/OpenglLayer.cpp.i

.PHONY : src/OpenglLayer.i

# target to preprocess a source file
src/OpenglLayer.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/OpenglLayer.cpp.i
.PHONY : src/OpenglLayer.cpp.i

src/OpenglLayer.s: src/OpenglLayer.cpp.s

.PHONY : src/OpenglLayer.s

# target to generate assembly for a file
src/OpenglLayer.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/OpenglLayer.cpp.s
.PHONY : src/OpenglLayer.cpp.s

src/core/Car.o: src/core/Car.cpp.o

.PHONY : src/core/Car.o

# target to build an object file
src/core/Car.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Car.cpp.o
.PHONY : src/core/Car.cpp.o

src/core/Car.i: src/core/Car.cpp.i

.PHONY : src/core/Car.i

# target to preprocess a source file
src/core/Car.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Car.cpp.i
.PHONY : src/core/Car.cpp.i

src/core/Car.s: src/core/Car.cpp.s

.PHONY : src/core/Car.s

# target to generate assembly for a file
src/core/Car.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Car.cpp.s
.PHONY : src/core/Car.cpp.s

src/core/ForceGenerator.o: src/core/ForceGenerator.cpp.o

.PHONY : src/core/ForceGenerator.o

# target to build an object file
src/core/ForceGenerator.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/ForceGenerator.cpp.o
.PHONY : src/core/ForceGenerator.cpp.o

src/core/ForceGenerator.i: src/core/ForceGenerator.cpp.i

.PHONY : src/core/ForceGenerator.i

# target to preprocess a source file
src/core/ForceGenerator.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/ForceGenerator.cpp.i
.PHONY : src/core/ForceGenerator.cpp.i

src/core/ForceGenerator.s: src/core/ForceGenerator.cpp.s

.PHONY : src/core/ForceGenerator.s

# target to generate assembly for a file
src/core/ForceGenerator.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/ForceGenerator.cpp.s
.PHONY : src/core/ForceGenerator.cpp.s

src/core/Particle.o: src/core/Particle.cpp.o

.PHONY : src/core/Particle.o

# target to build an object file
src/core/Particle.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Particle.cpp.o
.PHONY : src/core/Particle.cpp.o

src/core/Particle.i: src/core/Particle.cpp.i

.PHONY : src/core/Particle.i

# target to preprocess a source file
src/core/Particle.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Particle.cpp.i
.PHONY : src/core/Particle.cpp.i

src/core/Particle.s: src/core/Particle.cpp.s

.PHONY : src/core/Particle.s

# target to generate assembly for a file
src/core/Particle.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Particle.cpp.s
.PHONY : src/core/Particle.cpp.s

src/core/Road.o: src/core/Road.cpp.o

.PHONY : src/core/Road.o

# target to build an object file
src/core/Road.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Road.cpp.o
.PHONY : src/core/Road.cpp.o

src/core/Road.i: src/core/Road.cpp.i

.PHONY : src/core/Road.i

# target to preprocess a source file
src/core/Road.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Road.cpp.i
.PHONY : src/core/Road.cpp.i

src/core/Road.s: src/core/Road.cpp.s

.PHONY : src/core/Road.s

# target to generate assembly for a file
src/core/Road.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Road.cpp.s
.PHONY : src/core/Road.cpp.s

src/core/Vector.o: src/core/Vector.cpp.o

.PHONY : src/core/Vector.o

# target to build an object file
src/core/Vector.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Vector.cpp.o
.PHONY : src/core/Vector.cpp.o

src/core/Vector.i: src/core/Vector.cpp.i

.PHONY : src/core/Vector.i

# target to preprocess a source file
src/core/Vector.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Vector.cpp.i
.PHONY : src/core/Vector.cpp.i

src/core/Vector.s: src/core/Vector.cpp.s

.PHONY : src/core/Vector.s

# target to generate assembly for a file
src/core/Vector.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/core/Vector.cpp.s
.PHONY : src/core/Vector.cpp.s

src/glfw/Window.o: src/glfw/Window.cpp.o

.PHONY : src/glfw/Window.o

# target to build an object file
src/glfw/Window.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/glfw/Window.cpp.o
.PHONY : src/glfw/Window.cpp.o

src/glfw/Window.i: src/glfw/Window.cpp.i

.PHONY : src/glfw/Window.i

# target to preprocess a source file
src/glfw/Window.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/glfw/Window.cpp.i
.PHONY : src/glfw/Window.cpp.i

src/glfw/Window.s: src/glfw/Window.cpp.s

.PHONY : src/glfw/Window.s

# target to generate assembly for a file
src/glfw/Window.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/glfw/Window.cpp.s
.PHONY : src/glfw/Window.cpp.s

src/imgui/ImguiLayer.o: src/imgui/ImguiLayer.cpp.o

.PHONY : src/imgui/ImguiLayer.o

# target to build an object file
src/imgui/ImguiLayer.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/imgui/ImguiLayer.cpp.o
.PHONY : src/imgui/ImguiLayer.cpp.o

src/imgui/ImguiLayer.i: src/imgui/ImguiLayer.cpp.i

.PHONY : src/imgui/ImguiLayer.i

# target to preprocess a source file
src/imgui/ImguiLayer.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/imgui/ImguiLayer.cpp.i
.PHONY : src/imgui/ImguiLayer.cpp.i

src/imgui/ImguiLayer.s: src/imgui/ImguiLayer.cpp.s

.PHONY : src/imgui/ImguiLayer.s

# target to generate assembly for a file
src/imgui/ImguiLayer.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/imgui/ImguiLayer.cpp.s
.PHONY : src/imgui/ImguiLayer.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/opengl/Buffer.o: src/opengl/Buffer.cpp.o

.PHONY : src/opengl/Buffer.o

# target to build an object file
src/opengl/Buffer.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Buffer.cpp.o
.PHONY : src/opengl/Buffer.cpp.o

src/opengl/Buffer.i: src/opengl/Buffer.cpp.i

.PHONY : src/opengl/Buffer.i

# target to preprocess a source file
src/opengl/Buffer.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Buffer.cpp.i
.PHONY : src/opengl/Buffer.cpp.i

src/opengl/Buffer.s: src/opengl/Buffer.cpp.s

.PHONY : src/opengl/Buffer.s

# target to generate assembly for a file
src/opengl/Buffer.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Buffer.cpp.s
.PHONY : src/opengl/Buffer.cpp.s

src/opengl/OrtographicCamera.o: src/opengl/OrtographicCamera.cpp.o

.PHONY : src/opengl/OrtographicCamera.o

# target to build an object file
src/opengl/OrtographicCamera.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/OrtographicCamera.cpp.o
.PHONY : src/opengl/OrtographicCamera.cpp.o

src/opengl/OrtographicCamera.i: src/opengl/OrtographicCamera.cpp.i

.PHONY : src/opengl/OrtographicCamera.i

# target to preprocess a source file
src/opengl/OrtographicCamera.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/OrtographicCamera.cpp.i
.PHONY : src/opengl/OrtographicCamera.cpp.i

src/opengl/OrtographicCamera.s: src/opengl/OrtographicCamera.cpp.s

.PHONY : src/opengl/OrtographicCamera.s

# target to generate assembly for a file
src/opengl/OrtographicCamera.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/OrtographicCamera.cpp.s
.PHONY : src/opengl/OrtographicCamera.cpp.s

src/opengl/Renderer.o: src/opengl/Renderer.cpp.o

.PHONY : src/opengl/Renderer.o

# target to build an object file
src/opengl/Renderer.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Renderer.cpp.o
.PHONY : src/opengl/Renderer.cpp.o

src/opengl/Renderer.i: src/opengl/Renderer.cpp.i

.PHONY : src/opengl/Renderer.i

# target to preprocess a source file
src/opengl/Renderer.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Renderer.cpp.i
.PHONY : src/opengl/Renderer.cpp.i

src/opengl/Renderer.s: src/opengl/Renderer.cpp.s

.PHONY : src/opengl/Renderer.s

# target to generate assembly for a file
src/opengl/Renderer.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Renderer.cpp.s
.PHONY : src/opengl/Renderer.cpp.s

src/opengl/Shader.o: src/opengl/Shader.cpp.o

.PHONY : src/opengl/Shader.o

# target to build an object file
src/opengl/Shader.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Shader.cpp.o
.PHONY : src/opengl/Shader.cpp.o

src/opengl/Shader.i: src/opengl/Shader.cpp.i

.PHONY : src/opengl/Shader.i

# target to preprocess a source file
src/opengl/Shader.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Shader.cpp.i
.PHONY : src/opengl/Shader.cpp.i

src/opengl/Shader.s: src/opengl/Shader.cpp.s

.PHONY : src/opengl/Shader.s

# target to generate assembly for a file
src/opengl/Shader.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Shader.cpp.s
.PHONY : src/opengl/Shader.cpp.s

src/opengl/Texture.o: src/opengl/Texture.cpp.o

.PHONY : src/opengl/Texture.o

# target to build an object file
src/opengl/Texture.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Texture.cpp.o
.PHONY : src/opengl/Texture.cpp.o

src/opengl/Texture.i: src/opengl/Texture.cpp.i

.PHONY : src/opengl/Texture.i

# target to preprocess a source file
src/opengl/Texture.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Texture.cpp.i
.PHONY : src/opengl/Texture.cpp.i

src/opengl/Texture.s: src/opengl/Texture.cpp.s

.PHONY : src/opengl/Texture.s

# target to generate assembly for a file
src/opengl/Texture.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/Texture.cpp.s
.PHONY : src/opengl/Texture.cpp.s

src/opengl/VertexArray.o: src/opengl/VertexArray.cpp.o

.PHONY : src/opengl/VertexArray.o

# target to build an object file
src/opengl/VertexArray.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/VertexArray.cpp.o
.PHONY : src/opengl/VertexArray.cpp.o

src/opengl/VertexArray.i: src/opengl/VertexArray.cpp.i

.PHONY : src/opengl/VertexArray.i

# target to preprocess a source file
src/opengl/VertexArray.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/VertexArray.cpp.i
.PHONY : src/opengl/VertexArray.cpp.i

src/opengl/VertexArray.s: src/opengl/VertexArray.cpp.s

.PHONY : src/opengl/VertexArray.s

# target to generate assembly for a file
src/opengl/VertexArray.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/VertexArray.cpp.s
.PHONY : src/opengl/VertexArray.cpp.s

src/opengl/debug.o: src/opengl/debug.cpp.o

.PHONY : src/opengl/debug.o

# target to build an object file
src/opengl/debug.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/debug.cpp.o
.PHONY : src/opengl/debug.cpp.o

src/opengl/debug.i: src/opengl/debug.cpp.i

.PHONY : src/opengl/debug.i

# target to preprocess a source file
src/opengl/debug.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/debug.cpp.i
.PHONY : src/opengl/debug.cpp.i

src/opengl/debug.s: src/opengl/debug.cpp.s

.PHONY : src/opengl/debug.s

# target to generate assembly for a file
src/opengl/debug.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/opengl/debug.cpp.s
.PHONY : src/opengl/debug.cpp.s

src/vendor/imgui/imgui.o: src/vendor/imgui/imgui.cpp.o

.PHONY : src/vendor/imgui/imgui.o

# target to build an object file
src/vendor/imgui/imgui.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui.cpp.o
.PHONY : src/vendor/imgui/imgui.cpp.o

src/vendor/imgui/imgui.i: src/vendor/imgui/imgui.cpp.i

.PHONY : src/vendor/imgui/imgui.i

# target to preprocess a source file
src/vendor/imgui/imgui.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui.cpp.i
.PHONY : src/vendor/imgui/imgui.cpp.i

src/vendor/imgui/imgui.s: src/vendor/imgui/imgui.cpp.s

.PHONY : src/vendor/imgui/imgui.s

# target to generate assembly for a file
src/vendor/imgui/imgui.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui.cpp.s
.PHONY : src/vendor/imgui/imgui.cpp.s

src/vendor/imgui/imgui_demo.o: src/vendor/imgui/imgui_demo.cpp.o

.PHONY : src/vendor/imgui/imgui_demo.o

# target to build an object file
src/vendor/imgui/imgui_demo.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_demo.cpp.o
.PHONY : src/vendor/imgui/imgui_demo.cpp.o

src/vendor/imgui/imgui_demo.i: src/vendor/imgui/imgui_demo.cpp.i

.PHONY : src/vendor/imgui/imgui_demo.i

# target to preprocess a source file
src/vendor/imgui/imgui_demo.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_demo.cpp.i
.PHONY : src/vendor/imgui/imgui_demo.cpp.i

src/vendor/imgui/imgui_demo.s: src/vendor/imgui/imgui_demo.cpp.s

.PHONY : src/vendor/imgui/imgui_demo.s

# target to generate assembly for a file
src/vendor/imgui/imgui_demo.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_demo.cpp.s
.PHONY : src/vendor/imgui/imgui_demo.cpp.s

src/vendor/imgui/imgui_draw.o: src/vendor/imgui/imgui_draw.cpp.o

.PHONY : src/vendor/imgui/imgui_draw.o

# target to build an object file
src/vendor/imgui/imgui_draw.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_draw.cpp.o
.PHONY : src/vendor/imgui/imgui_draw.cpp.o

src/vendor/imgui/imgui_draw.i: src/vendor/imgui/imgui_draw.cpp.i

.PHONY : src/vendor/imgui/imgui_draw.i

# target to preprocess a source file
src/vendor/imgui/imgui_draw.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_draw.cpp.i
.PHONY : src/vendor/imgui/imgui_draw.cpp.i

src/vendor/imgui/imgui_draw.s: src/vendor/imgui/imgui_draw.cpp.s

.PHONY : src/vendor/imgui/imgui_draw.s

# target to generate assembly for a file
src/vendor/imgui/imgui_draw.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_draw.cpp.s
.PHONY : src/vendor/imgui/imgui_draw.cpp.s

src/vendor/imgui/imgui_impl_glfw.o: src/vendor/imgui/imgui_impl_glfw.cpp.o

.PHONY : src/vendor/imgui/imgui_impl_glfw.o

# target to build an object file
src/vendor/imgui/imgui_impl_glfw.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_impl_glfw.cpp.o
.PHONY : src/vendor/imgui/imgui_impl_glfw.cpp.o

src/vendor/imgui/imgui_impl_glfw.i: src/vendor/imgui/imgui_impl_glfw.cpp.i

.PHONY : src/vendor/imgui/imgui_impl_glfw.i

# target to preprocess a source file
src/vendor/imgui/imgui_impl_glfw.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_impl_glfw.cpp.i
.PHONY : src/vendor/imgui/imgui_impl_glfw.cpp.i

src/vendor/imgui/imgui_impl_glfw.s: src/vendor/imgui/imgui_impl_glfw.cpp.s

.PHONY : src/vendor/imgui/imgui_impl_glfw.s

# target to generate assembly for a file
src/vendor/imgui/imgui_impl_glfw.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_impl_glfw.cpp.s
.PHONY : src/vendor/imgui/imgui_impl_glfw.cpp.s

src/vendor/imgui/imgui_impl_opengl3.o: src/vendor/imgui/imgui_impl_opengl3.cpp.o

.PHONY : src/vendor/imgui/imgui_impl_opengl3.o

# target to build an object file
src/vendor/imgui/imgui_impl_opengl3.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.o
.PHONY : src/vendor/imgui/imgui_impl_opengl3.cpp.o

src/vendor/imgui/imgui_impl_opengl3.i: src/vendor/imgui/imgui_impl_opengl3.cpp.i

.PHONY : src/vendor/imgui/imgui_impl_opengl3.i

# target to preprocess a source file
src/vendor/imgui/imgui_impl_opengl3.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.i
.PHONY : src/vendor/imgui/imgui_impl_opengl3.cpp.i

src/vendor/imgui/imgui_impl_opengl3.s: src/vendor/imgui/imgui_impl_opengl3.cpp.s

.PHONY : src/vendor/imgui/imgui_impl_opengl3.s

# target to generate assembly for a file
src/vendor/imgui/imgui_impl_opengl3.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_impl_opengl3.cpp.s
.PHONY : src/vendor/imgui/imgui_impl_opengl3.cpp.s

src/vendor/imgui/imgui_widgets.o: src/vendor/imgui/imgui_widgets.cpp.o

.PHONY : src/vendor/imgui/imgui_widgets.o

# target to build an object file
src/vendor/imgui/imgui_widgets.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_widgets.cpp.o
.PHONY : src/vendor/imgui/imgui_widgets.cpp.o

src/vendor/imgui/imgui_widgets.i: src/vendor/imgui/imgui_widgets.cpp.i

.PHONY : src/vendor/imgui/imgui_widgets.i

# target to preprocess a source file
src/vendor/imgui/imgui_widgets.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_widgets.cpp.i
.PHONY : src/vendor/imgui/imgui_widgets.cpp.i

src/vendor/imgui/imgui_widgets.s: src/vendor/imgui/imgui_widgets.cpp.s

.PHONY : src/vendor/imgui/imgui_widgets.s

# target to generate assembly for a file
src/vendor/imgui/imgui_widgets.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/imgui/imgui_widgets.cpp.s
.PHONY : src/vendor/imgui/imgui_widgets.cpp.s

src/vendor/stb_image/stb_image.o: src/vendor/stb_image/stb_image.cpp.o

.PHONY : src/vendor/stb_image/stb_image.o

# target to build an object file
src/vendor/stb_image/stb_image.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/stb_image/stb_image.cpp.o
.PHONY : src/vendor/stb_image/stb_image.cpp.o

src/vendor/stb_image/stb_image.i: src/vendor/stb_image/stb_image.cpp.i

.PHONY : src/vendor/stb_image/stb_image.i

# target to preprocess a source file
src/vendor/stb_image/stb_image.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/stb_image/stb_image.cpp.i
.PHONY : src/vendor/stb_image/stb_image.cpp.i

src/vendor/stb_image/stb_image.s: src/vendor/stb_image/stb_image.cpp.s

.PHONY : src/vendor/stb_image/stb_image.s

# target to generate assembly for a file
src/vendor/stb_image/stb_image.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/src/vendor/stb_image/stb_image.cpp.s
.PHONY : src/vendor/stb_image/stb_image.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... main"
	@echo "... src/MDLParser.o"
	@echo "... src/MDLParser.i"
	@echo "... src/MDLParser.s"
	@echo "... src/ModelApplication.o"
	@echo "... src/ModelApplication.i"
	@echo "... src/ModelApplication.s"
	@echo "... src/OpenglLayer.o"
	@echo "... src/OpenglLayer.i"
	@echo "... src/OpenglLayer.s"
	@echo "... src/core/Car.o"
	@echo "... src/core/Car.i"
	@echo "... src/core/Car.s"
	@echo "... src/core/ForceGenerator.o"
	@echo "... src/core/ForceGenerator.i"
	@echo "... src/core/ForceGenerator.s"
	@echo "... src/core/Particle.o"
	@echo "... src/core/Particle.i"
	@echo "... src/core/Particle.s"
	@echo "... src/core/Road.o"
	@echo "... src/core/Road.i"
	@echo "... src/core/Road.s"
	@echo "... src/core/Vector.o"
	@echo "... src/core/Vector.i"
	@echo "... src/core/Vector.s"
	@echo "... src/glfw/Window.o"
	@echo "... src/glfw/Window.i"
	@echo "... src/glfw/Window.s"
	@echo "... src/imgui/ImguiLayer.o"
	@echo "... src/imgui/ImguiLayer.i"
	@echo "... src/imgui/ImguiLayer.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/opengl/Buffer.o"
	@echo "... src/opengl/Buffer.i"
	@echo "... src/opengl/Buffer.s"
	@echo "... src/opengl/OrtographicCamera.o"
	@echo "... src/opengl/OrtographicCamera.i"
	@echo "... src/opengl/OrtographicCamera.s"
	@echo "... src/opengl/Renderer.o"
	@echo "... src/opengl/Renderer.i"
	@echo "... src/opengl/Renderer.s"
	@echo "... src/opengl/Shader.o"
	@echo "... src/opengl/Shader.i"
	@echo "... src/opengl/Shader.s"
	@echo "... src/opengl/Texture.o"
	@echo "... src/opengl/Texture.i"
	@echo "... src/opengl/Texture.s"
	@echo "... src/opengl/VertexArray.o"
	@echo "... src/opengl/VertexArray.i"
	@echo "... src/opengl/VertexArray.s"
	@echo "... src/opengl/debug.o"
	@echo "... src/opengl/debug.i"
	@echo "... src/opengl/debug.s"
	@echo "... src/vendor/imgui/imgui.o"
	@echo "... src/vendor/imgui/imgui.i"
	@echo "... src/vendor/imgui/imgui.s"
	@echo "... src/vendor/imgui/imgui_demo.o"
	@echo "... src/vendor/imgui/imgui_demo.i"
	@echo "... src/vendor/imgui/imgui_demo.s"
	@echo "... src/vendor/imgui/imgui_draw.o"
	@echo "... src/vendor/imgui/imgui_draw.i"
	@echo "... src/vendor/imgui/imgui_draw.s"
	@echo "... src/vendor/imgui/imgui_impl_glfw.o"
	@echo "... src/vendor/imgui/imgui_impl_glfw.i"
	@echo "... src/vendor/imgui/imgui_impl_glfw.s"
	@echo "... src/vendor/imgui/imgui_impl_opengl3.o"
	@echo "... src/vendor/imgui/imgui_impl_opengl3.i"
	@echo "... src/vendor/imgui/imgui_impl_opengl3.s"
	@echo "... src/vendor/imgui/imgui_widgets.o"
	@echo "... src/vendor/imgui/imgui_widgets.i"
	@echo "... src/vendor/imgui/imgui_widgets.s"
	@echo "... src/vendor/stb_image/stb_image.o"
	@echo "... src/vendor/stb_image/stb_image.i"
	@echo "... src/vendor/stb_image/stb_image.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

