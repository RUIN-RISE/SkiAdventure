#ifndef __CURVE_H__
#define __CURVE_H__

// y = -x + sin(x)
class Curve {
public:
    Curve() = default;

    // y(x)
    double evaluate(double x) const;

    // y'(x)
    double derivative(double x) const;

    // <y(x), y'(x)>
    std::pair<double, double> evaluateAndDerivative(double x) const;
};

#endif