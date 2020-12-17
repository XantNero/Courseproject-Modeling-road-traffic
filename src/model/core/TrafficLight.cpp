#include "../pch.h"
#include "TrafficLight.h"

TrafficLight::TrafficLight(Vector position,
                           State startState,
                           int greenTime, int yellowTime, int redTime) 
    : m_Position(position)
    , m_CurrentTime(std::chrono::milliseconds(0))
    , m_State(startState)
    , m_StartState(startState)
{
    m_Period[(int)m_StartState] = 0;
    int i = 0;
    if (i == (int)m_StartState)
        ++i;
    m_Period[i++] = greenTime;
    if (i == (int)m_StartState)
        ++i;
    m_Period[i++] = yellowTime;
    if (i == (int)m_StartState)
        ++i;
    m_Period[i++] = redTime;
    
}

void TrafficLight::update() 
{
    using namespace std::chrono;
    auto end = steady_clock::now();
    auto dif = duration_cast<milliseconds>(end - m_CurrentTime);
    if (dif >= milliseconds(m_Period[((int)m_StartState + 3) % 4])) {
        m_CurrentTime = steady_clock::now();
        dif = milliseconds(0);
    }
    int i = (int)m_StartState;
    int cnt = 4;
    while (cnt--) {
        if (dif >= milliseconds(m_Period[i % 4]) &&
            dif <= milliseconds(m_Period[(i + 1) % 4]))
            m_State = (State)i;
        ++i;
    }
}


