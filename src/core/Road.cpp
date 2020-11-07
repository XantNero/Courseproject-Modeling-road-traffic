#include "Road.h"
#include "Vector.h"

unsigned int Road::s_LastID = 0;

Road::Road()
: points(), radius(5), m_ID(s_LastID++) { }

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

unsigned int Road::getID() const
{
    return m_ID;
}