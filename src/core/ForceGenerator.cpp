#include "ForceGenerator.h"
#include "Car.h"

/*
----------------------------------------------------------------------
|||||||||||||||||||||||SteerForceGenerator||||||||||||||||||||||||||||
----------------------------------------------------------------------
*/

SteerForceGenerator::SteerForceGenerator()
    : target()
{
}

SteerForceGenerator::SteerForceGenerator(const Vector &target)
    : target(target)
{
}

SteerForceGenerator::~SteerForceGenerator() { }

void SteerForceGenerator::updateForce(Particle2D* particle, const float time)
{
    Car* car = dynamic_cast<Car*>(particle);
    Vector desired = target - car->getPosition();
    if (desired.getMagnitude() == 0)  
        return;
    desired.setMagnitude(car->getMaxSpeed());
    Vector steer = desired - car->getVelocity()/* - car->getAcceleration()*/;
    steer.limitMagnitude(car->getMaxSpeed());
    car->applyForce(steer);
}

/*
----------------------------------------------------------------------
|||||||||||||||||||||||BrakeForceGenerator||||||||||||||||||||||||||||
----------------------------------------------------------------------
*/

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
    this->desired = desired;
    this->distance = distance;
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