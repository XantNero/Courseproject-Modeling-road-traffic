#include "Particle.h"


Particle2D::Particle2D(const Vector& pos, float mass, float damping)
    : m_Position(pos), m_Velocity(), m_Acceleration(), m_ForceAccumulator(),
    m_InverseMass(1 / mass), m_Damping(damping)
{

}

Particle2D::Particle2D(const float x, const float y, float mass, float damping)
    : m_Position(x, y), m_Velocity(), m_Acceleration(), m_ForceAccumulator(),
    m_InverseMass(1 / mass), m_Damping(damping)
{
    
}

// Particle2D::Particle2D()
//     : position(), velocity(), acceleration(), forceAccumulator(),
//     inverseMass(1.0f), damping(1.0f)
// {

// }

