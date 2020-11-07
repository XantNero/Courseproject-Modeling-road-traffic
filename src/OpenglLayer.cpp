#include "OpenglLayer.h"
#include "ModelApplication.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "glfw/Window.h"
#include "opengl/Texture.h"
#include "opengl/Renderer.h"
#include "GL/glew.h"

static const int MaxCars = 1000;
static const int MaxVertexBufferSize = MaxCars * 16 * sizeof(float);
static const int MaxIndexBufferCount = MaxCars * 6;

OpenglLayer::OpenglLayer() 
{  
}

OpenglLayer::~OpenglLayer() 
{
}

void OpenglLayer::onAttach() 
{
 


    {
    const Window* window = ModelApplication::getApp()->getWindow();
    m_Camera = std::make_unique<OrtographicCamera>(0.0f, (float)window->getWidth(), (float)window->getHeight(), 0.0f);
    m_Camera->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    }

    m_RoadVAO = std::make_unique<VertexArray>();
    m_RoadVAO->bind();
    std::shared_ptr<VertexBuffer> roadBuffer = std::make_shared<VertexBuffer>(MaxVertexBufferSize, nullptr);
    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2, 2 * sizeof(float));
    m_RoadVAO->addVertexBuffer(roadBuffer, layout);
    std::shared_ptr<IndexBuffer> roadIBO = std::make_shared<IndexBuffer>(MaxIndexBufferCount, nullptr);
    m_RoadVAO->setIndexBuffer(roadIBO);
    m_RoadVAO->unbind();

    m_RoadShader = std::make_unique<Shader>("res/shaders/road.shader");

    m_CarVAO = std::make_unique<VertexArray>();
    m_CarVAO->bind();

    std::shared_ptr<VertexBuffer> carBuffer = std::make_shared<VertexBuffer>(MaxVertexBufferSize, nullptr);
    VertexBufferLayout lay;
    lay.push(GL_FLOAT, 2, 2 * sizeof(float));
    lay.push(GL_FLOAT, 2, 2 * sizeof(float));
    m_CarVAO->addVertexBuffer(carBuffer, lay);
    
    std::shared_ptr<IndexBuffer> carIBO = std::make_shared<IndexBuffer>(MaxIndexBufferCount, nullptr);
    m_CarVAO->setIndexBuffer(carIBO);


    m_CarVAO->unbind();



    m_Texture = std::make_unique<Texture>("res/textures/c.png");
    m_Texture->bind(0);
    m_CarShader = std::make_unique<Shader>("res/shaders/car.shader");
    m_CarShader->bind();

    m_CarShader->setUniform1i("u_Texture", 0);
    //m_CarShader->unbind();
    
    Renderer::enableBlending();
   
}

void OpenglLayer::onDetach() 
{
    
}

void OpenglLayer::onUpdate(const ModelInformation& information) 
{
//       float roadVertices[] = {
//         540.0f, 720.0f,
//         540.0f, 360.0f,
//         0.0f, 0.0f,
//         1080.0f, 0.0f,
//         540.0f, 0.0f
//     };


//     unsigned int roadIndices[] = {
//         0, 1,
//         1, 2,
//         1, 3,
//         1, 4
//     };

    Renderer::setClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    Renderer::clear();


    m_RoadVAO->bind();
    std::shared_ptr<VertexBuffer> RoadBuffer = m_RoadVAO->getVertexBufferArray()[0];
    RoadBuffer->resetData();
    std::shared_ptr<IndexBuffer> RoadIBO = m_RoadVAO->getIndexBuffer();
    RoadIBO->ResetData();
    float roadsVertices[MaxVertexBufferSize];
    unsigned int roadsIndices[MaxIndexBufferCount];
    unsigned int roadsVertivesIndex = 0;
    unsigned int roadsIndicesIndex = 0;
    for (unsigned int i = 0; i < information.roads.size(); ++i) {
        const Road* road = information.roads[i];
        for (unsigned int j = 0; j < road->getRoadSize(); ++j) {
            Vector position = road->getPoint(j);
            roadsVertices[2 * roadsVertivesIndex] = (float)position.getX();
            roadsVertices[2 * roadsVertivesIndex + 1] = (float)position.getY();
         
            roadsIndices[roadsIndicesIndex] = roadsVertivesIndex;
            ++roadsIndicesIndex;
            if (j != 0 && j != road->getRoadSize() - 1) {
                roadsIndices[roadsIndicesIndex] = roadsVertivesIndex;
                ++roadsIndicesIndex;
            }
            ++roadsVertivesIndex;
        }
    }
    RoadBuffer->bind();
    RoadBuffer->addData(2 * roadsVertivesIndex* sizeof(float), roadsVertices);
    RoadIBO->bind();
    RoadIBO->addData(roadsIndicesIndex, roadsIndices);
    // RoadBuffer->bind();
    // RoadBuffer->addData(2 * 5 * sizeof(float), roadVertices);
    // RoadIBO->bind();
    // RoadIBO->addData(2 * 4, roadIndices);

    m_RoadShader->bind();
    m_RoadShader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    m_RoadShader->setUnifromMat4f("u_ViewProjectionMatrix", m_Camera->getViewProjectionMatrix());
    Renderer::draw(GL_LINES, *m_RoadVAO, *m_RoadShader);
     //m_RoadShader->unbind();
    m_CarVAO->bind();
    std::shared_ptr<VertexBuffer> CarBuffer = m_CarVAO->getVertexBufferArray()[0];
    CarBuffer->bind();
    CarBuffer->resetData();

    std::shared_ptr<IndexBuffer> CarIBO = m_CarVAO->getIndexBuffer();
    CarIBO->bind();
    CarIBO->ResetData();


    // car.followPath(road);
    // car.move();
    for (int i = 0; i < information.cars.size(); ++i) {
        Car car = information.cars[i];

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


        

        CarBuffer->addData(4 * 4 * sizeof(float), carTrig);
        CarIBO->addData(6, carIn);        
    }
    m_CarShader->bind();
    m_CarShader->setUnifromMat4f("u_ViewProjectionMatrix", m_Camera->getViewProjectionMatrix());
    //m_CarShader->setUniform1i("u_Texture", 0);
    Renderer::draw(GL_TRIANGLES, *m_CarVAO, *m_CarShader);
    //m_CarShader->unbind();

}
