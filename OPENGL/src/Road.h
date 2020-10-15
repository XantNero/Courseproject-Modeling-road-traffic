#ifndef _ROAD_H_
#define _ROAD_H_
#include <vector>
#include "Vector.h"
class Road
{
private:
    std::vector <Vector> points;
    double radius;
public:
    Road();
    ~Road();
    void addPoint(double x, double y);
    int getRoadSize() const;
    Vector getPoint(int) const;
    double getRadius() const;
};


#endif