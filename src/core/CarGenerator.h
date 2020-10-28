#ifndef _CARGENERATOR_H_
#define _CARGENERATOR_H_
#include "Vector.h"
#include "Car.h"
#include "Road.h"
#include <list>
#include <chrono>
#include <vector>
#include "CarRegistry.h"

class CarGenerator
{
private:
    Vector* position;
    int rate;
    std::chrono::time_point<std::chrono::steady_clock> time;
public:
    CarGenerator(const Vector &pos, const int rate = 300);
    int getRate() const;
    void setRate(int rate);
    ~CarGenerator();
    void update(CarRegistry &cars); //change to array of roads, roads connections
   // void avoidColision(); //change name
};

#endif