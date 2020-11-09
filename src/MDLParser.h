#ifndef _MDLPARSER_H_
#define _MDLPARSER_H_
#include "core/Car.h"
#include "core/Road.h"
#include <memory>
#include <vector>
#include <string>

struct ParseInformation
{
    RoadRegistry* roadRegistry;
    std::vector<CarGenerator*> CarGenerators;
};

class MDLParser
{
public:
    static const ParseInformation parseFile(const std::string& filePath); 
private:
    static RoadRegistry* parseRoads(std::ifstream& file);
    static std::vector<CarGenerator*> parseCarGenerators(std::ifstream& file);
};

#endif