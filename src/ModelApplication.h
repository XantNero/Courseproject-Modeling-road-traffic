#ifndef _MODELAPPLICATION_H_
#define _MODELAPPLICATION_H_
#include "glfw/Window.h"
#include "imgui/ImguiLayer.h"
#include "OpenglLayer.h"

#include "core/CarGenerator.h"
#include "core/CarRegistry.h"
#include "core/RoadRegistry.h"

#include <vector>

//TODO THINK: car* --> make carregistry unique_ptr

class OpenglLayer;

struct ModelInformation
{
    std::vector<Car> cars;
    std::vector<const Road*> roads;
};

class ModelApplication
{
public:
    ModelApplication();
    ~ModelApplication();
    static const ModelApplication* getApp();
    const Window* getWindow() const;
    void run();
private:
    ImguiLayer* m_ImguiLayer;
    OpenglLayer* m_OpenglLayer;
    Window* m_Window;
    static ModelApplication *s_App_Instanse;

    RoadRegistry m_Roads;
    CarRegistry m_CarRegistry;
    CarGenerator m_CarGenerator;
};

#endif