cmake_minimum_required(VERSION 3.16)

project(CourseWork)


add_executable(main
    src/main.cpp
    src/core/Vector.h src/core/Vector.cpp
    src/core/Road.h src/core/Road.cpp
    src/core/Car.h src/core/Car.cpp
    src/core/ForceGenerator.h src/core/ForceGenerator.cpp
    src/core/Particle.h src/core/Particle.cpp
    src/core/MDLParser.h src/core/MDLParser.cpp

    src/glfw/Window.h src/glfw/Window.cpp

    src/imgui/ImguiLayer.h src/imgui/ImguiLayer.cpp 

    src/OpenglLayer.h src/OpenglLayer.cpp
    src/ModelApplication.h src/ModelApplication.cpp
   

    src/opengl/Buffer.h src/opengl/Buffer.cpp
    src/opengl/VertexArray.h src/opengl/VertexArray.cpp
    src/opengl/debug.h src/opengl/debug.cpp
    src/opengl/Shader.h src/opengl/Shader.cpp
    src/opengl/Renderer.h src/opengl/Renderer.cpp
    src/opengl/Texture.h src/opengl/Texture.cpp
    src/opengl/OrtographicCamera.h src/opengl/OrtographicCamera.cpp
  
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

target_link_libraries(main -lglfw -lrt -lm -ldl -lGLEW -lGLU -lm -lGL)

set(CMAKE_CXX_FLAGS "-g")

project(QtApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-no-pie")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

  add_executable(gui
    QtApp/main.cpp
    QtApp/Mainwindow.cpp
    QtApp/Mainwindow.h
    QtApp/Workspace.h
    QtApp/Workspace.cpp
    QtApp/WorkspaceScene.h
    QtApp/WorkspaceScene.cpp
    QtApp/Item.h
    QtApp/Item.cpp
  )

target_link_libraries(gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
