#ifndef _ROADREGISTRY_H_
#define _ROADREGISTRY_H_
#include "Road.h"
#include <vector>

class RoadRegistry
{
public:
    RoadRegistry();
    ~RoadRegistry();

    int getRoadIndex(Road* const) const;
    Road& getRoad(int index) const;
    void addRoad(Road&);
    void connectRoads(int index_from, int index_to);
    const std::vector<int>& getRoadConnections(int road_index) const;
private:
    std::vector<std::vector<int>> connections;
    std::vector<Road*> roads;
};


#endif