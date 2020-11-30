#ifndef _CAR_H_
#define _CAR_H_
#include <list>
#include <chrono>

#include "Vector.h"
#include "Road.h"
#include "Particle.h"
#include "ForceGenerator.h"


// class Car
// {
// public:
//     enum State{
//             LIVE,
//             TURN,
//             DEAD
//     };
// public:
//     Car(Vector loc);
//     ~Car();
//     Car(const Car& );
//     void applyForce(Vector &force);
//     void move(float time);
//     void seek(Vector &target);
//     void followPath(const Road &);
//     Vector getPos() const;
//     Vector getVel() const;
//     State getState() const;
//     void setState(State state);
//     double getMaxSpeed() const;
//     bool view(const Car &car) const;
// private:
//     Vector getNormalPoint(Vector&, Vector&, Vector&);
// private:
//     Vector* location;
//     Vector* velocity;
//     Vector* acceleration;
//     double maxSpeed;
//     State state;
// };
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
    Car(const float x, const float y);
    ~Car();
    Car(const Car& );
    inline virtual void applyForce(const Vector &force) override { forceAccumulator += force; }
    virtual void move(float time) override;
    bool followPath(const Road* , Vector*);
    inline virtual Vector getPosition() const override { return position; }
    inline virtual Vector getVelocity() const override { return velocity; }
    inline virtual Vector getAcceleration() const override { return acceleration; }
    inline State getState() const { return state; }
    void setState(State state, bool value);
    double getMaxSpeed() const;
    bool view(const Car &car, double angle, double dist) const;
    inline virtual Vector getForceAccumulator() const override { return forceAccumulator; }
    // inline void setVel(const Vector& vel) {velocity = vel;}
    // inline void setMaxSpeed(const double spe) { maxSpeed = spe; }
    inline virtual void clearAccumulator() override { forceAccumulator *= 0; };
    virtual float getMass() const override { return 0; }
    virtual float getInverseMass() const override { return 0;}
    virtual bool hasFiniteMass() const override { return 0;}
    virtual void setDamping(float damping) override { }
    virtual float getDamping() const override { return 0;}
private:
    Vector getNormalPoint(Vector&, Vector&, Vector&);
   
private:
    double maxSpeed;
    State state;
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
    CarRegistry();
    ~CarRegistry();

    void addCar(const Car &car, const unsigned int start_roadID);
    void update(const RoadRegistry &roads, float time);
    std::vector<Car> getCars();
private:
    void applySteerForce(Car &car, SteerForceGenerator& steerForceGenerator, const Road* road);
    void applyBrakeForce(Car &car, BrakeForceGenerator& brakeForceGenerator);
private:
    std::list<CarInformation> cars;
};

class CarGenerator
{
public:
    CarGenerator();
    CarGenerator(const Vector &pos, const int rate = 200);
    inline void setPosition(const Vector &pos) { position = pos; }
    inline const Vector& getPosition() const { return position; }
    inline int getRate() const { return rate; }
    inline void setRate(int rate) { this->rate = rate; }
    inline void setStartRoadID(const unsigned int ID) { m_StartRoadID = ID; }
    inline unsigned int getStartRoadId() { return m_StartRoadID; }
    ~CarGenerator();
    void update(CarRegistry &cars); //change to array of roads, roads connections
   // void avoidColision(); //change name
private:
    Vector position;
    int rate;
    unsigned int m_StartRoadID;
    std::chrono::time_point<std::chrono::steady_clock> time;
};

#endif