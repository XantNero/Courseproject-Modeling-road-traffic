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
    cars.push_back({car, SteerForceGenerator(), BrakeForceGenerator(), start_road_index});
}
void CarRegistry::update(const RoadRegistry &roads, float time)
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
       
        applySteerForce(it->car, it->steerForceGenerator, roads.getRoad(it->roadIndex));
        //it->car.move(time);
        applyBrakeForce(it->car, it->brakeForceGenerator);
        //it->car.move(time);
        ++it;
    }
    it = cars.begin();
    while(it != cars.end()) {
        it->car.move(time);
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

void CarRegistry::applySteerForce(Car &car, SteerForceGenerator& steerForceGenerator, const Road& road) //think about ForceGenerator
{
    Vector target;
    if (car.followPath(road, &target)) {
        steerForceGenerator.setTarget(target);
        steerForceGenerator.updateForce(&car, 0);
    }
        
    
}
void CarRegistry::applyBrakeForce(Car &car, BrakeForceGenerator& brakeForceGenerator)
{
    std::list<CarInformation>::iterator it = cars.begin();
    while(it != cars.end()) {
        if (&it->car == &car) {
            ++it;
            continue;
        }
         
        if (car.view(it->car)) {
            brakeForceGenerator.init(it->car.getVelocity(), (float)it->car.getPosition().distance(car.getPosition()));
            brakeForceGenerator.updateForce(&car, 0);
            break;
        }
        ++it;
    }   
}