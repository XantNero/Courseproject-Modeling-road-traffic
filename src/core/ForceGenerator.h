#ifndef _FORCEGENERATOR_H_
#define _FORCEGENERATOR_H_
#include "Particle.h"

class ForceGenerator
{
public:
    virtual void updateForce(Particle2D* Particle2D, const float duration) {}
    virtual ~ForceGenerator() {}
};

class SteerForceGenerator : public ForceGenerator
{
public:
    SteerForceGenerator();
    SteerForceGenerator(const Vector &target);
    ~SteerForceGenerator();
    inline void setTarget(const Vector &target) { this->target = target; }
    inline Vector getTarget() const { return target; }
    virtual void updateForce(Particle2D* particle, const float time) override;
private:
    Vector target;
};

class BrakeForceGenerator : public ForceGenerator
{
public: 
    BrakeForceGenerator();
    BrakeForceGenerator(const Vector& desired, const float distance);
    ~BrakeForceGenerator();
    void init(const Vector& desired, const float distance);
    inline void setDesiredVelocity(const Vector& desired) { this->desired = desired; }
    inline Vector getDesiredVelocity() const { return desired; }
    inline void setDistance(const float distance) { this->distance = distance; }
    inline float getDistance() const { return distance; }
    virtual void updateForce(Particle2D* Particle2D, const float duration) override;
private:
    Vector desired;
    float distance;
};

class StopForceGenerator : public ForceGenerator
{
public: 
    StopForceGenerator() { }
    ~StopForceGenerator() { }
    virtual void updateForce(Particle2D* Particle2D, const float duration) override;
};

#endif