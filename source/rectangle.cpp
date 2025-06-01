#include "rectangle.hpp"
#include <stdexcept>
#include <sstream>
#include <algorithm>

Rectangle::Rectangle(const std::string& name, double x1, double y1, double x2, double y2) :
    Shape(name),
    leftTopX(std::min(x1, x2)),
    leftTopY(std::max(y1, y2)),
    rightBottomX(std::max(x1, x2)),
    rightBottomY(std::min(y1, y2)) {
    validate();
}

void Rectangle::validate() const {
    if (leftTopX == rightBottomX || leftTopY == rightBottomY) {
        throw std::invalid_argument("Прямоугольник не может быть вырожденным");
    }
}

double Rectangle::perimeter() const {
    double width = rightBottomX - leftTopX;
    double height = leftTopY - rightBottomY;
    return 2 * (width + height);
}

std::string Rectangle::parameters() const {
    std::ostringstream oss;
    oss << "Прямоугольник '" << name << "': Левый верхний (" << leftTopX << ", " << leftTopY
        << "), Правый нижний (" << rightBottomX << ", " << rightBottomY << ")";
    return oss.str();
}

std::string Rectangle::type() const {
    return "Прямоугольник";
}
