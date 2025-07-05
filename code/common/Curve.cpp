#include "Curve.h"

//(-x + 100sin(x/100)) *7/12

const int w = 100 ;
const double k = 7.0/12;

// y(x)
double Curve::evaluate(double x) const {
    return (-x + w*std::sin(x/w)) * k;
}

// y'(x)
double Curve::derivative(double x) const {
    return (-1 + std::cos(x/w)) * k;
}

// Angle of the curve at x
Angle Curve::angle(double x) const {
    return Angle::from_tan(derivative(x));
}

// Vector tangent at x
Vector Curve::tangent(double x) const {
    Vector res = Vector(1, derivative(x));
    res.normalize();
    return res;
}

std::pair<double, double> Curve::evaluateAndDerivative(double x) const {
    return {evaluate(x), derivative(x)};
}
