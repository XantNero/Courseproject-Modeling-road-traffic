#include "ModelApplication.h"



// static float ratio = 1.0f;
// static void cursor_position_callback(Window* window, double xpos, double ypos)
// {
//     static double CursorX = xpos;
//     static double CursorY = ypos;
//     if (glfwGetMouseButton(window->m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) && !ImGui::IsAnyItemActive()) {
//         //std::cout << xpos << ' ' << ypos << '\n';
//         double deltaX =  CursorX - xpos;
//         double deltaY =  CursorY - ypos;
//         //glfwSetCursorPos(window->m_Window, CursorX, CursorY);
//         camera.setPosition(camera.getPosition() + glm::vec3(ratio * deltaX, ratio * deltaY, 0.0f));
//     }
//     CursorX = xpos;
//     CursorY = ypos;
    
// }

// static void window_resize_callback(Window* window, int width, int height)
// {
//     static int prevWidth = width;
//     static int prevHeight = height;
//     //camera.setPosition(camera.getPosition() + glm::vec3((float)(width - prevWidth), (float)(height - prevHeight), 0.0f));
//     camera.setProjectionMatrix(glm::ortho(0.0f, ratio * (float)width, ratio * (float)height, 0.0f, -1.0f, 1.0f));
//     glViewport(0, 0, width, height);
//     prevWidth = width;
//     prevHeight = height;
// }


// static void scroll_callback(Window* window, double xOffset, double yOffset)
// {

//     float scale = 1.25f;
//     if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemActive())
//         return;
//     if (yOffset < 0) {
//         camera.setPosition(camera.getPosition() + glm::vec3((scale - 1) * (float)window->getWidth() * ratio / (2 * scale), (scale - 1) * (float)window->getHeight() * ratio / (2 * scale), 0.0f));
//         ratio /= -1 * scale * yOffset;
//     }
//     else {
//         ratio *= scale * yOffset;
//         camera.setPosition(camera.getPosition() - glm::vec3((scale - 1) * (float)window->getWidth() * ratio / (2 * scale), (scale - 1) * (float)window->getHeight() * ratio / (2 * scale), 0.0f));
        
//         //camera.setPosition(camera.getPosition() + glm::vec3((scale - 1) *(float)window->getWidth() * ratio / scale, (scale - 1) * (float)window->getHeight() * ratio / scale, 0.0f));
//     }
//     glm::vec4 p = camera.getViewProjectionMatrix() * glm::vec4(540.0f, 0.0f, 0.0f, 1.0f);
//     std::cout << p.x << ' ' << p.y << ' ';
    
//     camera.setProjectionMatrix(glm::ortho(0.0f, (float)window->getWidth() * ratio, (float)window->getHeight() * ratio, 0.0f, -1.0f, 1.0f));
//     glm::vec4 z = camera.getViewProjectionMatrix() * glm::vec4(540.0f, 0.0f, 0.0f, 1.0f);
//     std::cout << z.x << ' ' << z.y << ' ' <<'\n';
// }




ModelApplication* ModelApplication::s_App_Instanse = nullptr;

ModelApplication::ModelApplication() 
    :m_Window(new Window({"test", 1080, 720})), m_OpenglLayer(new OpenglLayer()), m_ImguiLayer(new ImguiLayer()) 
{
    s_App_Instanse = this;

    // m_Window->setCursorPosCallback(cursor_position_callback);
    // m_Window->setWindowSizeCallback(window_resize_callback);
    // m_Window->setScrollCallback(scroll_callback);
    m_Window->setVSync(true);

    
    float roadVertices[] = {
        540.0f, 720.0f,
        540.0f, 360.0f,
        0.0f, 0.0f,
        1080.0f, 0.0f,
        540.0f, 0.0f
    };

    std::unique_ptr<Road> road1 = std::make_unique<Road>();
    std::unique_ptr<Road> road2 = std::make_unique<Road>();
    std::unique_ptr<Road> road3 = std::make_unique<Road>();
    std::unique_ptr<Road> road4 = std::make_unique<Road>();

    road1->addPoint(roadVertices[0], roadVertices[1]);
    road1->addPoint(roadVertices[2], roadVertices[3]);
    road2->addPoint(roadVertices[2], roadVertices[3]);
    road2->addPoint(roadVertices[4], roadVertices[5]);
    road3->addPoint(roadVertices[2], roadVertices[3]);
    road3->addPoint(roadVertices[6], roadVertices[7]);
    road4->addPoint(roadVertices[2], roadVertices[3]);
    road4->addPoint(roadVertices[8], roadVertices[9]);
    
    m_Roads.addRoad(std::move(road1));
    m_Roads.addRoad(std::move(road2));
    m_Roads.addRoad(std::move(road3));
    m_Roads.addRoad(std::move(road4));
    m_Roads.connectRoads(0, 1);
    m_Roads.connectRoads(0, 2);
    m_Roads.connectRoads(0, 3);
    m_CarGenerator.setPosition(Vector(540, 720));
    m_OpenglLayer->onAttach();
    m_ImguiLayer->onAttach();
}

ModelApplication::~ModelApplication() 
{  
    m_ImguiLayer->onDetach();
    m_OpenglLayer->onDetach();
 
    delete m_Window;
}

const ModelApplication* ModelApplication::getApp() 
{
    return s_App_Instanse;
}

const Window* ModelApplication::getWindow() const
{
    return m_Window;
}

void ModelApplication::run() 
{
    while(!m_Window->shouldClose()) {
        //CarGenerator.setRate((float)genRate / time);
        float time = 1.0f;
        m_CarGenerator.update(m_CarRegistry);
        m_CarRegistry.update(m_Roads, time);

        ModelInformation info;
        info.cars = m_CarRegistry.getCars();
        info.roads = m_Roads.getRoads();
        m_OpenglLayer->onUpdate(info);
        m_ImguiLayer->begin();
        m_ImguiLayer->onImguiRender();
        m_ImguiLayer->end();
        m_Window->onUpdate();
    }
  
}

