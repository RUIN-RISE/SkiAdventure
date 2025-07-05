#ifndef CURVE_H
#define CURVE_H
#include<vector>
#include "Vector.h"
#include "Angle.h"

class Curve {
public:
    Curve(std::vector<Vector> deltas);

    void build_points(std::vector<Vector> deltas);

    double evaluate(double x) const;

    double derivative(double x) const;

    Angle angle(double x) const;

    Vector tangent(double x) const;

private:
    // points: [O-delta[n-1], O, O+delta[0], O+delta[0]+delta[1], ..., O+sum(deltas), O+sum(deltas)+delta[0]]
    std::vector<Vector> points;
    std::vector<double> slopes;
    double period_x, period_y;
};

#endif
