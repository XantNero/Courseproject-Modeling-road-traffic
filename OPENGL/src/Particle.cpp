#include "Particle.h"


Particle2D::Particle2D(const Vector& pos, float mass, float damping)
    : position(pos), velocity(), acceleration(), forceAccumulator(),
    inverseMass(1 / mass), damping(damping)
{

}

Particle2D::Particle2D(const float x, const float y, float mass, float damping)
    : position(x, y), velocity(), acceleration(), forceAccumulator(),
    inverseMass(1 / mass), damping(damping)
{
    
}

// Particle2D::Particle2D()
//     : position(), velocity(), acceleration(), forceAccumulator(),
//     inverseMass(1.0f), damping(1.0f)
// {

// }

