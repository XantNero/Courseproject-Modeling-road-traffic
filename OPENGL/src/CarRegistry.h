#ifndef _CARREGISTRY_H_
#define _CARREGISTRY_H_
#include "Car.h"
#include "RoadRegistry.h"
#include <list>
struct CarInformation
{
    Car car;
    int roadIndex;
};


class CarRegistry
{
public:
    CarRegistry();
    ~CarRegistry();

    void addCar(const Car &car, int start_road_index);
    void update(const RoadRegistry &roads);
    std::vector<Car> getCars();
private:
    std::list<CarInformation> cars;
};

#endif