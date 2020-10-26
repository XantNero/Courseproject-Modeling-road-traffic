#include "CarGenerator.h"
#include <math.h>

CarGenerator::CarGenerator(const Vector &pos, const int rate)
    :position(new Vector(pos)), rate(rate)
{
    time = std::chrono::steady_clock::now();
}

CarGenerator::~CarGenerator()
{
    delete position;
}

void CarGenerator::update(CarRegistry& cars)
{
    auto end = std::chrono::steady_clock::now();
    auto dif = std::chrono::duration_cast<std::chrono::milliseconds>(end - time);
    if (dif >= std::chrono::milliseconds(rate)) {
        Car car(*position);
        cars.addCar(car, 0);
        time = std::chrono::steady_clock::now();
    }
}

// void CarGenerator::avoidColision() //change name
// {
//     std::list<Car>::iterator itCheckCar = Cars.begin();

//     while(itCheckCar != Cars.end()) {
//         Vector Steer;
//         bool findCollision = false;
//         // Vector predict = itCheckCar->getVel();
//         // predict.setMagnitude(5 * itCheckCar->getMaxSpeed());
//         Vector CheckCarPosition = itCheckCar->getPos()/* + predict*/;
//         std::list<Car>::iterator itNextCar = Cars.begin();
//         while (itNextCar != Cars.end()) {   
//             if (itCheckCar == itNextCar) {
//                 ++itNextCar;
//                 continue;
//             }
//             findCollision = false;
//             Vector NextCarPosition = itNextCar->getPos();
//             Vector CheckVel = itCheckCar->getVel();
//             Vector NextVel = itNextCar->getVel();
//             Vector mag = CheckVel.getMagnitude();

//             Vector desired = itNextCar->getPos() - itCheckCar->getPos();
//             Vector msf = desired.getMagnitude();
//             double angle = CheckVel.getAngle(desired) / 3.14;
//             Vector c = itCheckCar->getPos();

//             if (/*NextCarPosition.distance(CheckCarPosition) < 100 &&*/ itCheckCar->view(*itNextCar)
//             /* && itNextCar->getRoadLocation() - itCheckCar->getRoadLocation() <= 1*//*&& angle < 5*/) { // made constant
                
//                 desired = CheckVel;
//                 desired.setMagnitude(NextVel.getMagnitude());
//                 desired.limitMagnitude(itCheckCar->getMaxSpeed());
//                 // desired -= itCheckCar->getPos();
//                 //Vector desired = itCheckCar->getVel();
//                 // if (dist.getMagnitude() < 10)
//                 //     mag = itCheckCar->getMaxSpeed();
//                 // else  
//                 //     mag = itCheckCar->getMaxSpeed() / dist.getMagnitude();
//                 // if (dist.getMagnitude() < 1)
//                 //     desired.setMagnitude(itCheckCar->getMaxSpeed() / 2);
//                 // else
//                 //     desired.setMagnitude(desired.getMagnitude() / dist.getMagnitude());
//                 // desired *= -1;
//                 // desired.setMagnitude(1);
//                 //desired.limitMagnitude(itCheckCar->getMaxSpeed() - 0.5);
//                 //desired /= 70;
//                 // desired.setMagnitude(desired.getMagnitude() / (200 * itCheckCar->getMaxSpeed() / dist.getMagnitude()));
                
//                 // if (desired.getMagnitude() > itCheckCar->getMaxSpeed())
//                 //     desired.setMagnitude(itCheckCar->getMaxSpeed());

//                 // desired.setMagnitude(itCheckCar->getMaxSpeed());
//                 // desired /= 1000;
    
//                 CheckVel.setMagnitude(itCheckCar->getMaxSpeed());
//                 Steer = desired - CheckVel;
//                 //Steer -= itCheckCar->getVel();
//                 // Steer *= -1;
//                 Steer.limitMagnitude(itCheckCar->getMaxSpeed());

//                 findCollision = true;
//             } 
//             ++itNextCar;
//             if (findCollision == true) {
//                  itCheckCar->applyForce(Steer);
//                  break;
//             }
               
//         }
//          // change to new seek
//         ++itCheckCar;
//     }
// }
