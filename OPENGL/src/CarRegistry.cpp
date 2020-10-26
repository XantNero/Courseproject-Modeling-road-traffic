#include "CarRegistry.h"
#include <iostream>

CarRegistry::CarRegistry()
    :cars()
{

}
CarRegistry::~CarRegistry()
{

}

void CarRegistry::addCar(const Car &car, int start_road_index)
{
    cars.push_back({car, start_road_index});
}
void CarRegistry::update(const RoadRegistry &roads)
{   
    std::list<CarInformation>::iterator it = cars.begin();
    while(it != cars.end()) {
        
        if (it->car.getState() == Car::TURN) {
            std::vector<int> conn = roads.getRoadConnections(it->roadIndex);
            if (conn.size() != 0) {
                    double prob = (double)(std::rand() % 100) / 100; // change
                int i = 0;
                while (prob > 1.0f / conn.size()) {
                    prob -= 1.0f / conn.size();
                    ++i;
                }
                it->roadIndex = conn[i];
                it->car.setState(Car::LIVE);
            }
            else {
                it->car.setState(Car::DEAD);
            }
        }
        if (it->car.getState() == Car::DEAD) {
            it = cars.erase(it);
        }
        if (it == cars.end())
            break;
        it->car.followPath(roads.getRoad(it->roadIndex));
        it->car.move();
        ++it;
    }
}

std::vector<Car> CarRegistry::getCars()
{
    std::vector<Car> ret;     
    std::list<CarInformation>::iterator it = cars.begin();
    while(it != cars.end()) {
        ret.push_back(it->car);
        ++it;
    }
    return ret;
}