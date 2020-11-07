#ifndef _ROADREGISTRY_H_
#define _ROADREGISTRY_H_
#include "Road.h"
#include <memory>
#include <unordered_map>
#include <vector>

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