#include "../pch.h"

#include "Vector.h"

inline Vector::Vector(double x /*= .0*/, double y /*= .0*/)
: x(x), y(y){ }

inline Vector::~Vector() { }

Vector::Vector(const Vector &obj)
{
    x = obj.getX();
    y = obj.getY();
}

Vector& Vector::operator=(const Vector &v)
{
    if (this == &v)
        return *this;
    setX(v.getX());
    setY(v.getY());
    return *this;
}

Vector& Vector::operator+=(const Vector& v)
{
    setX(getX() + v.getX());
    setY(getY() + v.getY());
    return *this;
}

Vector& Vector::operator+=(const double value)
{
    setX(getX() + value);
    setY(getY() + value);
    return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
    setX(getX() - v.getX());
    setY(getY() - v.getY());
    return *this;
}

Vector& Vector::operator-=(const double value)
{
    setX(getX() - value);
    setY(getY() - value);
    return *this;
}

Vector& Vector::operator/(const double value)
{
    if (value == 0.0) // TODO:make exception
        return *this;
    setX(getX() / value);
    setY(getY() / value);
    return *this;
}

Vector& Vector::operator/=(const double value)
{
    if (value == 0.0)
        return *this;
    setX(getX() / value);
    setY(getY() / value);
    return *this;
}

Vector& Vector::operator*=(const double value)
{
    setX(getX() * value);
    setY(getY() * value);
    return *this;
}

Vector& Vector::operator*(const double value)
{
    setX(getX() * value);
    setY(getY() * value);
    return *this;
}

void Vector::rotate(double angle)
{
    double magnitude = getMagnitude();
    double start_angle = heading2D();
    setX(cos(angle + start_angle));
    setY(sin(angle + start_angle));
    (*this) *= magnitude;
}

double Vector::distance(const Vector& point) 
{
    Vector temp(point.getX() - getX(), point.getY() - getY());
    return temp.getMagnitude();
}

void Vector::limitMagnitude(double limit)
{
    if (getMagnitude() > limit)
        setMagnitude(limit);
}

double Vector::getAngle(const Vector& v)
{   
    double m = getMagnitude();
    double mv = v.getMagnitude();
    double angle;
    if (mv == 0 || m == 0)
        angle = 0.0f;
    else    
         angle = (*this) * v /(mv * m);
    if (angle > 1.0f)
        angle = 1.0f;
    if (angle < -1.0f)
        angle ==-1.0f;
    return acos(angle);
}