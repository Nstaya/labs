#include "triangle.hpp"
#include <stdexcept>
#include <sstream>
#include <cmath>

Triangle::Triangle(const std::string& name, double x1, double y1, double x2, double y2, double x3, double y3) :
    Shape(name),
    x{x1, x2, x3},
    y{y1, y2, y3} {
    validate();
}

void Triangle::validate() const {
    if ((x[1] - x[0]) * (y[2] - y[1]) == (x[2] - x[0]) * (y[1] - y[0])) {
        throw std::invalid_argument("Точки треугольника лежат на одной прямой");
    }
}

double Triangle::perimeter() const {
    double a = sqrt(pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2));
    double b = sqrt(pow(x[2] - x[1], 2) + pow(y[2] - y[1], 2));
    double c = sqrt(pow(x[0] - x[2], 2) + pow(y[0] - y[2], 2));
    return a + b + c;
}

std::string Triangle::parameters() const {
    std::ostringstream oss;
    oss << "Треугольник '" << name << "': Вершины (" << x[0] << ", " << y[0] << "), ("
        << x[1] << ", " << y[1] << "), (" << x[2] << ", " << y[2] << ")";
    return oss.str();
}

std::string Triangle::type() const {
    return "Треугольник";
}
