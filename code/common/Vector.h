class Vector {
public:
    double x, y;

    Vector(double, double);

    Vector operator+(const Vector& other) const;

    Vector operator-(const Vector& other) const;

    //scalar multiplication
    Vector operator*(double scalar) const;

    //inner product
    double operator*(const Vector& other) const;

    //outer product
    double operator^(const Vector& other) const;

    double length() const;

    //make length 1
    void normalize();
};