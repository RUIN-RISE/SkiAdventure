#include "Vector.h"
#include "Angle.h"
#include<cmath>
Vector::Vector(double x, double y) : x(x), y(y) {}

Vector::Vector(const Vector &other) : x(other.x), y(other.y) {}

Vector Vector::operator+(const Vector& other) const {
    return Vector(x + other.x, y + other.y);
}

const Vector & Vector::operator+=(const Vector& other){
    x += other.x;
    y += other.y;
    return *this;
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(x - other.x, y - other.y);
}

const Vector & Vector::operator-=(const Vector& other){
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector Vector::operator*(double scalar) const {
    return Vector(x * scalar, y * scalar);
}

const Vector & Vector::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector Vector::operator/(double scalar) const {
    return Vector(x / scalar, y / scalar);
}

const Vector & Vector::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

double Vector::operator*(const Vector& other) const {
    return x * other.x + y * other.y;
}

double Vector::operator^(const Vector& other) const {
    return x * other.y - y * other.x;
}

double Vector::length() const {
    return std::sqrt(x * x + y * y);
}

void Vector::normalize() {
    double len = length();
    if (len > 0) {
        x /= len;
        y /= len;
    }
}

Angle Vector::angle() const {
    return Angle::from_tan(y / x);
}

// 90 degrees rotation
Vector Vector::orthogonal() const {
    return Vector(-y, x);
}

double dist(const Vector &a,const Vector &b){
	double ax = a.x,ay = a.y;
	double bx = b.x,by = b.y;
	return sqrt((ax-bx)*(ax-bx) + (ay-by)*(ay-by));
}
