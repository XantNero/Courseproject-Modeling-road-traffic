cmake_minimum_required(VERSION 3.16)

project(CourseWork)


add_executable(test
    src/main.cpp
    src/core/Vector.h src/core/Vector.cpp
    src/core/Road.h src/core/Road.cpp
    src/core/Car.h src/core/Car.cpp
    src/core/ForceGenerator.h
    src/core/Particle.h src/core/Particle.cpp
    src/core/SteerForceGenerator.h src/core/SteerForceGenerator.cpp
    src/core/BrakeForceGenerator.h src/core/BrakeForceGenerator.cpp
    src/core/CarGenerator.h src/core/CarGenerator.cpp
    src/core/RoadRegistry.h src/core/RoadRegistry.cpp
    src/core/CarRegistry.h src/core/CarRegistry.cpp

    src/opengl/VertexBuffer.h src/opengl/VertexBuffer.cpp
    src/opengl/IndexBuffer.h src/opengl/IndexBuffer.cpp
    src/opengl/VertexBufferLayout.h src/opengl/VertexBufferLayout.cpp
    src/opengl/VertexArray.h src/opengl/VertexArray.cpp
    src/opengl/debug.h src/opengl/debug.cpp
    src/opengl/Shader.h src/opengl/Shader.cpp
    src/opengl/Renderer.h src/opengl/Renderer.cpp
    src/opengl/Texture.h src/opengl/Texture.cpp
  
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

