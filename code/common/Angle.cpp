#include "Angle.h"

// rad_normalize radians to [0, 2π)
double Angle::rad_normalize(double rad) {
    while (rad >= TWO_PI) rad -= TWO_PI;
    while (rad < 0.0) rad += TWO_PI;
    return rad;
}

// Constructor with radians
Angle::Angle(double rad) : rad_(rad_normalize(rad)) {}

// Construct from degrees
Angle Angle::from_degree(double deg) {
    return Angle(deg * PI / 180.0);
}

// Construct from tangent
Angle Angle::from_tan(double tangent) {
    return Angle(atan(tangent));
}

// Get value in radians
double Angle::rad() const {
    return rad_;
}

// Get value in degrees
double Angle::deg() const {
    return rad_ * 180.0 / PI;
}

Angle Angle::operator+(const Angle &other) const {
    return Angle(rad_ + other.rad_);
}

Angle Angle::operator-(const Angle &other) const {
    return Angle(rad_ - other.rad_);
}

Angle& Angle::operator+=(const Angle &other) {
    rad_ = rad_normalize(rad_ + other.rad_);
    return *this;
}

Angle& Angle::operator-=(const Angle &other) {
    rad_ = rad_normalize(rad_ - other.rad_);
    return *this;
}

// Check if within [min_rad, max_rad], considering wraparound
bool Angle::is_between(double min_rad, double max_rad) const {
    double r = rad_;
    if (min_rad < max_rad)
        return (r >= min_rad && r <= max_rad);
    else
        return (r >= min_rad || r <= max_rad);
}
