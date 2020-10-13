#ifndef _CAR_H_
#define _CAR_H_
#include "Vector.h"
#include "Road.h"
class Car
{
private:
    Vector* location;
    Vector* velocity;
    Vector* acceleration;
    double maxSpeed;
public:
    Car(Vector loc);
    ~Car();
    void applyForce(Vector &force);
    void move();
    void seek(Vector &target);
    void followPath(Road &);
private:
    Vector getNormalPoint(Vector&, Vector&, Vector&);
};

#endif