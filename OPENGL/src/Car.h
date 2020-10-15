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
    bool live;
public:
    Car(Vector loc);
    ~Car();
    Car(const Car& );
    void applyForce(Vector &force);
    void move();
    void seek(Vector &target);
    void followPath(const Road &);
    Vector getPos() const;
    Vector getVel() const;
    bool getLive() const;
private:
    Vector getNormalPoint(Vector&, Vector&, Vector&);
};

#endif