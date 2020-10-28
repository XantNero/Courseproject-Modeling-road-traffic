#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "Vector.h"

class Particle2D
{
public:
    //Particle2D();
    Particle2D(const Vector& position, float mass = 1.0f, float damping = 0.98f);
    Particle2D(const float x, const float y, float mass = 1.0f, float damping = 0.98f);
    virtual ~Particle2D() { };
    virtual void move(float duration) = 0;
    //virtual void setMass(float mass) = 0;
    virtual float getMass() const = 0;
    //virtual void setInverseMass(float inverse_mass) = 0;
    virtual float getInverseMass() const = 0;
    virtual bool hasFiniteMass() const = 0;
    virtual void setDamping(float damping) = 0;
    virtual float getDamping() const = 0;
    //virtual void setPosition(const Vector& pos) = 0;
    //virtual void setPosition(const float x, const float y) = 0;
    virtual Vector getPosition() const = 0;
    // virtual void setVelocity(const Vector& velocity) = 0;
    virtual Vector getVelocity() const = 0;
    // virtual void setAcceleration(const Vector& acceleration) = 0;
    virtual Vector getAcceleration() const = 0;
    virtual Vector getForceAccumulator() const = 0;
    virtual void clearAccumulator() = 0;
    virtual void applyForce(const Vector& force) = 0;
protected:
    Vector position;
    Vector velocity;
    Vector acceleration;
    Vector forceAccumulator;
    float inverseMass;
    float damping;
};

#endif