#ifndef SHAPE_H
#define SHAPE_H

#include "point.hpp"
#include <string>
#include <memory>

class Shape {
public:
    explicit Shape(const std::string& name) : name(name) {}
    virtual ~Shape() = default;
    virtual double perimeter() const = 0;
    virtual std::string parameters() const = 0;
    virtual std::string type() const = 0;

    std::string name;
};

#endif // SHAPE_H
