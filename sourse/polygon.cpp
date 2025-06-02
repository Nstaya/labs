#include "polygon.hpp"
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <iostream>

Polygon::Polygon(const std::string &name, const std::vector<double>& coords) :
    Shape(name),
    vertices(coords) {
    validate();
}

void Polygon::validate() const {
    if (vertices.size() < 6 || vertices.size() % 2 != 0) {
        throw std::invalid_argument("Многоугольник должен иметь как минимум 3 вершины");
    }

    if (!isConvex()) {
        throw std::invalid_argument("Многоугольник не является выпуклым");
    }
}

double Polygon::perimeter() const {
    double p = 0.0;
    size_t n = vertices.size() / 2;

    for (size_t i = 0; i < n; ++i) {
        double x1 = vertices[2*i];
        double y1 = vertices[2*i + 1];
        double x2 = vertices[2*((i+1)%n)];
        double y2 = vertices[2*((i+1)%n) + 1];
        p += sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    return p;
}

std::string Polygon::parameters() const {
    std::ostringstream oss;
    oss << "Многоугольник '" << name << "': Вершины ";
    for (size_t i = 0; i < vertices.size(); i += 2) {
        oss << "(" << vertices[i] << ", " << vertices[i+1] << ")";
        if (i < vertices.size() - 2) oss << ", ";
    }
    return oss.str();
}

std::string Polygon::type() const {
    return "Многоугольник";
}

bool Polygon::isConvex() const {
    size_t n = vertices.size() / 2;
    if (n < 3) return false;

    int sign = 0;
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        size_t k = (i + 2) % n;

        double x1 = vertices[2*i], y1 = vertices[2*i + 1];
        double x2 = vertices[2*j], y2 = vertices[2*j + 1];
        double x3 = vertices[2*k], y3 = vertices[2*k + 1];

        double cross = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);

        if (cross != 0) {
            if (sign == 0) {
                sign = cross > 0 ? 1 : -1;
            } else if (sign * cross < 0) {
                return false;
            }
        }
    }
    return true;
}
