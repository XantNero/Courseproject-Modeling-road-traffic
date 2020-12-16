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
    ~SteerForceGenerator() {}
    inline void setTarget(const Vector &target) { m_Target = target; }
    inline Vector getTarget() const { return m_Target; }
    virtual void updateForce(Particle2D* particle, const float time) override;
private:
    Vector m_Target;
};

class BrakeForceGenerator : public ForceGenerator
{
public: 
    BrakeForceGenerator();
    BrakeForceGenerator(const Vector& desired, const float distance);
    ~BrakeForceGenerator() {}
    void init(const Vector& desired, const float distance);
    inline void setDesiredVelocity(const Vector& desired) { m_Desired = desired; }
    inline Vector getDesiredVelocity() const { return m_Desired; }
    inline void setDistance(const float distance) { m_Distance = distance; }
    inline float getDistance() const { return m_Distance; }
    virtual void updateForce(Particle2D* Particle2D, const float duration) override;
private:
    Vector m_Desired;
    float m_Distance;
};

#endif