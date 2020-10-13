#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vector.h"
#include "Road.h"
#include "Car.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "debug.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"



// struct ShaderProgramSource {
//     std::string VertexSource;
//     std::string FragmentSource;
// };


// static ShaderProgramSource ParseShader(const std::string &filePath)
// {
//     std::ifstream stream(filePath);

//     enum class ShaderType {
//         NONE = -1, VERTEX = 0, FRAGMENT = 1
//     };

//     std::stringstream ss[2];
//     std::string line;
//     ShaderType type = ShaderType::NONE;
//     while (getline(stream, line)) {
//         if (line.find("#shader") != std::string::npos) {
//             if (line.find("vertex") != std::string::npos) {
//                 type = ShaderType::VERTEX;
//             }
//             else if (line.find("fragment") != std::string::npos) {
//                 type = ShaderType::FRAGMENT;
//             }
//         }
//         else {
//             ss[(int)type] << line << '\n';
//         }
//     }

//     stream.close();
//     return {ss[0].str(), ss[1].str()};
// }

// static unsigned int CompileShader(unsigned int type, const std::string &source)
// {
//     GLCall(unsigned int shader = glCreateShader(type));
//     const char* src = source.c_str();
//     GLCall(glShaderSource(shader, 1, &src, 0));
//     GLCall(glCompileShader(shader));
//     return shader;
// }


// static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
// {
//     GLCall(unsigned int program = glCreateProgram());
//     unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//     unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//     GLCall(glAttachShader(program, vs));
//     GLCall(glAttachShader(program, fs));
//     GLCall(glLinkProgram(program));
//     GLCall(glValidateProgram(program));

//     GLCall(glDeleteShader(vs));
//     GLCall(glDeleteShader(fs));
//     return program;
    
// }


int main(void)
{
    srand(time(NULL));
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
        return -1;
    }

    float roadVertices[] = {
        0.0f, 0.7f,
        -0.6f, 0.5f,
        -0.6f, 0.1f,
        0.3f, 0.0f,
        0.5f, -0.5f
    };

    unsigned int roadIndices[] = {
        0, 1,
        1, 2,
        2, 3,
        3, 4
    };


    Road road;
    for (int i = 0; i < sizeof(roadVertices) / (2 * sizeof(float)); ++i) {
        road.addPoint(roadVertices[2 * i] * width / 2, roadVertices[2 * i + 1] * height / 2);
    }

    Car car(Vector(rand() % width - width / 2, rand() % height - height / 2));


     VertexArray vao;
     vao.bind();
    //unsigned int vao;
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);
    VertexBuffer roadBuffer((void*)roadVertices, 5 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2, 2 * sizeof(float));
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    //std::cout << GL_FLOAT << '\n';
    vao.addBuffer(roadBuffer, layout);
    IndexBuffer ibo(roadIndices, 8);
    vao.unbind();
    //glBindVertexArray(0);
    Shader shader("res/shaders/tr.shader");
    shader.bind();

    roadBuffer.unbind();
    ibo.unbind();

    Renderer renderer;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        GLCall(glClearColor(0.3f, 0.1f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        //glDrawArrays(GL_LINES, 0, 5);
        vao.bind();
        //roadBuffer.bind();
        //ibo.bind();
        //glBindVertexArray(vao);
        shader.setUniform4f("u_Color", 0.2f, 0.5f, 0.8f, 1.0f);
        GLCall(glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0));
        //ibo.unbind();
        //glBindVertexArray(0);
        vao.unbind();
       

        car.followPath(road);
        car.move();
        Vector pos = car.getPos();
        Vector vel = car.getVel();
        vel.setMagnitude(20);
        Vector vel1 = vel;
        Vector vel2 = vel;
        vel1.rotate(2 * 3.14/3);
        vel2.rotate(-2 *3.14/3);
        vel1.setMagnitude(10);
        vel2.setMagnitude(10);

        float carTrig[] = {
            pos.getX() + vel.getX(), pos.getY() + vel.getY(),
            pos.getX() - vel1.getX(), pos.getY() - vel1.getY(),
            pos.getX() - vel2.getX(), pos.getY() - vel2.getY()
        };
        for (int i = 0; i < sizeof(carTrig) / (2 * sizeof(float)); ++i) {
            carTrig[2 * i] /= width / 2;
            carTrig[2 * i + 1] /= height / 2;
        }

        VertexArray vaoCar;
        vaoCar.bind();
        VertexBuffer carBuffer(carTrig, 2 * 3 * sizeof(float));
        
        VertexBufferLayout lay;
        lay.push(GL_FLOAT, 2, 2 * sizeof(float));
        vaoCar.addBuffer(carBuffer, lay);
    
        unsigned int carIn[] = {
            0, 1, 2
        };
        IndexBuffer IndexBufferCar(carIn, 3);
        shader.setUniform4f("u_Color", 0.0f, 1.0f, 0.0f, 1.0f);
        renderer.draw(vaoCar, ibo, shader);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}