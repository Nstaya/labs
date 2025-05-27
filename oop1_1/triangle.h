#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include "point.h"
#include <array>
#include <memory>

class Triangle : public Shape {
public:
    Triangle(const std::string& n, double x1, double y1, double x2, double y2, double x3, double y3);
    double perimeter() const override;
    std::string parameters() const override;
    std::string type() const override;

private:
    std::array<double, 3> x;
    std::array<double, 3> y;
    void validate() const;
};

#endif // TRIANGLE_H
