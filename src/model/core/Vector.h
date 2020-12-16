#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <cmath>
class Vector
{
private:
    double x;
    double y;
public:
    Vector(double x = .0, double y = .0) : x(x), y(y){ }
    ~Vector() {} 
    Vector(const Vector&);
    Vector& operator=(const Vector&);
    Vector& operator+=(const Vector&);
    Vector& operator+=(const double);
    inline Vector operator+(const Vector& v) { return Vector(getX() + v.getX(), getY() + v.getY()); }
    inline friend Vector operator+(const double value, const Vector& right)
      { return Vector(value + right.getX(), value + right.getY()); }
    inline Vector operator+(const double value) { return Vector(getX() + value, getY() + value); }
    Vector& operator-=(const Vector&);
    Vector& operator-=(const double);
    inline Vector operator-(const Vector& v) { return Vector(getX() - v.getX(), getY() - v.getY()); }
    inline Vector operator-(const double value) { return Vector(getX() - value, getY() - value); }
    Vector& operator/=(const double);
    Vector& operator/(const double);
    Vector& operator*=(const double);
    Vector& operator*(const double);
    inline friend Vector operator*(const double value, const Vector& right)
        { return Vector(value * right.getX(), value * right.getY()); }
    inline friend double operator*(const Vector& left, const Vector& right)
        { return left.getX() * right.getX() + left.getY() * right.getY(); }
    inline friend double scalarDotProduct(const Vector& left, const Vector& right)
        { return left.getX() * right.getY() - left.getY() * right.getX(); }
    inline friend bool operator==(const Vector& left, const Vector& right)
        { return (left.getX() == right.getX() && left.getY() == right.getY()); }

    inline double getMagnitude() const { double s = getSquareMagnitude(); if (s < 0) s = 0; return sqrt(s); }
    inline double getSquareMagnitude() const { return getX() * getX() + getY() * getY(); }
    inline void normalize() { (*this) /= getMagnitude(); }
    inline void setMagnitude(double magnitude)
        { normalize(); (*this) *= magnitude; }
    void limitMagnitude(double limit);
    inline double heading2D() const { return atan2(getY(), getX()); }
    void rotate(double angle);
    inline double getX() const { return x; }
    inline double getY() const { return y; }
    inline void setX(double value) { x = value; }
    inline void setY(double value) { y = value; }
    double distance(const Vector &);
    double getAngle(const Vector &);
    friend Vector getNormalPoint(Vector& point, Vector& a, Vector& b);
};


#endif