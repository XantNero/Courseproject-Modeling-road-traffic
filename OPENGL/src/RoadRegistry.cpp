#include "RoadRegistry.h"

RoadRegistry::RoadRegistry()
    :connections(), roads()
{

}
RoadRegistry::~RoadRegistry()
{
}

int RoadRegistry::getRoadIndex(Road* const road) const
{
    for (int i = 0; i < roads.size(); ++i)
        if (road == roads[i])
            return i;
    return -1;
}
Road& RoadRegistry::getRoad(int index) const
{
    return *roads[index];
}
void RoadRegistry::addRoad(Road& road)
{
    roads.push_back(&road);
    connections.push_back(std::vector<int>());
}
void RoadRegistry::connectRoads(int index_from, int index_to)
{
    connections[index_from].push_back(index_to);
}

const std::vector<int>& RoadRegistry::getRoadConnections(int road_index) const
{
    return connections[road_index];
}