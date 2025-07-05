#ifndef __CURVE_H__
#define __CURVE_H__

#include "Angle.h"
#include "Vector.h"

// y = (-x + 100sin(x/100)) *7/12
class Curve {
public:
    Curve() = default;

    double evaluate(double x) const;

    double derivative(double x) const;

    Angle angle(double x) const;

    Vector tangent(double x) const;

    // <y(x), y'(x)>
    std::pair<double, double> evaluateAndDerivative(double x) const;
};

#endif