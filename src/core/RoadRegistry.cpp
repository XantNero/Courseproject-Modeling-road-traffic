#include "../pch.h"

#include "RoadRegistry.h"

RoadRegistry::RoadRegistry()
    :connections(), roads(), m_hash()
{

}
RoadRegistry::~RoadRegistry()
{
}

const Road* RoadRegistry::getRoad(const unsigned int roadID) const
{
    if (m_hash.find(roadID) != m_hash.end())
        return roads[m_hash[roadID]].get();
    return nullptr;
}

const std::vector<const Road*> RoadRegistry::getRoads() const
{
    std::vector<const Road*> ret(roads.size());
    for (unsigned int i = 0; i < roads.size(); ++i) {
        ret[i] =roads[i].get();
    }
    return ret;
}
void RoadRegistry::addRoad(std::unique_ptr<Road> road)
{
    m_hash[road->getID()] = connections.size();
    roads.push_back(std::move(road));
    connections.push_back(std::vector<unsigned int>());
}
void RoadRegistry::connectRoads(const unsigned int ID_from, const unsigned int ID_to)
{
    if (m_hash.find(ID_from) != m_hash.end())
    connections[m_hash[ID_from]].push_back(ID_to);
}

const std::vector<unsigned int>& RoadRegistry::getRoadConnections(const unsigned int roadID) const
{
    if (m_hash.find(roadID) != m_hash.end())
    return connections[m_hash[roadID]];
}