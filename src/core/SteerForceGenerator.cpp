#include "SteerForceGenerator.h"
#include "Car.h"
SteerForceGenerator::SteerForceGenerator()
    : target()
{
}

SteerForceGenerator::SteerForceGenerator(const Vector &target)
    : target(target)
{
}

SteerForceGenerator::~SteerForceGenerator() { }

void SteerForceGenerator::setTarget(const Vector &target)
{
    this->target = target;
}

Vector SteerForceGenerator::getTarget() const
{
    return target;
}


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