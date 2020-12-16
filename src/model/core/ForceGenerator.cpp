#include "ForceGenerator.h"
#include "Car.h"

/*
----------------------------------------------------------------------
|||||||||||||||||||||||SteerForceGenerator||||||||||||||||||||||||||||
----------------------------------------------------------------------
*/

SteerForceGenerator::SteerForceGenerator()
    : m_Target()
{
}

SteerForceGenerator::SteerForceGenerator(const Vector &target)
    : m_Target(target)
{
}

void SteerForceGenerator::updateForce(Particle2D* particle, const float time)
{
    Car* car = dynamic_cast<Car*>(particle);
    Vector desired = m_Target - car->getPosition();
    if (desired.getMagnitude() == 0)  
        return;
    double lim = 1000 * car->getMaxSpeed();
    desired.setMagnitude(lim);
    Vector steer = desired - car->getVelocity()/* - car->getAcceleration()*/;
    steer.limitMagnitude(lim);
    car->applyForce(steer);
}

/*
----------------------------------------------------------------------
|||||||||||||||||||||||BrakeForceGenerator||||||||||||||||||||||||||||
----------------------------------------------------------------------
*/

BrakeForceGenerator::BrakeForceGenerator()
    : m_Desired(), m_Distance(0)
{
}
BrakeForceGenerator::BrakeForceGenerator(const Vector& desired, const float distance)
    : m_Desired(desired), m_Distance(distance)
{
}

void BrakeForceGenerator::init(const Vector& desired, const float distance)
{
    m_Desired = desired;
    m_Distance = distance;
}

void BrakeForceGenerator::updateForce(Particle2D* particle, const float duration) 
{
    Car* car = dynamic_cast<Car*>(particle);
    Vector desiredBrake = car->getVelocity();
    Vector vel = car->getVelocity(); 
    Vector desVel = car->getVelocity();
    desVel.setMagnitude(m_Desired.getMagnitude());
    Vector brake(0.0f, 0.0f);
    if (m_Desired.getSquareMagnitude() < vel.getSquareMagnitude()) {
        brake = desVel - vel;
    }
    car->applyForce(brake);
}

// void BrakeForceGenerator::updateForce(Particle2D* particle, const float duration) 
// {
//     Car* car = dynamic_cast<Car*>(particle);
//     // Vector vel = car->getVelocity();
//     // vel.setMagnitude(getDesiredVelocity().getMagnitude());
//     // car->setVel(vel);
    
//     Vector desiredBrake = /*car->getAcceleration() + */car->getVelocity();
//     //desiredBrake *= -1.0f;
//     Vector vel = car->getVelocity(); 
//     Vector desVel = car->getVelocity();
//     desVel.setMagnitude(m_Desired.getMagnitude());

//     Vector brake(0.0f, 0.0f);
//     if (m_Desired.getSquareMagnitude() < vel.getSquareMagnitude()) {
//         brake = desVel - vel;
//         //brake.setMagnitude(brake.getMagnitude() * 2);
//     }
       
    
//     // double b = getDesiredVelocity().getMagnitude();
//     // desiredBrake.setMagnitude(/*car->getMaxSpeed() - getDesiredVelocity().getMagnitude()*/ fabs(a - b));
//     // desiredBrake *= -1.0f;
//     // if (getDistance() > 50)
//     //     desiredBrake.setMagnitude(desiredBrake.getMagnitude() * getDistance() / 50.0f);
//     car->applyForce(brake);
// }

// void StopForceGenerator::updateForce(Particle2D* particle, const float duration) 
// {
//     Car* car = dynamic_cast<Car*>(particle);
//      Vector desiredBrake = car->getForceAccumulator() + car->getAcceleration() + car->getVelocity();
//     //desiredBrake *= -1.0f;
//     double a = car->getVelocity().getMagnitude(); 
//     double b = getDesiredVelocity().getMagnitude();
//     desiredBrake.setMagnitude(car->getMaxSpeed() - getDesiredVelocity().getMagnitude());
//     desiredBrake *= -1.0f;
//     // if (getDistance() > 50)
//     //     desiredBrake.setMagnitude(desiredBrake.getMagnitude() * getDistance() / 50.0f);
//     car->applyForce(desiredBrake);
// }