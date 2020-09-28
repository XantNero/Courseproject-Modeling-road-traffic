#include "Vector.h"
#include <cmath>

inline Vector::Vector(double x /*= .0*/, double y /*= .0*/)
: x(x), y(y), limit(0) { }

inline Vector::~Vector() { }

inline Vector::Vector(const Vector &obj)
{
    x = obj.getX();
    y = obj.getY();
    limit = obj.limit;
}

Vector& Vector::operator=(const Vector &v)
{
    if (this == &v)
        return *this;
    setX(v.getX());
    setY(v.getY());
    limit = v.limit;
    return *this;
}

Vector& Vector::operator+=(const Vector& v)
{
    setX(getX() + v.getX());
    setY(getY() + v.getY());
    checkLimit();
    return *this;
}

Vector& Vector::operator+=(const double value)
{
    setX(getX() + value);
    setY(getY() + value);
    checkLimit();
    return *this;
}

Vector& Vector::operator+(const Vector& v)
{
    setX(getX() + v.getX());
    setY(getY() + v.getY());
    checkLimit();
    return *this;
}

inline Vector operator+(const double value, const Vector& right)
{
    return Vector(value + right.getX(), value + right.getY());
}

Vector& Vector::operator+(const double value)
{
    setX(getX() + value);
    setY(getY() + value);
    checkLimit();
    return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
    setX(getX() - v.getX());
    setY(getY() - v.getY());
    checkLimit();
    return *this;
}

Vector& Vector::operator-=(const double value)
{
    setX(getX() - value);
    setY(getY() - value);
    checkLimit();
    return *this;
}


Vector& Vector::operator-(const Vector& v) 
{
    setX(getX() - v.getX());
    setY(getY() - v.getY());
    checkLimit();
    return *this;
}


Vector& Vector::operator-(const double value)
{
    setX(getX() - value);
    setY(getY() - value);
    checkLimit();
    return *this;
}

Vector& Vector::operator/(const double value)
{
    setX(getX() / value);
    setY(getY() / value);
    checkLimit();
    return *this;
}

Vector& Vector::operator/=(const double value)
{
    setX(getX() / value);
    setY(getY() / value);
    checkLimit();
    return *this;
}

Vector& Vector::operator*=(const double value)
{
    setX(getX() * value);
    setY(getY() * value);
    checkLimit();
    return *this;
}

Vector& Vector::operator*(const double value)
{
    setX(getX() * value);
    setY(getY() * value);
    checkLimit();
    return *this;
}

inline Vector operator*(const double value, const Vector &right)
{
    return Vector(value * right.getX(), value * right.getY());
}

inline double operator*(const Vector& left, const Vector &right)
{
    return left.getX() * right.getX() + left.getY() * right.getY();
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

inline void Vector::checkLimit()
{
    if (getLimit() != 0 && getMagnitude() > getLimit())
        setMagnitude(getLimit());
}

inline double Vector::getLimit() const
{
    return limit;
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
    checkLimit();
}

inline void Vector::setY(double value)
{
    y = value;
    checkLimit();
}

void Vector::rotate(double) { }