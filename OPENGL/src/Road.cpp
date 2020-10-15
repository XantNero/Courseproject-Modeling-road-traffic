#include "Road.h"
#include "Vector.h"

Road::Road()
: points(), radius(5) { }

Road::~Road() { }

void Road::addPoint(double x, double y) 
{
    points.push_back(Vector(x, y));
}

int Road::getRoadSize() const
{
    return points.size();
}

Vector Road::getPoint(int i) const
{
    return points[i];
}

double Road::getRadius() const
{
    return radius;
}