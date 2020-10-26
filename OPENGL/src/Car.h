#ifndef _CAR_H_
#define _CAR_H_
#include "Vector.h"
#include "Road.h"

class Car
{
public:
    enum State{
            LIVE,
            TURN,
            DEAD
    };
public:
    Car(Vector loc);
    ~Car();
    Car(const Car& );
    void applyForce(Vector &force);
    void move(float time);
    void seek(Vector &target);
    void followPath(const Road &);
    Vector getPos() const;
    Vector getVel() const;
    State getState() const;
    void setState(State state);
    double getMaxSpeed() const;
    bool view(const Car &car) const;
private:
    Vector getNormalPoint(Vector&, Vector&, Vector&);
private:
    Vector* location;
    Vector* velocity;
    Vector* acceleration;
    double maxSpeed;
    State state;
};

#endif