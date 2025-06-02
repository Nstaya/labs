#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"
#include "point.hpp"
#include <memory>


class Circle : public Shape {
public:
    Circle(const std::string& n, const Point &center, double radius);
    double perimeter() const override;
    std::string parameters() const override;
    std::string type() const override;
    void validate() const override;

private:
    Point center_;
    double radius_;
};

#endif // CIRCLE_H
