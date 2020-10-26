cmake_minimum_required(VERSION 3.16)

project(CourseWork)


add_executable(test
    src/test.cpp
    src/Vector.h src/Vector.cpp
    src/Road.h src/Road.cpp
    src/Car.h src/Car.cpp
    src/VertexBuffer.h src/VertexBuffer.cpp
    src/IndexBuffer.h src/IndexBuffer.cpp
    src/VertexBufferLayout.h src/VertexBufferLayout.cpp
    src/VertexArray.h src/VertexArray.cpp
    src/debug.h src/debug.cpp
    src/Shader.h src/Shader.cpp
    src/Renderer.h src/Renderer.cpp
    src/Texture.h src/Texture.cpp
    src/vendor/stb_image/stb_image.h src/vendor/stb_image/stb_image.cpp
    src/vendor/glm/glm.hpp src/vendor/glm/gtc/matrix_transform.hpp
    src/CarGenerator.h src/CarGenerator.cpp
    src/RoadRegistry.h src/RoadRegistry.cpp
    src/CarRegistry.h src/CarRegistry.cpp
)

target_link_libraries(test -lglfw -lrt -lm -ldl -lGLEW -lGLU -lm -lGL)

set(CMAKE_CXX_FLAGS "-g")

