#include "Car.h"
#include "Vector.h"
#include "Road.h"

void Car::applyForce(Vector &force)
{
    (*acceleration) += force;
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

void Car::followPath(Road &road)
{
    Vector predict = *velocity;
    predict.setMagnitude(50);
    Vector predictPos = predict + (*location);

    double worldRecord = 10000000.;
    Vector normal;
    Vector target;

    for (int i = 0; i < road.getRoadSize() - 1; ++i) {
        Vector a = road.getPoint(i);
        Vector b = road.getPoint(i + 1);

        Vector normalPoint = getNormalPoint(predictPos, a, b);
        if (normalPoint.getX() < a.getX() || normalPoint.getX() > b.getX()) {
            normalPoint = b;
        } 

        double distance = predictPos.distance(normalPoint);

        if (distance < worldRecord) {
            worldRecord = distance; 
            normal = normalPoint;

            Vector dir = a - b;
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