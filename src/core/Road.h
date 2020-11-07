#ifndef _ROAD_H_
#define _ROAD_H_
#include <vector>
#include "Vector.h"
class Road
{
public:
    Road();
    ~Road();
    Road(const Road&) = delete;
    void addPoint(double x, double y);
    int getRoadSize() const;
    Vector getPoint(int) const;
    double getRadius() const;
    unsigned int getID() const;
private:
    std::vector <Vector> points;
    double radius;
    unsigned int m_ID;

    static unsigned int s_LastID;
};


#endif