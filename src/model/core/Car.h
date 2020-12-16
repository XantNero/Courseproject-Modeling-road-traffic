#ifndef _CAR_H_
#define _CAR_H_
#include <list>
#include <chrono>

#include "Vector.h"
#include "Road.h"
#include "TrafficLight.h"
#include "Particle.h"
#include "ForceGenerator.h"


class Car : public Particle2D
{
public:
    enum State{
        LIVE    = 1L << 0,
        TURN    = 1L << 1,
        FOLLOW  = 1L << 2,
        YIELD    = 1L << 3,
        STOP    = 1L << 4
    };
public:
    Car(const Vector& position);
    Car(float x, float y);
    ~Car() {}
    Car(const Car& );
    inline virtual void applyForce(const Vector &force) override { m_ForceAccumulator += force; }
    virtual void move(float time) override;
    bool followPath(const Road* , Vector*);
    inline virtual Vector getPosition() const override { return m_Position; }
    inline virtual Vector getVelocity() const override { return m_Velocity; }
    inline virtual Vector getAcceleration() const override { return m_Acceleration; }
    inline State getState() const { return m_State; }
    void setState(State state, bool value);
    double getMaxSpeed() const;
    inline double getMaxPossibleSpeed() const { return m_MaxSpeed; }
    bool view(const Car &car, double startAngle, double endAngle, double dist) const;
    bool view(const TrafficLight &light, double startAngle, double endAngle, double dist) const;
    inline virtual Vector getForceAccumulator() const override { return m_ForceAccumulator; }
    // inline void setVel(const Vector& vel) {velocity = vel;}
    // inline void setMaxSpeed(const double spe) { maxSpeed = spe; }
private:
    inline virtual void clearAccumulator() override { m_ForceAccumulator *= 0; };
    virtual float getMass() const override { return 0; }
    virtual float getInverseMass() const override { return 0;}
    virtual bool hasFiniteMass() const override { return 0;}
    virtual void setDamping(float damping) override { }
    virtual float getDamping() const override { return 0;}

private:
    double m_MaxSpeed;
    State m_State;
};

inline constexpr Car::State operator&(Car::State __a, Car::State __b)
{ return Car::State(static_cast<int>(__a) & static_cast<int>(__b)); }
inline constexpr Car::State operator|(Car::State __a, Car::State __b)
{ return Car::State(static_cast<int>(__a) | static_cast<int>(__b)); }
inline constexpr Car::State operator^(Car::State __a, Car::State __b)
{ return Car::State(static_cast<int>(__a) ^ static_cast<int>(__b)); }
inline constexpr Car::State operator~(Car::State __a)
{ return Car::State(~static_cast<int>(__a)); }
inline const Car::State& operator|=(Car::State& __a, Car::State __b)
{ return __a = __a | __b; }
inline const Car::State& operator&=(Car::State& __a, Car::State __b)
{ return __a = __a & __b; }
inline const Car::State& operator^=(Car::State& __a, Car::State __b)
{ return __a = __a ^ __b; }

struct CarInformation
{
    Car car;
    SteerForceGenerator steerForceGenerator;
    BrakeForceGenerator brakeForceGenerator;
    unsigned int roadID;
};

class CarRegistry
{
public:
    CarRegistry()  : m_Cars() {}
    ~CarRegistry() {}

    void addCar(const Car &car, const unsigned int start_roadID);
    void update(const RoadRegistry &roads, const std::vector<const TrafficLight*>& lights, float time);
    std::vector<Car> getCars();
private:
    void interectLights(std::list<CarInformation>::iterator& it, const std::vector<const TrafficLight*> &lights);
    void yieldInterect(std::list<CarInformation>::iterator& it, const RoadRegistry &roads);
    void turn(std::list<CarInformation>::iterator& it, const RoadRegistry &roads);
    void interectFollow(std::list<CarInformation>::iterator& it, const RoadRegistry &roads);
    void applySteerForce(Car &car, SteerForceGenerator& steerForceGenerator, const Road* road);
    void applyBrakeForce(Car &car, BrakeForceGenerator& brakeForceGenerator);
private:
    std::list<CarInformation> m_Cars;
};

class CarGenerator
{
public:
    CarGenerator();
    CarGenerator(const Vector &pos, const int rate = 1000);
    ~CarGenerator() {}
    inline void setPosition(const Vector &pos) { m_Position = pos; }
    inline const Vector& getPosition() const { return m_Position; }
    inline int getRate() const { return m_Rate; }
    inline void setRate(int rate) { this->m_Rate = rate; }
    inline void setStartRoadID(const unsigned int ID) { m_StartRoadID = ID; }
    inline unsigned int getStartRoadId() { return m_StartRoadID; }
  
    void update(CarRegistry &cars); //change to array of roads, roads connections
   // void avoidColision(); //change name
private:
    Vector m_Position;
    int m_Rate;
    unsigned int m_StartRoadID;
    std::chrono::time_point<std::chrono::steady_clock> time;
};

#endif