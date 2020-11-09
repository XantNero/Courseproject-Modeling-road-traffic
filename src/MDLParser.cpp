#include "pch.h"
#include "MDLParser.h"
#include <cstdio>

const ParseInformation MDLParser::parseFile(const std::string& filePath) 
{
    static std::string keyWords[] = {
        "#CarGenerators",
        "#Roads",
    };
    ParseInformation info;
    std::ifstream file(filePath);
    std::string line;
    while(getline(file, line)) {
        if (line == "#CarGenerators")
            info.CarGenerators = parseCarGenerators(file);
        else if (line == "#Roads")
            info.roadRegistry = parseRoads(file);
    }
    file.close();
    return info;
}

RoadRegistry* MDLParser::parseRoads(std::ifstream& file) 
{
    std::string line;
    RoadRegistry* registry = new RoadRegistry();
    while (getline(file, line)) {
        if (line == "}" || line == "#Connections")
            break;
        if (line == "" || line == "{")
            continue;
        int ID, count;
        sscanf(line.c_str(), "%d%d", &ID, &count);
        std::unique_ptr<Road> road = std::make_unique<Road>(ID);
        for (unsigned int i = 0; i < count; ++i) {
            getline(file, line);
            float x, y;
            sscanf(line.c_str(), "%f%f", &x, &y);
            road->addPoint(x, y);
        }
        registry->addRoad(std::move(road));
    }
    while (getline(file, line)) {
        if (line == "}")
            break;
        if (line == "" || line == "{")
            continue;
        int IDfrom, IDto;
        sscanf(line.c_str(), "%d%d", &IDfrom, &IDto);
        registry->connectRoads(IDfrom, IDto);
    }
    return registry;
}

std::vector<CarGenerator*> MDLParser::parseCarGenerators(std::ifstream& file) 
{
    std::string line;
    std::vector<CarGenerator*> generators;
    while (getline(file, line)) {
        if (line == "}")
            break;
        if (line == "" || line == "{")
            continue;
        int startID;
        float x, y;
        sscanf(line.c_str(), "%d%f%f", &startID, &x, &y);
        CarGenerator* generator = new CarGenerator(Vector(x, y));
        generator->setStartRoadID(startID);
        generators.push_back(generator);
    }
    return generators;
}
