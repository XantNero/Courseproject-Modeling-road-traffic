#include "../pch.h"

#include "Car.h"
#include "Vector.h"
#include "Road.h"

struct angle
{
    double start;
    double end;
};
static struct 
{
    double pi = 3.14f;
    double infinity = 1000000000000000.0f;
    double epsilon = 0.0000000000000000001f;
    angle lightViewAngle = {0.0f,  pi / 2.0f + 0.01};
    unsigned int lightViewDistance = 75;
    angle yieldViewAngle = {0.0f, pi / 3};
    unsigned int yieldViewDistance = 50;
    angle yieldSideViewAngle = {pi / 6, 4 * pi / 6};
    unsigned int yieldSideViewDistance = 75;
    angle followViewAngle = { 0.0f, pi / 2.0f + 0.01};
    unsigned int followViewDistance = 50;
    double stopSpeed = 1.0f;
    unsigned int turnViewDistance = 50;
    unsigned int standartCarGeneratorRate = 1000;
    unsigned int minMaxSpeed = 100;
    unsigned int maxMaxSpeed = 200;
} Constants;


/*
----------------------------------------------------------------------
|||||||||||||||||||||||Car||||||||||||||||||||||||||||||||||||||||||||
----------------------------------------------------------------------
*/

Car::Car(const Vector& pos)
    : Particle2D(pos), m_MaxSpeed(Constants.minMaxSpeed + rand() % (Constants.maxMaxSpeed - Constants.minMaxSpeed)), m_State(LIVE)
{
    m_Position = pos;
}

Car::Car(const float x, const float y)
    : Particle2D(x, y),  m_MaxSpeed(Constants.minMaxSpeed + rand() % (Constants.maxMaxSpeed - Constants.minMaxSpeed)), m_State(LIVE)
{
    m_Position = Vector(x, y);
}

Car::Car(const Car& copy)
    : Particle2D(copy.m_Position), m_MaxSpeed(copy.m_MaxSpeed), m_State(copy.m_State)
{
    //position = copy.position;
    m_Acceleration = copy.m_Acceleration;
    m_Velocity = copy.m_Velocity;
    m_ForceAccumulator = copy.m_ForceAccumulator;
    m_InverseMass = copy.m_InverseMass;
    m_Damping = copy.m_Damping;
}

void Car::setState(State state, bool value)
{
    if (value)
        this->m_State |= state;
    else
        this->m_State &= ~state;
}

double Car::getMaxSpeed() const
{
    
    if (m_State & State::FOLLOW)
        return m_Velocity.getMagnitude();
    else if (m_State & State::STOP)
        return Constants.stopSpeed;
    
    return m_MaxSpeed;
}

bool Car::followPath(const Road* road, Vector* target)
{  
    Vector predict = m_Velocity;
    predict.setMagnitude(5);
    Vector predictPos = predict + m_Position;
    Vector pos = getPosition();
    double worldRecord = Constants.infinity;
    Vector normal;
    double distance = 0;

    for (int i = 0; i < road->getRoadSize() - 1; ++i) {
        Vector a = road->getPoint(i);
        Vector b = road->getPoint(i + 1);

        Vector normalPoint = getNormalPoint(predictPos, a, b);
        if (!(normalPoint.getX() + road->getRadius() > std::min(a.getX(), b.getX()) && normalPoint.getX() - road->getRadius() < std::max(a.getX(), b.getX())
            && normalPoint.getY() + road->getRadius() > std::min(a.getY(), b.getY()) && normalPoint.getY() - road->getRadius() < std::max(a.getY(), b.getY()))) {
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
            dir.setMagnitude(5);
            (*target) = normal + dir;
            worldRecord = distance; 
            if (normal == road->getPoint(road->getRoadSize() - 1) && normal.distance(getPosition()) < Constants.turnViewDistance)
                setState(State::TURN, true);
        }
    }
    return true;
}  

// bool Car::followPath(const Road* road, Vector* target)
// {  
//     Vector predict = velocity;
//     predict.setMagnitude(getMaxSpeed());
//     Vector predictPos = predict + position;
//     Vector pos = getPosition();
//     double worldRecord = 10000000.;
//     Vector normal;
//     double distance = 0;

//     // if (nowRoadStart == -1) {
//     for (int i = 0; i < road->getRoadSize() - 1; ++i) {
//         Vector a = road->getPoint(i);
//         Vector b = road->getPoint(i + 1);

//         Vector normalPoint = getNormalPoint(predictPos, a, b);
//         if (!(normalPoint.getX() + road->getRadius() > std::min(a.getX(), b.getX()) && normalPoint.getX() - road->getRadius() < std::max(a.getX(), b.getX())
//             && normalPoint.getY() + road->getRadius() > std::min(a.getY(), b.getY()) && normalPoint.getY() - road->getRadius() < std::max(a.getY(), b.getY()))) {
//             // if (getState() & State::TURN) {
//             //     normalPoint = a;
//             // }
//             // else 
//                 normalPoint = b;
//         } 
//             if (getState() & State::TURN) {
//             setState(State::TURN, false);
                        
//             if (road->isMain() == false) {
//                 setState(State::YIELD, true);
//                 setState(State::STOP, false);
//             }
//             else {
//                 setState(State::YIELD | State::STOP, false);
//             }
//         }
        
            
//         distance = predictPos.distance(normalPoint);

//         if (distance < worldRecord) {
            
//             normal = normalPoint;

//             Vector dir = b - a;
//             dir.setMagnitude(m_MaxSpeed);
//             Vector temp = *target;
//             (*target) = normal + dir;
//             Vector mov = *target - getPosition();
//             // if (getVel() * mov == -1.0) {
//             //     target = temp;
//             // }
                
//             worldRecord = distance; 

//             if (normal == road->getPoint(road->getRoadSize() - 1) && normal.distance(getPosition()) < 50)
//                 setState(State::TURN, true);
//         }
//     }
//     return true;
// }  

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
  
    // else {
    //     Vector target = getPos() + getVel();
    //     seek(target);
    // }


void Car::move(float time)
{
    m_Acceleration *= 0;
    m_Acceleration += m_ForceAccumulator;
    std::cout << m_Acceleration.getMagnitude() << '\n';
    m_Velocity += m_Acceleration * time;
    std::cout << m_Velocity.getMagnitude() << ' '; 
    m_Velocity.limitMagnitude(getMaxSpeed());
    std::cout << m_Velocity.getMagnitude() << '\n';
    m_Position += m_Velocity  * time;
    // acceleration *= damping;
    clearAccumulator();    
}

bool Car::view(const Car &car, double startAngle, double endAngle, double d) const
{
    Vector dist = car.getPosition() - getPosition();
    Vector vel = getVelocity();
    double a = dist.getAngle(vel);
    if (dist.getMagnitude() < d && startAngle <= a  && a <= endAngle)
        return true;
    return false;
}

bool Car::view(const TrafficLight &light, double startAngle, double endAngle, double d) const
{
    Vector dist = light.getPosition() - getPosition();
    Vector vel = getVelocity();
    double a = dist.getAngle(vel);
    if (dist.getMagnitude() < d && startAngle <= a && a <= endAngle)
        return true;
    return false;
}

/*
----------------------------------------------------------------------
|||||||||||||||||||||||CarRegistry||||||||||||||||||||||||||||||||||||
----------------------------------------------------------------------
*/

void CarRegistry::addCar(const Car &car, const unsigned int start_roadID)
{ 
    m_Cars.push_back({car, SteerForceGenerator(), BrakeForceGenerator(), start_roadID});
}

void CarRegistry::update(const RoadRegistry &roads, const std::vector<const TrafficLight*> &lights, float time)
{   
    std::list<CarInformation>::iterator it = m_Cars.begin();
    while(it != m_Cars.end()) {
        
        interectLights(it, lights);
        yieldInterect(it, roads);
        turn(it, roads);        
        interectFollow(it, roads);
        if ((it->car.getState() & Car::LIVE) == 0) {
            it = m_Cars.erase(it);
            continue;
        }
        if (it == m_Cars.end())
            break;
        applySteerForce(it->car, it->steerForceGenerator, roads.getRoad(it->roadID));
        //it->car.move(time);
        applyBrakeForce(it->car, it->brakeForceGenerator);
        //it->car.move(time);
        ++it;
    }
    it = m_Cars.begin();
    while(it != m_Cars.end()) {
        it->car.move(time);
        ++it;
    }
    
}

std::vector<Car> CarRegistry::getCars()
{
    std::vector<Car> ret;     
    std::list<CarInformation>::iterator it = m_Cars.begin();
    while(it != m_Cars.end()) {
        ret.push_back(it->car);
        ++it;
    }
    return ret;
}

void CarRegistry::interectLights(std::list<CarInformation>::iterator& it, const std::vector<const TrafficLight*> &lights) 
{
    bool red_fl = false;
    for (unsigned int i = 0; i < lights.size(); ++i) {
        if (it->car.view(*lights[i], Constants.lightViewAngle.start, Constants.lightViewAngle.end, Constants.lightViewDistance)) {
            if (lights[i]->getState() == TrafficLight::State::Red || lights[i]->getState() == TrafficLight::State::Yellow) {
                it->car.setState(Car::State::STOP, true);
                Vector desired = it->car.getVelocity();
                desired.setMagnitude(it->car.getMaxSpeed());
                it->brakeForceGenerator.init(desired, (float)lights[i]->getPosition().distance(it->car.getPosition()));
                red_fl = true;
            }
            break;
        }
    }
    if (!red_fl)
        it->car.setState(Car::State::STOP, false);
}

void CarRegistry::yieldInterect(std::list<CarInformation>::iterator& it, const RoadRegistry &roads)
{
     if ((it->car.getState() & Car::State::YIELD) /*&& (it->car.getState() & Car::State::FOLLOW) == 0*/) {
            std::list<CarInformation>::iterator view_check = m_Cars.begin();
            bool stop_fl = false;
            while(view_check != m_Cars.end()) {
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
                if (fl) {
                    ++view_check;
                    continue;
                }
                if (it->car.view(view_check->car, Constants.yieldViewAngle.start, Constants.yieldViewAngle.end,  Constants.yieldViewDistance)
                    || it->car.view(view_check->car, Constants.yieldSideViewAngle.start, Constants.yieldSideViewAngle.end, Constants.yieldSideViewDistance)) {
                    it->car.setState(Car::State::STOP, true);
                    Vector desired = it->car.getVelocity();
                    desired.setMagnitude(it->car.getMaxSpeed());
                    it->brakeForceGenerator.init(desired, (float)view_check->car.getPosition().distance(it->car.getPosition()));
                    stop_fl = true;
                    break;
                }
                ++view_check;
            }   
            if (!stop_fl)
                it->car.setState(Car::State::STOP, false);
        }
}

void CarRegistry::turn(std::list<CarInformation>::iterator& it, const RoadRegistry &roads)
{
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
        }
        else {  
            it->car.setState(Car::LIVE, false);
        }
    }
}
// if (roads.getRoad(it->roadID)->isMain() == false) {
//     it->car.setState(Car::State::YELL, true);
// }
// else {
//     it->car.setState(Car::State::YELL | Car::State::STOP, false);
// }
void CarRegistry::interectFollow(std::list<CarInformation>::iterator& it, const RoadRegistry &roads)
{
    if ((it->car.getState() & Car::State::TURN) == 0 && (it->car.getState() & Car::State::STOP) == 0) {
        std::list<CarInformation>::iterator view_check = m_Cars.begin();
        bool follow_fl = false;
        while(view_check != m_Cars.end()) {
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
            
            if (it->car.view(view_check->car, Constants.followViewAngle.start, Constants.followViewAngle.end, Constants.followViewDistance)) {
                // if (it->car.getVelocity().getSquareMagnitude() < Constants.epsilon) {
                //     it->car.setState(Car::State::LIVE, false);
                //     break;
                // }
                
                it->car.setState(Car::State::FOLLOW, true);
                Vector desired = it->car.getVelocity();
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
    :m_Position(), m_Rate(Constants.standartCarGeneratorRate)
{ 
    time = std::chrono::steady_clock::now();
}

CarGenerator::CarGenerator(const Vector &pos, const int rate)
    :m_Position(pos), m_Rate(rate)
{
    time = std::chrono::steady_clock::now();
}

void CarGenerator::update(CarRegistry& carRegistry)
{
    auto end = std::chrono::steady_clock::now();
    auto dif = std::chrono::duration_cast<std::chrono::milliseconds>(end - time);
    bool add_fl = true;
    if (dif >= std::chrono::milliseconds(m_Rate)) {
        Car car(m_Position);
        std::vector<Car> cars = carRegistry.getCars();
        for (auto u : cars) {
            if (u.getPosition().distance(m_Position) < Constants.followViewDistance) {
                add_fl = false;
                break;
            }
        }
        if (add_fl)
            carRegistry.addCar(car, m_StartRoadID);
       
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