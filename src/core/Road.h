#ifndef _ROAD_H_
#define _ROAD_H_
#include <vector>
#include <memory>
#include <unordered_map>
#include "Vector.h"
class Road
{
public:
    Road(unsigned int id) : points(), radius(1), m_ID(id) { }
    ~Road() { }
    inline void addPoint(double x, double y) { points.push_back(Vector(x, y)); }
    inline int getRoadSize() const { return points.size(); }
    //TODO: EXEPTION 
    inline Vector getPoint(int i) const { return points[i]; }
    inline double getRadius() const { return radius; }
    inline unsigned int getID() const { return m_ID; }
private:
    std::vector <Vector> points;
    double radius;
    unsigned int m_ID;
};

class RoadRegistry
{
public:
    RoadRegistry();
    ~RoadRegistry();

    const Road* getRoad(const unsigned int roadID) const;
    const std::vector<const Road*> getRoads() const;
    void addRoad(std::unique_ptr<Road> road);
    void connectRoads(const unsigned int ID_from, const unsigned int ID_to);
    const std::vector<unsigned int>& getRoadConnections(const unsigned int roadID) const;
    unsigned int getRoadsCount() const;
private:
    std::vector<std::vector<unsigned int>> connections;
    std::vector<std::unique_ptr<Road>> roads;
    mutable std::unordered_map<unsigned int, unsigned int> m_hash;
};

#endif