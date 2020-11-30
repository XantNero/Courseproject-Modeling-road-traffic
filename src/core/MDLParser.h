#ifndef _MDLPARSER_H_
#define _MDLPARSER_H_
#include "Car.h"
#include "Road.h"
#include <memory>
#include <vector>
#include <string>

struct ParseInformation
{
    RoadRegistry* roadRegistry;
    std::vector<CarGenerator*> CarGenerators;
};

struct RoadGraph
{
    std::vector<std::vector<int>> connections;
    std::vector<std::vector<int>> back_connections;
};


class MDLParser
{
public:
    static const ParseInformation parseFile(const std::string& filePath); 
private:
    static RoadRegistry* parseRoads(std::ifstream& file);
    static std::vector<CarGenerator*> parseCarGenerators(std::ifstream& file);
    static std::vector<Vector> parsePoints(std::ifstream& file, std::vector<bool>& road_value);
    static RoadGraph parseConnections(std::ifstream& file);
    static void constructRoads(RoadGraph& graph, int x, RoadRegistry* roadRegistry, std::vector<Vector>& points, std::vector<bool> &vis, std::vector<bool>& roadValue);
    static void connectRoads(RoadGraph& graph, RoadRegistry* roadRegistry);
};

#endif