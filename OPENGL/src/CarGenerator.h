#ifndef _CARGENERATOR_H_
#define _CARGENERATOR_H_
#include "Vector.h"
#include "Car.h"
#include "Road.h"
#include <list>
#include <chrono>
#include <vector>

class CarGenerator
{
private:
    Vector* position;
    std::list <Car> Cars;
    int rate;
    std::chrono::time_point<std::chrono::steady_clock> time;
public:
    CarGenerator(const Vector &pos, const int rate = 2000);
    ~CarGenerator();
    void update(const Road &road); //change to array of roads, roads connections
    std::vector<Car> getCars() const;
};

#endif