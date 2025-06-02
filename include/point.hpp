#ifndef POINT_H
#define POINT_H

#include <string>

class Point {
public:
    Point(double x, double y);
    double x() const;
    double y() const;
    std::string to_string() const;
    void input();
private:
    double x_, y_;
};

#endif // POINT_H
