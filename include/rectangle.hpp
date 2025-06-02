#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"
#include <memory>

class Rectangle : public Shape {
public:
    Rectangle(const std::string& name, double x1, double y1, double x2, double y2);
    double perimeter() const override;
    std::string parameters() const override;
    std::string type() const override;
    void validate() const override;

private:
    double leftTopX, leftTopY, rightBottomX, rightBottomY;
};

#endif // RECTANGLE_H
