#ifndef _CARREGISTRY_H_
#define _CARREGISTRY_H_
#include "Car.h"
#include "RoadRegistry.h"
#include "ForceGenerator.h"
#include "SteerForceGenerator.h"
#include "BrakeForceGenerator.h"
#include <list>
struct CarInformation
{
    Car car;
    SteerForceGenerator steerForceGenerator;
    BrakeForceGenerator brakeForceGenerator;
    int roadIndex;
};


class CarRegistry
{
public:
    CarRegistry();
    ~CarRegistry();

    void addCar(const Car &car, int start_road_index);
    void update(const RoadRegistry &roads, float time);
    std::vector<Car> getCars();
private:
    void applySteerForce(Car &car, SteerForceGenerator& steerForceGenerator, const Road& road);
    void applyBrakeForce(Car &car, BrakeForceGenerator& brakeForceGenerator);
private:
    std::list<CarInformation> cars;
};

#endif