#include "BrakeForceGenerator.h"

BrakeForceGenerator::BrakeForceGenerator()
    : desired(), distance(0)
{
}
BrakeForceGenerator::BrakeForceGenerator(const Vector& desired, const float distance)
    : desired(desired), distance(distance)
{
}
BrakeForceGenerator::~BrakeForceGenerator()
{
}

void BrakeForceGenerator::init(const Vector& desired, const float distance)
{
    // setDesiredVelocity(desired);
    // setDistance(distance);
    this->desired = desired;
    this->distance = distance;
}
inline void BrakeForceGenerator::setDesiredVelocity(const Vector& desired)
{
    this->desired = desired;
}
inline Vector BrakeForceGenerator::getDesiredVelocity() const
{
    return desired;
}
inline void BrakeForceGenerator::setDistance(const float distance)
{
    this->distance = distance;
}
inline float BrakeForceGenerator::getDistance() const
{
    return distance;
}


void BrakeForceGenerator::updateForce(Particle2D* particle, const float duration) 
{
    Car* car = dynamic_cast<Car*>(particle);
    // Vector vel = car->getVelocity();
    // vel.setMagnitude(getDesiredVelocity().getMagnitude());
    // car->setVel(vel);
    
    Vector desiredBrake = car->getForceAccumulator() + car->getAcceleration() + car->getVelocity();
    //desiredBrake *= -1.0f;
    double a = car->getVelocity().getMagnitude(); 
    double b = getDesiredVelocity().getMagnitude();
    desiredBrake.setMagnitude(car->getMaxSpeed() - getDesiredVelocity().getMagnitude());
    desiredBrake *= -1.0f;
    // if (getDistance() > 50)
    //     desiredBrake.setMagnitude(desiredBrake.getMagnitude() * getDistance() / 50.0f);
    car->applyForce(desiredBrake);
}