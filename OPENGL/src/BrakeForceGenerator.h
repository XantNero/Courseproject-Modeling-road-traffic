#ifndef _BRAKEFORCEGENERATOR_H_
#define _BRAKEFORCEGENERATOR_H_
#include "ForceGenerator.h"
#include "Car.h"

class BrakeForceGenerator : public ForceGenerator
{
public: 
    BrakeForceGenerator();
    BrakeForceGenerator(const Vector& desired, const float distance);
    ~BrakeForceGenerator();
    void init(const Vector& desired, const float distance);
    void setDesiredVelocity(const Vector& desired);
    Vector getDesiredVelocity() const;
    void setDistance(const float distance);
    float getDistance() const;
    virtual void updateForce(Particle2D* Particle2D, const float duration) override;
private:
    Vector desired;
    float distance;
};

#endif