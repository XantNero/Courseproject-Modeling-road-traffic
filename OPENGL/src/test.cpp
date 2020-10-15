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
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "Texture.h"
#include "CarGenerator.h"



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
    window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    //glfwSwapInterval(1);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
        return -1;
    }

    float roadVertices[] = {
        320.0f, 84.0f,
        128.0f, 120.0f,
        129.0f, 216.0f,
        514.0f, 310.0f,
        524.0f, 320.0f,
        880.0f, 120.0f,
        900.0f, 140.0f,
        900.0f, 600.0f,
        200.0f, 460.0f
    };

    unsigned int roadIndices[] = {
        0, 1,
        1, 2,
        2, 3,
        3, 4,
        4, 5,
        5, 6,
        6, 7,
        7, 8
    };


    Road road;
    for (int i = 0; i < sizeof(roadVertices) / (2 * sizeof(float)); ++i) {
        road.addPoint(roadVertices[2 * i], roadVertices[2 * i + 1]);
    }

    CarGenerator CarGenerator(Vector(rand() % width, rand() % height));
    Car car(Vector(rand() % width, rand() % height));

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


     VertexArray vao;
     vao.bind();
    VertexBuffer roadBuffer((void*)roadVertices, 9 * 2 * sizeof(float));
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2, 2 * sizeof(float));
    vao.addBuffer(roadBuffer, layout);
    IndexBuffer ibo(roadIndices, 16);
    vao.unbind();
    Shader shader("res/shaders/basic.shader");
    shader.bind();

    roadBuffer.unbind();
    ibo.unbind();




    glm::mat4 proj = glm::ortho(0.0f, 1080.0f, 720.0f, 0.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
    
    glm::mat4 MVP = proj * view * model;

    shader.setUnifromMat4f("u_MVP", proj);
    Renderer renderer;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        GLCall(glClearColor(0.3f, 0.1f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
        shader.bind();
        shader.setUniform4f("u_Color", 0.2f, 0.5f, 0.8f, 1.0f);
        renderer.draw(GL_LINES, vao, ibo, shader);
       

        CarGenerator.update(road);
        std::vector<Car> Cars = CarGenerator.getCars();

        // car.followPath(road);
        // car.move();
        for (auto car : Cars) {
            Vector pos = car.getPos();
            Vector vel = car.getVel();
            vel.setMagnitude(20);
            Vector vel1 = vel;
            vel1.rotate(26.5 * 3.14 / 180.0);
            Vector vel2 = vel1;
            vel2.rotate(127 * 3.14 / 180.0);
            Vector vel3 = vel2;
            vel3.rotate(53 * 3.14 / 180.0);
            Vector vel4 = vel3;
            vel4.rotate(127 * 3.14 / 180.0);
            vel1.setMagnitude(50);
            vel2.setMagnitude(50);
            vel3.setMagnitude(50);
            vel4.setMagnitude(50);

            float carTrig[] = {
                pos.getX() + vel1.getX(), pos.getY() + vel1.getY(), 0.0f, 1.0f,
                pos.getX() + vel2.getX(), pos.getY() + vel2.getY(), 0.0f, 0.0f, 
                pos.getX() + vel3.getX(), pos.getY() + vel3.getY(), 1.0f, 0.0f,
                pos.getX() + vel4.getX(), pos.getY() + vel4.getY(), 1.0f, 1.0f 
            };
            VertexArray vaoCar;
            vaoCar.bind();

           Texture carTexture("res/textures/c.png");
           carTexture.bind(0);
            VertexBuffer carBuffer(carTrig, 4 * 4 * sizeof(float));
            
            VertexBufferLayout lay;
            lay.push(GL_FLOAT, 2, 2 * sizeof(float));
           lay.push(GL_FLOAT, 2, 2 * sizeof(float));
            vaoCar.addBuffer(carBuffer, lay);
        
            unsigned int carIn[] = {
                0, 1, 2,
                2, 3, 0
            };
            IndexBuffer IndexBufferCar(carIn, 6);
            Shader carShader("res/shaders/tr.shader");
            carShader.bind();
           carShader.setUniform1i("u_Texture", 0);
            carShader.setUnifromMat4f("u_MVP", MVP);
            renderer.draw(GL_TRIANGLES, vaoCar, ibo, carShader);
        }
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}