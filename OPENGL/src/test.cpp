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
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
//#include "vendor/glm/ext.hpp"
#include "Texture.h"
#include "CarGenerator.h"
#include "RoadRegistry.h"
#include "CarRegistry.h"


//play with count of cars rendering

static const int MaxCars = 1000;
static const int MaxVertexBufferSize = MaxCars * 16 * sizeof(float);
static const int MaxIndexBufferCount = MaxCars * 6;


int main(void)
{
    srand(time(NULL));
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 720, "Hello World", NULL, NULL);
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


    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

      glm::mat4 proj = glm::ortho(0.0f, 1080.0f, 720.0f, 0.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0));
    
    glm::mat4 MVP = proj * view * model;


    RoadRegistry roads;
    
    float roadVertices[] = {
        540.0f, 720.0f,
        540.0f, 360.0f,
        0.0f, 0.0f,
        1080.0f, 0.0f,
        540.0f, 0.0f
    };

   

    unsigned int roadIndices[] = {
        0, 1,
        1, 2,
        1, 3,
        1, 4
    };


    Road road1;
    Road road2;
    Road road3;
    Road road4;
    road1.addPoint(roadVertices[0], roadVertices[1]);
    road1.addPoint(roadVertices[2], roadVertices[3]);
    road2.addPoint(roadVertices[2], roadVertices[3]);
    road2.addPoint(roadVertices[4], roadVertices[5]);
    road3.addPoint(roadVertices[2], roadVertices[3]);
    road3.addPoint(roadVertices[6], roadVertices[7]);
    road4.addPoint(roadVertices[2], roadVertices[3]);
    road4.addPoint(roadVertices[8], roadVertices[9]);
    roads.addRoad(road1);
    roads.addRoad(road2);
    roads.addRoad(road3);
    roads.addRoad(road4);
    roads.connectRoads(roads.getRoadIndex(&road1), roads.getRoadIndex(&road2));
    roads.connectRoads(roads.getRoadIndex(&road1), roads.getRoadIndex(&road3));
    roads.connectRoads(roads.getRoadIndex(&road1), roads.getRoadIndex(&road4));

    //  for (int i = 0; i < sizeof(roadVertices) / (2 *sizeof(float)); ++i) {
    //     glm::vec4 pos = glm::vec4(roadVertices[2 * i], roadVertices[2 * i + 1], 0.0f, 1.0f);
    //     pos = proj * pos;
    //     roadVertices[2 * i] = pos.x;
    //     roadVertices[2 * i + 1] = pos.y;
    // }

    CarGenerator CarGenerator(Vector(540, 710));
    CarRegistry carRegistry;
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


     VertexArray vao;
     vao.bind();
    VertexBuffer roadBuffer(5 * 2 * sizeof(float), (void*)roadVertices);
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2, 2 * sizeof(float));
    vao.addBuffer(roadBuffer, layout);
    IndexBuffer ibo(8, roadIndices);
    vao.unbind();
    Shader shader("res/shaders/basic.shader");
    shader.bind();

    roadBuffer.unbind();
    ibo.unbind();
    // vao.unbind();



  
    shader.setUnifromMat4f("u_MVP", proj);
    Renderer renderer;


    VertexArray vaoCar;
    vaoCar.bind();

    VertexBuffer carBuffer(MaxVertexBufferSize, nullptr);   
    VertexBufferLayout lay;
    lay.push(GL_FLOAT, 2, 2 * sizeof(float));
    lay.push(GL_FLOAT, 2, 2 * sizeof(float));
    vaoCar.addBuffer(carBuffer, lay);
    
    IndexBuffer IndexBufferCar(MaxIndexBufferCount, nullptr);

    Texture carTexture("res/textures/c.png");
    carTexture.bind(0);

    Shader carShader("res/shaders/tr.shader");
    carShader.bind();
    carShader.setUniform1i("u_Texture", 0);
    carShader.setUnifromMat4f("u_MVP", MVP);
    vaoCar.unbind();
    carBuffer.unbind();
    IndexBufferCar.unbind();
   
    glm::vec3 cl(0.3f, 0.1f, 0.3f);
    int genRate = 500;
    float time = 1.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        GLCall(glClearColor(cl.x, cl.y, cl.z, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
        shader.bind();
        shader.setUniform4f("u_Color", 0.2f, 0.5f, 0.8f, 1.0f);
        renderer.draw(GL_LINES, vao, ibo, shader);
       

       // CarGenerator.avoidColision();
       CarGenerator.setRate((float)genRate / time);
        CarGenerator.update(carRegistry);
        carRegistry.update(roads, time);
        std::vector<Car> Cars = carRegistry.getCars();

        carBuffer.resetData();
        IndexBufferCar.ResetData();


        // car.followPath(road);
        // car.move();
        for (int i = 0; i < Cars.size(); ++i) {
            Car car = Cars[i];

            Vector pos = car.getPosition();
            Vector vel = car.getVelocity();
            vel.setMagnitude(20);
            Vector vel1 = vel;
            vel1.rotate(26.5 * 3.14 / 180.0);
            Vector vel2 = vel1;
            vel2.rotate(127 * 3.14 / 180.0);
            Vector vel3 = vel2;
            vel3.rotate(53 * 3.14 / 180.0);
            Vector vel4 = vel3;
            vel4.rotate(127 * 3.14 / 180.0);
            vel1.setMagnitude(20);
            vel2.setMagnitude(20);
            vel3.setMagnitude(20);
            vel4.setMagnitude(20);

            float carTrig[] = {
                pos.getX() + vel1.getX(), pos.getY() + vel1.getY(), 0.0f, 1.0f,
                pos.getX() + vel2.getX(), pos.getY() + vel2.getY(), 0.0f, 0.0f, 
                pos.getX() + vel3.getX(), pos.getY() + vel3.getY(), 1.0f, 0.0f,
                pos.getX() + vel4.getX(), pos.getY() + vel4.getY(), 1.0f, 1.0f 
            };


            unsigned int carIn[] = {
                0 + i * 4, 1 + i * 4, 2 + i * 4,
                2 + i * 4, 3 + i * 4, 0 + i * 4
            };

            // int width = 20, height = 40;
            // Vector initialDir(-1.0f, 0.0f);
            // float carTrig[] = {
            //     pos.getX() + width / 2, pos.getY() - height / 2, 0.0f, 1.0f,
            //     pos.getX() + width / 2, pos.getY() + height / 2, 0.0f, 0.0f, 
            //     pos.getX() - width / 2, pos.getY() + height / 2, 1.0f, 0.0f,
            //     pos.getX() - width / 2, pos.getY() - height / 2, 1.0f, 1.0f 
            // };

            // for (int i = 0; i < 4 * 4; i += 4) {
            //     glm::vec4 pos = glm::vec4(carTrig[i], carTrig[i + 1], 0.0f, 1.0f);
            //     glm::mat4 rot = glm::rotate(glm::mat4(1.0f), /*(float)vel.getAngle(initialDir)*/ 3.14f, glm::vec3(0.0f, 0.0f, 1.0f));

  
            //     pos =  proj * pos;
            //     pos = rot * pos;
            //     carTrig[i] = pos.x;
            //     carTrig[i + 1] = pos.y;
            // }


           
            vaoCar.bind();
            carBuffer.bind();
            IndexBufferCar.bind();
            carBuffer.addData(4 * 4 * sizeof(float), carTrig);
            IndexBufferCar.addData(6, carIn);
            vaoCar.unbind();
            
        }
        
        renderer.draw(GL_TRIANGLES, vaoCar, IndexBufferCar, carShader);

      

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

         if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::SliderFloat3("COLOR", &cl.x, 0.0f, 1.0f);
            ImGui::SliderInt("gen speed", &genRate, 10, 2000);
            ImGui::SliderFloat("time speed", &time, 0.1f, 10.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        }

          /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}