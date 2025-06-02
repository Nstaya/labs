#ifndef POLYGON_H
#define POLYGON_H

#include "shape.hpp"
#include <vector>

class Polygon : public Shape {
public:
    Polygon(const std::string& name, const std::vector<double>& coords);
    double perimeter() const override;
    std::string parameters() const override;
    std::string type() const override;
    void validate() const override;

private:
    std::vector<double> vertices;
    bool isConvex() const;
};

#endif // POLYGON_H
