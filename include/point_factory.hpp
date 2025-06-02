#ifndef POINT_FACTORY_H
#define POINT_FACTORY_H

#include "point.hpp"
#include <memory>

class PointFactory {
public:
    static std::unique_ptr<Point> create(double x, double y);
    static std::unique_ptr<Point> create_from_input();
};

#endif // POINT_FACTORY_H
