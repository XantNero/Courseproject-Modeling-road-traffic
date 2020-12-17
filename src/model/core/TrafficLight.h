#ifndef _TRAFFICLIGHT_H_
#define _TRAFFICLIGHT_H_
#include "Vector.h"
#include <chrono>

class TrafficLight
{
public:
    enum class State
    {
        Green   = 0,
        Yellow  = 1,
        Red    = 2
    };
public:
    TrafficLight(Vector position, State startState,
                 int greenTime, int yellowTime, int redTime);
    ~TrafficLight() { }
    void update();
    inline State getState() const { return m_State; }
    inline Vector getPosition() const { return m_Position; }
    inline void setPosition(Vector pos) { m_Position = pos; }
private:
    Vector m_Position;
    int m_Period[4];
    State m_State;
    State m_StartState;
    std::chrono::time_point<std::chrono::steady_clock> m_CurrentTime;
};

#endif