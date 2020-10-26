#include "Vector.h"
#include <cmath>

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

Vector Vector::operator+(const Vector& v)
{
    Vector res(getX() + v.getX(), getY() + v.getY());
    return res;
}

inline Vector operator+(const double value, const Vector& right)
{
    return Vector(value + right.getX(), value + right.getY());
}

Vector Vector::operator+(const double value)
{
    Vector res(getX() + value, getY() + value);
    return res;
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


Vector Vector::operator-(const Vector& v) 
{
    Vector res(getX() - v.getX(), getY() - v.getY());
    return res;
}


Vector Vector::operator-(const double value)
{
    Vector res(getX() - value, getY() - value);
    return res;
}

Vector& Vector::operator/(const double value)
{
    if (value == 0.0) // make exception
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

Vector operator*(const double value, const Vector &right)
{
    return Vector(value * right.getX(), value * right.getY());
}

double operator*(const Vector &left, const Vector &right)
{
    return left.getX() * right.getX() + left.getY() * right.getY();
}

bool operator==(const Vector& left, const Vector& right)
{
    return (left.getX() == right.getX() && left.getY() == right.getY());
}

inline double Vector::getMagnitude() const
{
    return sqrt(getX() * getX() + getY() * getY());
}

inline void Vector::normalize()
{
    (*this) /= getMagnitude();
}

inline void Vector::setMagnitude(double magnitude)
{
    normalize();
    (*this) *= magnitude; 
}

inline double Vector::heading2D() const
{
    return atan2(getY(), getX());
}

inline double Vector::getX() const
{
    return x;
}

inline double Vector::getY() const
{
    return y;
}

inline void Vector::setX(double value)
{
    x = value;
}

inline void Vector::setY(double value)
{
    y = value;
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
    return acos((*this) * v /( getMagnitude() * v.getMagnitude()));
}