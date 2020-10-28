#ifndef _FORCEGENERATOR_H_
#define _FORCEGENERATOR_H_
#include "Particle.h"

class ForceGenerator
{
public:
    virtual void updateForce(Particle2D* Particle2D, const float duration) {}
};

#endif