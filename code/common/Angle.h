#ifndef ANGLE_H
#define ANGLE_H

const double PI = 3.1415926535897932385;
const double TWO_PI = 2.0 * PI;

class Angle {
public:
    Angle(double rad = 0);
    static Angle from_degree(double deg);
    static Angle from_tan(double tangent);
    static double rad_normalize(double rad);
    
    double rad() const;
    double deg() const;

    Angle operator+(const Angle &other) const;
    Angle operator-(const Angle &other) const;
    Angle& operator+=(const Angle &other);
    Angle& operator-=(const Angle &other);

    bool is_between(double min_rad, double max_rad) const;

private:
    double rad_;  // Internal storage in radians
};

#endif
