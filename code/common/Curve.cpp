#include<cmath>
#include "Curve.h"
#include<vector>
#include<iostream>
using namespace std;
Curve::Curve(std::vector<Vector> deltas) {
    build_points(deltas);
}

void Curve::build_points(std::vector<Vector> deltas) {
    points.clear();
    points.push_back(Vector(0, 0) - deltas.back());
    points.push_back(Vector(0, 0));
    for (auto v : deltas)
        points.push_back(points.back() + v);
    points.push_back(points.back() + deltas[0]);

    period_x = points[points.size()-2].x - points[1].x;
    period_y = points[points.size()-2].y - points[1].y;

    slopes.resize(points.size());
    int n = points.size();
    for (int i = 1; i < n - 1; ++i) {
        double dx1 = points[i].x - points[i-1].x;
        double dy1 = points[i].y - points[i-1].y;
        double dx2 = points[i+1].x - points[i].x;
        double dy2 = points[i+1].y - points[i].y;
        slopes[i] = (dy1/dx1 + dy2/dx2) / 2;
    }
    slopes[0] = slopes[1];
    slopes[n-1] = slopes[n-2];
    cout<<"ok"<<endl;
}

// returns quotient and remainder of a/b where b>0, ensuring 0 <= remainder < b
std::pair<double,double> f_division(double a, double b){
    double q = floor(a / b);
    double r = a - q * b;
    return {q, r};
}

double Curve::evaluate(double x) const {
    auto tmp = f_division(x, period_x);
    double k = tmp.first;
    x = tmp.second;

    for (int i = 1; i + 1 < points.size(); ++i) {
        if (x >= points[i].x && x <= points[i+1].x) {
            double h = points[i+1].x - points[i].x;
            double t = (x - points[i].x) / h;
            double t2 = t * t, t3 = t2 * t;
            return (2*t3 - 3*t2 + 1) * points[i].y +
                   (t3 - 2*t2 + t) * h * slopes[i] +
                   (-2*t3 + 3*t2) * points[i+1].y +
                   (t3 - t2) * h * slopes[i+1] +
                   k * period_y;
        }
    }
    return 0.0;
}

double Curve::derivative(double x) const {
    x = f_division(x, period_x).second;

    for (int i = 1; i + 1 < points.size(); ++i) {
        if (x >= points[i].x && x <= points[i+1].x) {
            double h = points[i+1].x - points[i].x;
            double t = (x - points[i].x) / h;
            double t2 = t * t;
            return ((6*t2 - 6*t) * points[i].y +
                   (3*t2 - 4*t + 1) * h * slopes[i] +
                   (-6*t2 + 6*t) * points[i+1].y +
                   (3*t2 - 2*t) * h * slopes[i+1]) / h;
        }
    }
    return 0.0;
}

Angle Curve::angle(double x) const {
    return Angle::from_tan(derivative(x));
}

// Vector tangent at x
Vector Curve::tangent(double x) const {
    Vector res = Vector(1, derivative(x));
    res.normalize();
    return res;
}
