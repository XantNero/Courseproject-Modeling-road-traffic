#include "../pch.h"

#include "Car.h"
#include "Vector.h"
#include "Road.h"

/*
----------------------------------------------------------------------
|||||||||||||||||||||||Car||||||||||||||||||||||||||||||||||||||||||||
----------------------------------------------------------------------
*/

Car::Car(const Vector& pos)
    : Particle2D(pos), maxSpeed(5 + rand() % 4 - 2), state(LIVE)
{
    position = pos;
}

Car::Car(const float x, const float y)
    : Particle2D(x, y),  maxSpeed(5 + rand() % 4 - 2), state(LIVE)
{
    position = Vector(x, y);
}

Car::~Car()
{
}

Car::Car(const Car& copy)
    : Particle2D(copy.position), maxSpeed(copy.maxSpeed), state(copy.state)
{
    //position = copy.position;
    acceleration = copy.acceleration;
    velocity = copy.velocity;
    forceAccumulator = copy.forceAccumulator;
    inverseMass = copy.inverseMass;
    damping = copy.damping;
}

void Car::setState(State state, bool value)
{
    if (value)
        this->state |= state;
    else
        this->state &= ~state;
}

double Car::getMaxSpeed() const
{
    if (state & State::FOLLOW)
        return velocity.getMagnitude();
    else if (state & State::STOP)
        return 0.01f;
    return maxSpeed;
}

bool Car::followPath(const Road* road, Vector* target)
{  
    Vector predict = velocity;
    predict.setMagnitude(getMaxSpeed());
    Vector predictPos = predict + position;
    Vector pos = getPosition();
    double worldRecord = 10000000.;
    Vector normal;
    double distance = 0;

    // if (nowRoadStart == -1) {
         for (int i = 0; i < road->getRoadSize() - 1; ++i) {
            Vector a = road->getPoint(i);
            Vector b = road->getPoint(i + 1);

            Vector normalPoint = getNormalPoint(predictPos, a, b);
            if (!(normalPoint.getX() + road->getRadius() > std::min(a.getX(), b.getX()) && normalPoint.getX() - road->getRadius() < std::max(a.getX(), b.getX())
                && normalPoint.getY() + road->getRadius() > std::min(a.getY(), b.getY()) && normalPoint.getY() - road->getRadius() < std::max(a.getY(), b.getY()))) {
                // if (getState() & State::TURN) {
                //     normalPoint = a;
                // }
                // else 
                    normalPoint = b;
            } 
             if (getState() & State::TURN) {
                setState(State::TURN, false);
                            
                if (road->isMain() == false) {
                    setState(State::YIELD, true);
                    setState(State::STOP, false);
                }
                else {
                    setState(State::YIELD | State::STOP, false);
                }
            }
           
               
            distance = predictPos.distance(normalPoint);

            if (distance < worldRecord) {
                
                normal = normalPoint;

                Vector dir = b - a;
                dir.setMagnitude(maxSpeed);
                Vector temp = *target;
                (*target) = normal + dir;
                Vector mov = *target - getPosition();
                // if (getVel() * mov == -1.0) {
                //     target = temp;
                // }
                    
                worldRecord = distance; 

                if (normal == road->getPoint(road->getRoadSize() - 1) && normal.distance(getPosition()) < 50)
                    setState(State::TURN, true);
            }
        }

   

    // Vector a = road.getPoint(nowRoadStart);
    // Vector b = road.getPoint(nowRoadStart + 1);

    // if (poscheck.getAngle(dir) < asin(road.getRadius() / poscheck.getMagnitude())
    //                 && pos.getX() > std::min(a.getX(), b.getX()) && pos.getX() < std::max(a.getX(), b.getX())
    //                 && pos.getY() > std::min(a.getY(), b.getY()) && pos.getY() < std::max(a.getY(), b.getY())) {
    //                 nowRoadStart = i;
    //             } 


    //}
    // else {
    //     Vector a = road.getPoint(nowRoadStart);
    //     Vector b = road.getPoint(nowRoadStart + 1);
    //     Vector dir = b - a;
    //     Vector poscheck = pos - a;
    //     if (poscheck.getAngle(dir) < asin(road.getRadius() / poscheck.getMagnitude())
    //         && pos.getX() > std::min(a.getX(), b.getX()) && pos.getX() < std::max(a.getX(), b.getX())
    //         && pos.getY() > std::min(a.getY(), b.getY()) && pos.getY() < std::max(a.getY(), b.getY())) { 
    //         target = dir;
    //         target.setMagnitude(getMaxSpeed());
    //         target += pos;
    //         turning = false;
    //     }
    //     else if (turning) {
    //         target = dir;
    //         target.setMagnitude(getMaxSpeed());
    //         a += pos;
    //     }
    //     else {
    //         ++nowRoadStart;
    //         if (nowRoadStart == road.getRoadSize() - 1) {
    //             live = false;
    //             return;
    //         }  
    //         a = b;
    //         b = road.getPoint(nowRoadStart + 1);
    //         dir = b - a;
    //         dir.setMagnitude(getMaxSpeed());
    //         target = a + dir;
    //         turning = true;
    //     } 
    // }
    // if (worldRecord > road->getRadius() || getVelocity().getMagnitude() == 0.0)
    //     return true;
    return true;
    // else {
    //     Vector target = getPos() + getVel();
    //     seek(target);
    // }
}

void Car::move(float time)
{
    acceleration *= 0;
    acceleration += forceAccumulator;
    velocity += acceleration * time;
    velocity.limitMagnitude(maxSpeed * time);
    position += velocity * time;
    // acceleration *= damping;
    clearAccumulator();    
}

Vector Car::getNormalPoint(Vector&p, Vector&a, Vector&b) 
{
    Vector ap = p - a;
    Vector ab = b - a;
    ab.normalize();
    ab *= ab * ap;
    return ab + a;
}

bool Car::view(const Car &car, double angle, double d) const
{
    Vector dist = car.getPosition() - getPosition();
    Vector vel = getVelocity();
    double a = dist.getAngle(vel);
    if (dist.getMagnitude() < d && a < angle)
        return true;
    return false;
}

/*
----------------------------------------------------------------------
|||||||||||||||||||||||CarRegistry||||||||||||||||||||||||||||||||||||
----------------------------------------------------------------------
*/

CarRegistry::CarRegistry()
    :cars()
{

}
CarRegistry::~CarRegistry()
{

}

void CarRegistry::addCar(const Car &car, const unsigned int start_roadID)
{ 
    cars.push_back({car, SteerForceGenerator(), BrakeForceGenerator(), start_roadID});
}

void CarRegistry::update(const RoadRegistry &roads, float time)
{   
    std::list<CarInformation>::iterator it = cars.begin();
    while(it != cars.end()) {
        
         if ((it->car.getState() & Car::State::YIELD) && (it->car.getState() & Car::State::FOLLOW) == 0) {
            std::list<CarInformation>::iterator view_check = cars.begin();
            bool stop_fl = false;
            while(view_check != cars.end()) {
                if (/*it->roadID == view_check->roadID || */&it->car == &view_check->car) {
                    ++view_check;
                    continue;
                }
                bool fl = false;
                std::vector<unsigned int> conn = roads.getRoadConnections(view_check->roadID);
                for (auto u : conn) {
                    if (it->roadID == u) {
                        fl = true;
                        break;
                    }
                }
                // if (it->roadID == view_check->roadID)
                //     fl = true;
                if (fl) {
                    ++view_check;
                    continue;
                }
                
                if (it->car.view(view_check->car, 4 * 3.14 / 6, 75)) {
                    
                    it->car.setState(Car::State::STOP, true);
                    Vector desired = it->car.getVelocity();
                    desired.setMagnitude(0.01);
                    it->brakeForceGenerator.init(desired, (float)view_check->car.getPosition().distance(it->car.getPosition()));
                    stop_fl = true;
                    break;
                }
                ++view_check;
            }   
            if (!stop_fl)
                it->car.setState(Car::State::STOP, false);
        }



        if (it->car.getState() & Car::TURN) {
            std::vector<unsigned int> conn = roads.getRoadConnections(it->roadID);
            if (conn.size() != 0) {
                    double prob = (double)(std::rand() % 100) / 100; // change
                int i = 0;
                while (prob > 1.0f / conn.size()) {
                    prob -= 1.0f / conn.size();
                    ++i;
                }
                it->roadID = conn[i];
                // if (roads.getRoad(it->roadID)->isMain() == false) {

                //     it->car.setState(Car::State::YELL, true);
                // }
                // else {
                //     it->car.setState(Car::State::YELL | Car::State::STOP, false);
                // }
            }
            else {
                it->car.setState(Car::LIVE, false);
            }
        }

        std::list<CarInformation>::iterator view_check = cars.begin();
        bool follow_fl = false;
        if ((it->car.getState() & Car::State::TURN) == 0) {
             while(view_check != cars.end()) {
                if (&it->car == &view_check->car) {
                    ++view_check;
                    continue;
                }
                bool fl = false;
                std::vector<unsigned int> conn = roads.getRoadConnections(it->roadID);
                for (auto u : conn) {
                    if (view_check->roadID == u) {
                        fl = true;
                        break;
                    }
                }
                if (it->roadID == view_check->roadID)
                    fl = true;
                if (!fl) {
                    ++view_check;
                      continue;
                }
                  
                if (it->car.view(view_check->car, 3.14 / 2 + 0.1, 50)) {
                    if (it->car.getVelocity().getSquareMagnitude() == 0) {
                        it->car.setState(Car::State::LIVE, false);
                        break;
                    }
                    
                    it->car.setState(Car::State::FOLLOW, true);
                    Vector desired = view_check->car.getVelocity();
                    desired.setMagnitude(view_check->car.getMaxSpeed());
                    it->brakeForceGenerator.init(desired, (float)view_check->car.getPosition().distance(it->car.getPosition()));
                    follow_fl = true;
                    break;
                }
                ++view_check;
            }   
            if (!follow_fl)
                it->car.setState(Car::State::FOLLOW, false);
        }
       



        if ((it->car.getState() & Car::LIVE) == 0) {
            it = cars.erase(it);
            continue;
        }
        if (it == cars.end())
            break;
        
       

       
        applySteerForce(it->car, it->steerForceGenerator, roads.getRoad(it->roadID));
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

void CarRegistry::applySteerForce(Car &car, SteerForceGenerator& steerForceGenerator, const Road* road) //think about ForceGenerator
{
    Vector target;
    if (car.followPath(road, &target)) {
        steerForceGenerator.setTarget(target);
        steerForceGenerator.updateForce(&car, 0);
    }
}
void CarRegistry::applyBrakeForce(Car &car, BrakeForceGenerator& brakeForceGenerator)
{
   if ((car.getState() & Car::State::FOLLOW) || (car.getState() & Car::State::STOP)) {
        brakeForceGenerator.updateForce(&car, 0);
    }

}

/*
----------------------------------------------------------------------
|||||||||||||||||||||||CarGenerator|||||||||||||||||||||||||||||||||||
----------------------------------------------------------------------
*/

CarGenerator::CarGenerator() 
    :position(), rate(300)
{ 
    time = std::chrono::steady_clock::now();
}

CarGenerator::CarGenerator(const Vector &pos, const int rate)
    :position(pos), rate(rate)
{
    time = std::chrono::steady_clock::now();
}

CarGenerator::~CarGenerator()
{
}

void CarGenerator::update(CarRegistry& cars)
{
    // static int i = 0;
    // if (i == 1)
    //     (*position) += Vector(0, 70);
    auto end = std::chrono::steady_clock::now();
    auto dif = std::chrono::duration_cast<std::chrono::milliseconds>(end - time);
    if (dif >= std::chrono::milliseconds(rate)/* && i < 2*/) {
        Car car(position);
        // if (i == 0)
        //     car.setMaxSpeed(3.0f);
        // else 
        //    car.setMaxSpeed(7.0f);
        cars.addCar(car, m_StartRoadID);
        time = std::chrono::steady_clock::now();
        //++i;
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