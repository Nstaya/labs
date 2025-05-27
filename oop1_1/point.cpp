#include "point.h"
#include <iostream>
#include <sstream>

Point::Point(double x, double y) : x_(x), y_(y) {}

double Point::x() const { return x_; }
double Point::y() const { return y_; }

std::string Point::to_string() const {
    std::ostringstream oss;
    oss << "(" << x_ << ", " << y_ << ")";
    return oss.str();
}

void Point::input() {
    std::cin >> x_ >> y_;
}
