cmake_minimum_required(VERSION 3.16)

project(CourseWork)


add_executable(test
    test.cpp
    Vector.h Vector.cpp
    Road.h Road.cpp
    Car.h Car.cpp
    VertexBuffer.h VertexBuffer.cpp
)

target_link_libraries(test -lglfw -lrt -lm -ldl -lGLEW -lGLU -lm -lGL)
