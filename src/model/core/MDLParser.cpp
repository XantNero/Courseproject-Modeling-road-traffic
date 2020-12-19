#include "../pch.h"
#include "MDLParser.h"
#include <cstdio>

static std::unordered_multimap<int, std::pair<int, int>> m;
static std::set<std::pair<int, int>> roadType;


const ParseInformation MDLParser::parseFile(const std::string& filePath) 
{
    static std::string keyWords[] = {
        "#CarGenerators",
        "#Roads",
        "#Connections",
        "#Points",
        "#TrafficLights"
    };
    ParseInformation info;
    std::ifstream file(filePath);
    std::string line;
    std::vector<Vector> points;
    std::vector<bool> vis;
    RoadGraph graph;
    std::vector<int> lightsConnections;
    while(getline(file, line)) {
        if (line == "#CarGenerators")
            info.CarGenerators = parseCarGenerators(file);
        else if (line == "#Points")
            points = parsePoints(file);
        else if (line == "#Connections")
            graph = parseConnections(file);
        else if (line == "#TrafficLights")
            info.TrafficLights = parseTrafficLights(file, lightsConnections);
    }
    for (int i = 0; i < info.TrafficLights.size(); ++i) {
        info.TrafficLights[i]->setPosition(points[lightsConnections[i]]);
    }
    vis.resize(points.size(), false);
    info.roadRegistry = new RoadRegistry();
    for (int i = 0; i < info.CarGenerators.size(); ++i) {
        info.CarGenerators[i]->
            setPosition(points[info.CarGenerators[i]->getStartRoadId()]);
    }
    for (int i = 0; i < points.size(); ++i) {
        if (!vis[i])
            constructRoads(graph, i, info.roadRegistry, points, vis);
    }
    connectRoads(graph, info.roadRegistry);
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
        unsigned int rate;
        sscanf(line.c_str(), "%d%f%f%d", &startID, &x, &y, &rate);
        CarGenerator* generator = new CarGenerator(Vector(x, y), rate);
        generator->setStartRoadID(startID);
        generators.push_back(generator);
    }
    return generators;
}

std::vector<Vector> MDLParser::parsePoints(std::ifstream& file) 
{
    std::string line;
    std::vector<Vector> points;
    while (getline(file, line)) {
        if (line == "}")
            break;
        if (line == "" || line == "{")
            continue;
        int ID;
        float x, y;
        sscanf(line.c_str(), "%d%f%f", &ID, &x, &y);
        points.push_back(Vector(x, y));
    }
    return points;
}

std::vector<TrafficLight*>
MDLParser::parseTrafficLights(std::ifstream& file,
                              std::vector<int>& lightsConnections) 
{
    std::string line;
    std::vector<TrafficLight*> lights;
    while (getline(file, line)) {
        if (line == "}")
            break;
        if (line == "" || line == "{")
            continue;
        int ConnectionID;
        float x, y;
        int green, yellow, red;
        sscanf(line.c_str(), "%d%f%f%d%d%d",
               &ConnectionID, &x, &y, &green, &yellow, &red);
        TrafficLight::State state;
        if (green <= yellow) {
            if (green <= red)
                state = TrafficLight::State::Green;
            else 
                state = TrafficLight::State::Red;
        }
        else {
            state = TrafficLight::State::Yellow;
        }
        TrafficLight* light =
            new TrafficLight(Vector(x, y), state,
            green * 1000, yellow * 1000, red * 1000);
        lights.push_back(light);
        lightsConnections.push_back(ConnectionID);
    }
    return lights;
}


RoadGraph MDLParser::parseConnections(std::ifstream& file) 
{
    std::string line;
    RoadGraph graph;
    while (getline(file, line)) {
        if (line == "}")
            break;
        if (line == "" || line == "{")
            continue;
        int IDfrom, IDto, type;
        sscanf(line.c_str(), "%d%d%d", &IDfrom, &IDto, &type);
        if (!type)
            roadType.insert({IDfrom, IDto});
        if (IDfrom >= graph.connections.size()) {
            graph.connections.resize(IDfrom + 1);
        }
        graph.connections[IDfrom].push_back(IDto);
        if (IDto >= graph.back_connections.size()) {
            graph.back_connections.resize(IDto + 1);
        }
        graph.back_connections[IDto].push_back(IDfrom);
    }
    if (graph.connections.size() != graph.back_connections.size()) {
        graph.connections.resize(std::max(graph.connections.size(),
                                          graph.back_connections.size()));
        graph.back_connections.resize(std::max(graph.connections.size(),
                                               graph.back_connections.size()));
    }
    return graph;
}

void MDLParser::constructRoads(RoadGraph& graph,
                               int x, RoadRegistry* roadRegistry,
                               std::vector<Vector>& points,
                               std::vector<bool>& vis) 
{
    static unsigned int lastID = points.size();
    while (graph.back_connections[x].size() == 1 &&
           graph.connections[x].size() <= 1) {
        x = graph.back_connections[x][0];
    }
    vis[x] = true;
    bool road_value = false;
    for (unsigned int i = 0; i < graph.connections[x].size(); ++i) {
        std::unique_ptr<Road> road=
            std::make_unique<Road>(i == 0 ? x : lastID++);
        road_value = false;
        road->addPoint(points[x].getX(), points[x].getY());
        std::queue<int> queue;
        int it = graph.connections[x][i];
        queue.push(it);
        while (graph.back_connections[it].size() == 1 &&
               graph.connections[it].size() == 1) {
            vis[it] = true;
            it = graph.connections[it][0];
            queue.push(it);
        }
         if (graph.back_connections[it].size() == 1 &&
             graph.connections[it].size() == 0)
            vis[it] = true;
          if (i != 0)
            m.insert({x, {lastID - 1, it}});
        else 
            m.insert({x, {x, it}});
        std::pair<int, int> key;
        key.first = x;
        while (!queue.empty()) {
            road->addPoint(points[queue.front()].getX(),
                           points[queue.front()].getY());
            key.second = queue.front();
            if (!roadType.count(key))
                road_value = true;
            key.first = queue.front();
            queue.pop();
        }
        road->setMain(road_value);
        roadRegistry->addRoad(std::move(road));
    }
    
}

//TODO:   \    /
//        ----------
//        /    \


void MDLParser::connectRoads(RoadGraph& graph, RoadRegistry* roadRegistry) 
{
    std::pair<std::unordered_multimap<int, std::pair<int, int>>::iterator,
            std::unordered_multimap<int, std::pair<int, int>>::iterator> start;
    std::pair<std::unordered_multimap<int, std::pair<int, int>>::iterator,
            std::unordered_multimap<int, std::pair<int, int>>::iterator> end;
    std::unordered_multimap<int, std::pair<int, int>>::iterator it;
    std::unordered_multimap<int, std::pair<int, int>>::iterator jt;
    for (unsigned int i = 0; i < graph.connections.size(); ++i) {
        start = m.equal_range(i);
        for (it = start.first; it != start.second; ++it) {
            end = m.equal_range(it->second.second);
            for (jt = end.first; jt != end.second; ++jt) {
                roadRegistry->connectRoads(it->second.first, jt->second.first);
            }
        }
        // if (graph.connections[i].size() > 1) {
        //     int x = i;
        //     x = graph.back_connections[x][0];
        //     while (graph.back_connections[x].size() == 1 &&
        //            graph.connections[x].size() == 1) {
        //         x = graph.back_connections[x][0];
        //     }
        //     if (roadRegistry->getRoad(i) != nullptr)
        //         //roadRegistry->connectRoads(x, i);
        //         result = m.equal_range(i);
        //         for (it = result.first; it != result.second; ++it) {
        //                 if (roadRegistry->getRoad(it->second.first) != nullptr)
        //                 roadRegistry->connectRoads(x, it->second.first);
        //         }
        //     // it = result.first;  
        //     // if (roadRegistry->getRoad(graph.connections[i][0]) != nullptr)
        //     //     roadRegistry->connectRoads(i, graph.connections[i][0]);
        //     // for (unsigned int j = graph.connections[i].size() - 1; j > 0; --j) {
        //     //     if (roadRegistry->getRoad(graph.connections[i][j]) != nullptr)
        //     //         roadRegistry->connectRoads(it->second, graph.connections[i][j]);
        //     //     ++it;
        //     // }
        // }
        // else if (graph.back_connections[i].size() > 1) {
        //     for (unsigned int j = 0;
        //          j < graph.back_connections[i].size();
        //          ++j) {
        //         int x = graph.back_connections[i][j];
        //         // if (graph.connections[x].size() != 1)
        //         //     continue;
        //         while (graph.back_connections[x].size() == 1 && 
        //                graph.connections[x].size() == 1) {
        //             x = graph.back_connections[x][0];
        //         }
        //         // if (graph.connections[x].size() != 1)
        //         //     continue;
        //         result = m.equal_range(x);
        //         for (it = result.first; it != result.second; ++it) {
        //             if (roadRegistry->getRoad(i) != nullptr &&
        //                 i == it->second.second) {
        //                 roadRegistry->connectRoads(it->second.first, i);
        //             }
        //         }
        //         // if (roadRegistry->getRoad(i) != nullptr)
        //         //     roadRegistry->connectRoads(x, i);
        //     }
        // }
    }
}