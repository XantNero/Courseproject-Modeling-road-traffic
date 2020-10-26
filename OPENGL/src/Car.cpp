#include "Car.h"
#include "Vector.h"
#include "Road.h"
#include <iostream>
#include <math.h>
Car::Car(Vector loc)
    : location(new Vector(loc)), velocity(new Vector),
    acceleration(new Vector), maxSpeed(5 + rand() % 4 - 2), state(LIVE) { }

Car::~Car()
{
    delete location;
    delete velocity;
    delete acceleration;
}


void Car::applyForce(Vector &force)
{
    (*acceleration) += force;
}

Car::Car(const Car& copy)
{
    location = new Vector(*(copy.location));
    acceleration = new Vector(*(copy.acceleration));
    velocity = new Vector(*(copy.velocity));
    maxSpeed = copy.maxSpeed;
    state = copy.state;
}

void Car::seek(Vector &target) // make new seek
{
    Vector desired = target - (*location);

    if (desired.getMagnitude() == 0)  
        return;
    desired.setMagnitude(getMaxSpeed());
    Vector steer = desired - (*velocity);
    steer.limitMagnitude(maxSpeed);
    applyForce(steer);
}

void Car::followPath(const Road &road)
{  
    Vector predict = (*velocity);
    predict.setMagnitude(30);
    Vector predictPos = predict + (*location);
    Vector pos = getPos();
    double worldRecord = 10000000.;
    Vector normal;
    Vector target;

    // if (nowRoadStart == -1) {
         for (int i = 0; i < road.getRoadSize() - 1; ++i) {
            Vector a = road.getPoint(i);
            Vector b = road.getPoint(i + 1);

            Vector normalPoint = getNormalPoint(predictPos, a, b);
            if (!(normalPoint.getX() + road.getRadius() > std::min(a.getX(), b.getX()) && normalPoint.getX() - road.getRadius() < std::max(a.getX(), b.getX())
                && normalPoint.getY() + road.getRadius() > std::min(a.getY(), b.getY()) && normalPoint.getY() - road.getRadius() < std::max(a.getY(), b.getY()))) {
                normalPoint = b;
            } 

            double distance = predictPos.distance(normalPoint);

            if (distance < worldRecord) {
                
                normal = normalPoint;

                Vector dir = b - a;
                dir.setMagnitude(getMaxSpeed());
                Vector temp = target;
                target = normal + dir;
                Vector mov = target - getPos();
                // if (getVel() * mov == -1.0) {
                //     target = temp;
                // }
                    
                worldRecord = distance; 


            
                if (normal == road.getPoint(road.getRoadSize() - 1) && normal.distance(getPos()) < 50)
                    setState(TURN);
            }
        }

    // Vector a = road.getPoint(nowRoadStart);
    // Vector b = road.getPoint(nowRoadStart + 1);

    // if (poscheck.getAngle(dir) < asin(road.getRadius() / poscheck.getMagnitude())
    //                 && pos.getX() > std::min(a.getX(), b.getX()) && pos.getX() < std::max(a.getX(), b.getX())
    //                 && pos.getY() > std::min(a.getY(), b.getY()) && pos.getY() < std::max(a.getY(), b.getY())) {
    //                 nowRoadStart = i;
    //             } 


    //}
    // else {
    //     Vector a = road.getPoint(nowRoadStart);
    //     Vector b = road.getPoint(nowRoadStart + 1);
    //     Vector dir = b - a;
    //     Vector poscheck = pos - a;
    //     if (poscheck.getAngle(dir) < asin(road.getRadius() / poscheck.getMagnitude())
    //         && pos.getX() > std::min(a.getX(), b.getX()) && pos.getX() < std::max(a.getX(), b.getX())
    //         && pos.getY() > std::min(a.getY(), b.getY()) && pos.getY() < std::max(a.getY(), b.getY())) { 
    //         target = dir;
    //         target.setMagnitude(getMaxSpeed());
    //         target += pos;
    //         turning = false;
    //     }
    //     else if (turning) {
    //         target = dir;
    //         target.setMagnitude(getMaxSpeed());
    //         a += pos;
    //     }
    //     else {
    //         ++nowRoadStart;
    //         if (nowRoadStart == road.getRoadSize() - 1) {
    //             live = false;
    //             return;
    //         }  
    //         a = b;
    //         b = road.getPoint(nowRoadStart + 1);
    //         dir = b - a;
    //         dir.setMagnitude(getMaxSpeed());
    //         target = a + dir;
    //         turning = true;
    //     } 
    // }
   
    seek(target);
    // else {
    //     Vector target = getPos() + getVel();
    //     seek(target);
    // }
}

void Car::move(float time)
{
    (*velocity) += (*acceleration) * time;
    velocity->limitMagnitude(maxSpeed * time);
    (*location) += (*velocity) * time;
    (*acceleration) *= 0;
}

Vector Car::getNormalPoint(Vector&p, Vector&a, Vector&b) 
{
    Vector ap = p - a;
    Vector ab = b - a;
    ab.normalize();
    ab *= ab * ap;
    return ab + a;
}

Vector Car::getPos() const
{
    return *location;
}

Vector Car::getVel() const
{
    return *velocity;
}

Car::State Car::getState() const
{
    return state;
}

void Car::setState(Car::State state)
{
    this->state = state;
}

double Car::getMaxSpeed() const
{
    return maxSpeed;
}

bool Car::view(const Car &car) const
{
    Vector dist = car.getPos() - getPos();
    double d = 75;
    double angle = 3.14 / 6.;
    Vector vel = getVel();
    vel *= -1;
    double a = dist.getAngle(vel);
    if (dist.getMagnitude() > 0 && dist.getMagnitude() < d && a > angle)
        return true;
    return false;

}