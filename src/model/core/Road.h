#ifndef _ROAD_H_
#define _ROAD_H_
#include <vector>
#include <memory>
#include <unordered_map>
#include "Vector.h"
class Road
{
public:
    Road(unsigned int id, bool main = true)
        : m_Points(), m_Radius(0), m_ID(id), m_Main(false) { }
    ~Road() { }
    inline void addPoint(double x, double y) 
        { m_Points.push_back(Vector(x, y)); }
    inline int getRoadSize() const { return m_Points.size(); }
    //TODO: EXEPTION 
    inline Vector getPoint(int i) const { return m_Points[i]; }
    inline double getRadius() const { return m_Radius; }
    inline unsigned int getID() const { return m_ID; }
    inline bool isMain() const { return m_Main; }
    inline void setMain(bool value) { m_Main = value; }
    // inline void addTrafficLight(TrafficLight* light) {m_TrafficLights.push_back(std::make_shared<TrafficLight>(light)); }
    // inline const std::vector<std::shared_ptr<TrafficLight>>& getTrafficLights() const
    //     { return m_TrafficLights; }
private:
    std::vector <Vector> m_Points;
    //std::vector<std::shared_ptr<TrafficLight>> m_TrafficLights;
    double m_Radius;
    unsigned int m_ID;
    bool m_Main;
};

class RoadRegistry
{
public:
    RoadRegistry() : connections(), roads(), m_hash() { }
    ~RoadRegistry() { }

    const Road* getRoad(const unsigned int roadID) const;
    const std::vector<const Road*> getRoads() const;
    void addRoad(std::unique_ptr<Road> road);
    void connectRoads(const unsigned int ID_from, const unsigned int ID_to);
    const std::vector<unsigned int>& 
    getRoadConnections(const unsigned int roadID) const;
    unsigned int getRoadsCount() const;
private:
    std::vector<std::vector<unsigned int>> connections;
    std::vector<std::unique_ptr<Road>> roads;
    mutable std::unordered_map<unsigned int, unsigned int> m_hash;
};

#endif