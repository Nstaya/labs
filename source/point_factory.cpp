#include "point_factory.hpp"
#include <iostream>

std::unique_ptr<Point> PointFactory::create(double x, double y) {
    return std::make_unique<Point>(x, y);
}

std::unique_ptr<Point> PointFactory::create_from_input() {
    double x, y;
    std::cin >> x >> y;
    return create(x, y);
}
