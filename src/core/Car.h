#ifndef _CAR_H_
#define _CAR_H_
#include "Vector.h"
#include "Road.h"
#include "Particle.h"

// class Car
// {
// public:
//     enum State{
//             LIVE,
//             TURN,
//             DEAD
//     };
// public:
//     Car(Vector loc);
//     ~Car();
//     Car(const Car& );
//     void applyForce(Vector &force);
//     void move(float time);
//     void seek(Vector &target);
//     void followPath(const Road &);
//     Vector getPos() const;
//     Vector getVel() const;
//     State getState() const;
//     void setState(State state);
//     double getMaxSpeed() const;
//     bool view(const Car &car) const;
// private:
//     Vector getNormalPoint(Vector&, Vector&, Vector&);
// private:
//     Vector* location;
//     Vector* velocity;
//     Vector* acceleration;
//     double maxSpeed;
//     State state;
// };


class Car : public Particle2D
{
public:
    enum State{
            LIVE,
            TURN,
            DEAD
    };
public:
    Car(const Vector& position);
    Car(const float x, const float y);
    ~Car();
    Car(const Car& );
    virtual void applyForce(const Vector &force) override;
    virtual void move(float time) override;
    bool followPath(const Road* , Vector*);
    virtual Vector getPosition() const override;
    virtual Vector getVelocity() const override;
    virtual Vector getAcceleration() const override;
    State getState() const;
    void setState(State state);
    double getMaxSpeed() const;
    bool view(const Car &car) const;
    virtual Vector getForceAccumulator() const override;
    inline void setVel(const Vector& vel) {velocity = vel;}
    inline void setMaxSpeed(const double spe) { maxSpeed = spe; }
    virtual void clearAccumulator() override;
    virtual float getMass() const override { return 0; }
    virtual float getInverseMass() const override { return 0;}
    virtual bool hasFiniteMass() const override { return 0;}
    virtual void setDamping(float damping) override { }
    virtual float getDamping() const override { return 0;}
private:
    Vector getNormalPoint(Vector&, Vector&, Vector&);
   
private:
    double maxSpeed;
    State state;
};


#endif