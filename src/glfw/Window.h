#ifndef _WINDOW_H_
#define _WINDOW_H_
#include <string>
struct GLFWwindow; 

class Window;

struct WindowData
{
    std::string Title;
    unsigned int Width, Height;
    unsigned int CursorPosX, CursorPosY;
    Window* WindowPointer;
    //TODO: SET PROPER EVENT SYSTEM
    void (*WindowSizeCallback)(Window* window, int width, int height) = nullptr;
    void (*KeyCallback)(Window* window, int key, int scancode, int action, int mods) = nullptr;
    void (*CharCallback)(Window* window, unsigned int keycode) = nullptr;
    void (*MouseButtonCallback)(Window* window, int button, int action, int mods) = nullptr;
    void (*ScrollCallback)(Window* window, double xOffset, double yOffset) = nullptr;
    void (*CursorPosCallback)(Window* window, double xPos, double yPos) = nullptr;
};
struct WindowProps
{
    std::string Title;
    unsigned int Width, Height;
    WindowProps(const std::string& title = "Model", const unsigned int width = 1080,
                const unsigned int height = 720)
                : Title(title), Width(width), Height(height)
    {
    }
};

class Window
{
public:
    Window();
    Window(const WindowProps& props);
    ~Window();
    void onUpdate();
    void setWindowSizeCallback(void (*)(Window* window, int width, int height));
	void setKeyCallback(void (*)(Window* window, int key, int scancode, int action, int mods));
	void setCharCallback(void (*)(Window* window, unsigned int keycode));
	void setMouseButtonCallback(void (*)(Window* window, int button, int action, int mods));
	void setScrollCallback(void (*)(Window* window, double xOffset, double yOffset));
	void setCursorPosCallback(void (*)(Window* window, double xPos, double yPos));

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    bool shouldClose() const;
    void setVSync(bool);
    GLFWwindow* m_Window;
private:

    void shutDown();
    WindowData m_data;
};

static void WindowSizeCallback(GLFWwindow* window, int width, int height);
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void CharCallback(GLFWwindow* window, unsigned int keycode);
static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
static void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);

#endif