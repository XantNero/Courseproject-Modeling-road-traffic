#ifndef _STEERFORCEGENERATOR_H_
#define _STEERFORCEGENERATOR_H_
#include "ForceGenerator.h"
class SteerForceGenerator : public ForceGenerator
{
public:
    SteerForceGenerator();
    SteerForceGenerator(const Vector &target);
    ~SteerForceGenerator();
    void setTarget(const Vector &target);
    Vector getTarget() const;
    virtual void updateForce(Particle2D* particle, const float time) override;
private:
    Vector target;
};

#endif