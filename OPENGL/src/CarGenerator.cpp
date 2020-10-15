#include "CarGenerator.h"

CarGenerator::CarGenerator(const Vector &pos, const int rate)
    :position(new Vector(pos)), Cars(std::list<Car>()), rate(rate)
{
    time = std::chrono::steady_clock::now();
}

CarGenerator::~CarGenerator()
{
    delete position;
}

void CarGenerator::update(const Road &road)
{
    auto end = std::chrono::steady_clock::now();
    auto dif = std::chrono::duration_cast<std::chrono::milliseconds>(end - time);
    if (dif >= std::chrono::milliseconds(rate)) {
        Car car(*position);
        Cars.push_back(car);
        time = std::chrono::steady_clock::now();
    }

    std::list<Car>::iterator it = Cars.begin();

    while(it != Cars.end()) {
        if (it->getLive() == false) {
            it = Cars.erase(it);
        }
        if (it == Cars.end())
            break;
        it->followPath(road);
        it->move();
        ++it;
    }
}

std::vector<Car> CarGenerator::getCars() const
{
    return std::vector<Car> (Cars.begin(), Cars.end());
    //return Cars;
}