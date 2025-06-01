#include "circle.hpp"
#include <cmath>
#include <sstream>

Circle::Circle(const std::string &name, const Point &center, double radius) :
    Shape(name),
    center_(center), radius_(radius) {
    validate();
}

void Circle::validate() const {
    if (radius_ <= 0)
        throw std::invalid_argument("\nРадиус должен быть положительным");
}

double Circle::perimeter() const {
    return 2 * M_PI * radius_;
}

std::string Circle::parameters() const {
    std::ostringstream oss;
    oss << "Круг '" << name << "': Центр ("<< center_.to_string() << "), Радиус " << radius_;
    return oss.str();
}

std::string Circle::type() const {
    return "Круг";
}
