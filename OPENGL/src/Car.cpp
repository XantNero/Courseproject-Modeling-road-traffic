#include "Car.h"
#include "Vector.h"
#include "Road.h"

Car::Car(Vector loc)
: location(new Vector(loc)), velocity(new Vector), acceleration(new Vector), maxSpeed(5), live(true) { }

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
    live = copy.live;
}

void Car::seek(Vector &target)
{
    Vector desired = target - (*location);

    if (desired.getMagnitude() == 0) 
        return;
    desired.normalize();
    desired *= maxSpeed;
    Vector steer = desired - (*velocity);
    steer.limitMagnitude(maxSpeed);
    applyForce(steer);
}

void Car::followPath(const Road &road)
{  
    if ((*location).distance(road.getPoint(road.getRoadSize() - 1)) < road.getRadius()) {
        live = false;
    }
        
    Vector predict = (*velocity);
    predict.setMagnitude(20);
    Vector predictPos = predict + (*location);

    double worldRecord = 10000000.;
    Vector normal;
    Vector target;

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
            worldRecord = distance; 
            normal = normalPoint;

            Vector dir = b - a;
            dir.setMagnitude(10);
            target = normal + dir;
            
        }
    }
    if (worldRecord > road.getRadius()) {
        seek(target);
    }
}

void Car::move()
{
    (*velocity) += (*acceleration);
    velocity->limitMagnitude(maxSpeed);
    (*location) += (*velocity);
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

bool Car::getLive() const
{
    return live;
}