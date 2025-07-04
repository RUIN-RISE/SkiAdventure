#include "Curve.h"

//(-x + 100sin(x/100)) *7/12

const int w = 100 ;
const double k = 7.0/12;

double Curve::evaluate(double x) const {
    return (-x + w*std::sin(x/w)) * k;
}

double Curve::derivative(double x) const {
    return (-1 + std::cos(x/w)) * k;
}

std::pair<double, double> Curve::evaluateAndDerivative(double x) const {
    return {evaluate(x), derivative(x)};
}
