#ifndef __VECTOR_H__
#define __VECTOR_H__

class Angle;

class Vector {
public:
    double x, y;

    Vector(double x = 0, double y = 0);

    Vector(const Vector &other);

    Vector operator+(const Vector& other) const;

    const Vector & operator+=(const Vector& other);

    Vector operator-(const Vector& other) const;

    const Vector & operator-=(const Vector& other);

    //scalar multiplication
    Vector operator*(double scalar) const;

    const Vector & operator*=(double scalar);

    Vector operator/(double scalar) const;

    const Vector & operator/=(double scalar);

    //inner product
    double operator*(const Vector& other) const;

    //outer product
    double operator^(const Vector& other) const;

    double length() const;

    //make length 1
    void normalize();

    Angle angle() const;

    Vector orthogonal() const;
};

#endif