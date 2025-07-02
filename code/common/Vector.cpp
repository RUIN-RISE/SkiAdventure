#include <Vector.h>
#include <cmath>

Vector::Vector(double x = 0, double y = 0) : x(x), y(y) {}

Vector Vector::operator+(const Vector& other) const {
    return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(double scalar) const {
    return Vector(x * scalar, y * scalar);
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