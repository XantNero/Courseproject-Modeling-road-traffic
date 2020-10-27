cmake_minimum_required(VERSION 3.16)

project(CourseWork)


add_executable(test
    src/test.cpp
    src/Vector.h src/Vector.cpp
    src/Road.h src/Road.cpp
    src/Car.h src/Car.cpp
    src/Particle.h src/Particle.cpp
    src/VertexBuffer.h src/VertexBuffer.cpp
    src/IndexBuffer.h src/IndexBuffer.cpp
    src/VertexBufferLayout.h src/VertexBufferLayout.cpp
    src/VertexArray.h src/VertexArray.cpp
    src/debug.h src/debug.cpp
    src/Shader.h src/Shader.cpp
    src/Renderer.h src/Renderer.cpp
    src/Texture.h src/Texture.cpp
    src/CarGenerator.h src/CarGenerator.cpp
    src/RoadRegistry.h src/RoadRegistry.cpp
    src/CarRegistry.h src/CarRegistry.cpp
    src/vendor/stb_image/stb_image.h src/vendor/stb_image/stb_image.cpp
    src/vendor/glm/glm.hpp src/vendor/glm/gtc/matrix_transform.hpp
    src/vendor/imgui/imconfig.h
    src/vendor/imgui/imgui_demo.cpp
    src/vendor/imgui/imgui_draw.cpp
    src/vendor/imgui/imgui_impl_opengl3.cpp
    src/vendor/imgui/imgui_impl_opengl3.h
    src/vendor/imgui/imgui_impl_glfw.cpp
    src/vendor/imgui/imgui_impl_glfw.h
    src/vendor/imgui/imgui_internal.h
    src/vendor/imgui/imgui_widgets.cpp
    src/vendor/imgui/imgui.cpp
    src/vendor/imgui/imgui.h
    src/vendor/imgui/imstb_rectpack.h
    src/vendor/imgui/imstb_textedit.h
    src/vendor/imgui/imstb_truetype.h
)

target_link_libraries(test -lglfw -lrt -lm -ldl -lGLEW -lGLU -lm -lGL)

set(CMAKE_CXX_FLAGS "-g")

