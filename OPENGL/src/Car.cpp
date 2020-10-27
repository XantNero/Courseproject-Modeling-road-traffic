#include "Car.h"
#include "Vector.h"
#include "Road.h"
#include <iostream>
#include <math.h>
Car::Car(const Vector& pos)
    : Particle2D(pos), maxSpeed(5 + rand() % 4 - 2), state(LIVE)
{
    position = pos;
}

Car::Car(const float x, const float y)
    : Particle2D(x, y),  maxSpeed(5 + rand() % 4 - 2), state(LIVE)
{
    position = Vector(x, y);
}



Car::~Car()
{
}


void Car::applyForce(const Vector &force)
{
    forceAccumulator += force;
}

Car::Car(const Car& copy)
    : Particle2D(copy.position), maxSpeed(copy.maxSpeed), state(copy.state)
{
    //position = copy.position;
    acceleration = copy.acceleration;
    velocity = copy.velocity;
    forceAccumulator = copy.forceAccumulator;
    inverseMass = copy.inverseMass;
    damping = copy.damping;
}

void Car::seek(Vector &target) // make new seek
{
    Vector desired = target - position;

    if (desired.getMagnitude() == 0)  
        return;
    desired.setMagnitude(getMaxSpeed());
    Vector steer = desired - velocity;
    steer.limitMagnitude(maxSpeed);
    applyForce(steer);
}

void Car::followPath(const Road &road)
{  
    Vector predict = velocity;
    predict.setMagnitude(30);
    Vector predictPos = predict + position;
    Vector pos = getPosition();
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
                Vector mov = target - getPosition();
                // if (getVel() * mov == -1.0) {
                //     target = temp;
                // }
                    
                worldRecord = distance; 


            
                if (normal == road.getPoint(road.getRoadSize() - 1) && normal.distance(getPosition()) < 50)
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
    acceleration *= 0;
    acceleration += forceAccumulator;
    velocity += acceleration * time;
    velocity.limitMagnitude(maxSpeed * time);
    position += velocity * time;
    clearAccumulator();    
}

void Car::clearAccumulator()
{
    forceAccumulator *= 0;
}

Vector Car::getNormalPoint(Vector&p, Vector&a, Vector&b) 
{
    Vector ap = p - a;
    Vector ab = b - a;
    ab.normalize();
    ab *= ab * ap;
    return ab + a;
}

Vector Car::getPosition() const
{
    return position;
}

Vector Car::getVelocity() const
{
    return velocity;
}

Vector Car::getAcceleration() const
{
    return acceleration;
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
    Vector dist = car.getPosition() - getPosition();
    double d = 75;
    double angle = 3.14 / 6.;
    Vector vel = getVelocity();
    vel *= -1;
    double a = dist.getAngle(vel);
    if (dist.getMagnitude() > 0 && dist.getMagnitude() < d && a > angle)
        return true;
    return false;

}