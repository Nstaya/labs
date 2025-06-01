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

private:
    Point center_;
    double radius_;
    void validate() const;
};

#endif // CIRCLE_H
