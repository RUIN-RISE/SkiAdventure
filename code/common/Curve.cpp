#include "Curve.h"
#include <cmath>

double Curve::evaluate(double x) const {
    return -x + std::sin(x);
}

double Curve::derivative(double x) const {
    return -1 + std::cos(x);
}

std::pair<double, double> Curve::evaluateAndDerivative(double x) const {
    return {evaluate(x), derivative(x)};
}