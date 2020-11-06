#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

#include "core/Vector.h"
#include "core/Road.h"
#include "core/Car.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "opengl/debug.h"
#include "opengl/VertexBuffer.h"
#include "opengl/IndexBuffer.h"
#include "opengl/VertexBufferLayout.h"
#include "opengl/VertexArray.h"
#include "opengl/Shader.h"
#include "opengl/Renderer.h"
#include "opengl/OrtographicCamera.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
//#include "vendor/glm/ext.hpp"
#include "opengl/Texture.h"
#include "core/CarGenerator.h"
#include "core/RoadRegistry.h"
#include "core/CarRegistry.h"


//play with count of cars rendering

static const int MaxCars = 1000;
static const int MaxVertexBufferSize = MaxCars * 16 * sizeof(float);
static const int MaxIndexBufferCount = MaxCars * 6;
static float ratio = 1.0f;
static OrtographicCamera camera(0.0f, 1080.0f, 720.0f, 0.0f);
static void cursor_position_callback(Window* window, double xpos, double ypos)
{
    static double CursorX = xpos;
    static double CursorY = ypos;
    if (glfwGetMouseButton(window->m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) && !ImGui::IsAnyItemActive()) {
        //std::cout << xpos << ' ' << ypos << '\n';
        double deltaX =  CursorX - xpos;
        double deltaY =  CursorY - ypos;
        //glfwSetCursorPos(window->m_Window, CursorX, CursorY);
        camera.setPosition(camera.getPosition() + glm::vec3(ratio * deltaX, ratio * deltaY, 0.0f));
    }
    CursorX = xpos;
    CursorY = ypos;
    
}

static void window_resize_callback(Window* window, int width, int height)
{
    static int prevWidth = width;
    static int prevHeight = height;
    //camera.setPosition(camera.getPosition() + glm::vec3((float)(width - prevWidth), (float)(height - prevHeight), 0.0f));
    camera.setProjectionMatrix(glm::ortho(0.0f, ratio * (float)width, ratio * (float)height, 0.0f, -1.0f, 1.0f));
    glViewport(0, 0, width, height);
    prevWidth = width;
    prevHeight = height;
}


static void scroll_callback(Window* window, double xOffset, double yOffset)
{

    float scale = 1.25f;
    if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemActive())
        return;
    if (yOffset < 0) {
        camera.setPosition(camera.getPosition() + glm::vec3((scale - 1) * (float)window->getWidth() * ratio / (2 * scale), (scale - 1) * (float)window->getHeight() * ratio / (2 * scale), 0.0f));
        ratio /= -1 * scale * yOffset;
    }
    else {
        ratio *= scale * yOffset;
        camera.setPosition(camera.getPosition() - glm::vec3((scale - 1) * (float)window->getWidth() * ratio / (2 * scale), (scale - 1) * (float)window->getHeight() * ratio / (2 * scale), 0.0f));
        
        //camera.setPosition(camera.getPosition() + glm::vec3((scale - 1) *(float)window->getWidth() * ratio / scale, (scale - 1) * (float)window->getHeight() * ratio / scale, 0.0f));
    }
    glm::vec4 p = camera.getViewProjectionMatrix() * glm::vec4(540.0f, 0.0f, 0.0f, 1.0f);
    std::cout << p.x << ' ' << p.y << ' ';
    
    camera.setProjectionMatrix(glm::ortho(0.0f, (float)window->getWidth() * ratio, (float)window->getHeight() * ratio, 0.0f, -1.0f, 1.0f));
    glm::vec4 z = camera.getViewProjectionMatrix() * glm::vec4(540.0f, 0.0f, 0.0f, 1.0f);
    std::cout << z.x << ' ' << z.y << ' ' <<'\n';
}


int main(void)
{
    srand(time(NULL));
    //GLFWwindow* window;
    Window window({"test", 1080, 720});
    window.setCursorPosCallback(cursor_position_callback);
    window.setWindowSizeCallback(window_resize_callback);
    window.setScrollCallback(scroll_callback);
    /* Initialize the library */
    
    const char* glsl_version = "#version 130";
   camera.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    //camera.setProjectionMatrix(glm::ortho(0.0f, 2 * 1080.0f, 2 * 720.0f, 0.0f, -1.0f, 1.0f));
    /* Create a windowed mode window and its OpenGL context */
   

    glfwSwapInterval(1);

    // int width, height;
    // glfwGetWindowSize(window, &width, &height);

    /* Make the window's context current */
   


    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.m_Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    
    

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

    vaoCar.unbind();
    carBuffer.unbind();
    IndexBufferCar.unbind();
   
    glm::vec3 cl(0.2f, 0.3f, 0.8f);
    int genRate = 500;
    float time = 1.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window.m_Window)) {
        /* Render here */
        GLCall(glClearColor(cl.r, cl.g, cl.b, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        
        // glm::vec4 p =  glm::ortho(0.0f, 1080.0f, 720.0f, 0.0f) * glm::vec4(1080.0f, 0.0f, 0.0f, 1.0f); 
        // glm::vec4 z = camera.getViewProjectionMatrix() * glm::vec4(1080.0f, 0.0f, 0.0f, 1.0f);
        // std::cout << p.x << ' ' << p.y << ' ' << z.x << ' ' << z.y << ' ' <<'\n';

        shader.bind();
        shader.setUniform4f("u_Color", 0.2f, 0.5f, 0.8f, 1.0f);
        shader.setUnifromMat4f("u_ViewProjectionMatrix", camera.getViewProjectionMatrix());
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
            Vector normal(0.0f, -1.0f);
            float angle = vel.getAngle(normal);
            if (scalarDotProduct(vel, normal) > 0)
                angle *= -1;
            glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(pos.getX(), pos.getY(), 0.0f))
                                    * glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
            // vel.setMagnitude(20);
            // Vector vel1 = vel;
            // vel1.rotate(26.5 * 3.14 / 180.0);
            // Vector vel2 = vel1;
            // vel2.rotate(127 * 3.14 / 180.0);
            // Vector vel3 = vel2;
            // vel3.rotate(53 * 3.14 / 180.0);
            // Vector vel4 = vel3;
            // vel4.rotate(127 * 3.14 / 180.0);
            // vel1.setMagnitude(20);
            // vel2.setMagnitude(20);
            // vel3.setMagnitude(20);
            // vel4.setMagnitude(20);

            // float carTrig[] = {
            //     pos.getX() + vel1.getX(), pos.getY() + vel1.getY(), 0.0f, 1.0f,
            //     pos.getX() + vel2.getX(), pos.getY() + vel2.getY(), 0.0f, 0.0f, 
            //     pos.getX() + vel3.getX(), pos.getY() + vel3.getY(), 1.0f, 0.0f,
            //     pos.getX() + vel4.getX(), pos.getY() + vel4.getY(), 1.0f, 1.0f 
            // };
             float carTrig[] = {
                -10.0f, -20.0f, 0.0f, 1.0f,
                -10.0f, 20.0f, 0.0f, 0.0f, 
                10.0f, 20.0f, 1.0f, 0.0f,
                10.0f, -20.0f, 1.0f, 1.0f 
            };

            for (int j = 0; j < 4; ++j) {
                glm::vec4 position = ModelMatrix * glm::vec4(carTrig[4 * j], carTrig[4 * j + 1], 0.0f, 1.0f);
                carTrig[4 * j] = position.x;
                carTrig[4 * j + 1] = position.y; 
            }


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
        carShader.bind();
        carShader.setUnifromMat4f("u_ViewProjectionMatrix", camera.getViewProjectionMatrix());
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
        window.onUpdate();

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();


    return 0;
}