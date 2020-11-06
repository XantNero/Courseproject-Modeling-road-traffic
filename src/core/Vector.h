#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector
{
private:
    double x;
    double y;
public:
    Vector(double x = .0, double y = .0);
    ~Vector();
    Vector(const Vector&);
    Vector& operator=(const Vector&);
    Vector& operator+=(const Vector&);
    Vector& operator+=(const double);
    Vector operator+(const Vector&);
    friend Vector operator+(const double, const Vector&);
    Vector operator+(const double);
    Vector& operator-=(const Vector&);
    Vector& operator-=(const double);
    Vector operator-(const Vector&);
    Vector operator-(const double);
    Vector& operator/=(const double);
    Vector& operator/(const double);
    Vector& operator*=(const double);
    Vector& operator*(const double);
    friend Vector operator*(const double, const Vector&);
    friend double operator*(const Vector&, const Vector&);
    friend bool operator==(const Vector&, const Vector&);

    friend double scalarDotProduct(const Vector&, const Vector&);

    double getMagnitude() const;
    void normalize();
    void setMagnitude(double magnitude);
    void limitMagnitude(double limit);
    double heading2D() const;
    void rotate(double angle);
    double getX() const;
    double getY() const;
    void setX(double);
    void setY(double);
    double distance(const Vector &);
    double getAngle(const Vector &);
};


#endif