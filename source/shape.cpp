#include "shape.hpp"

Shape::Shape(const std::string& name) : name(name) {}

std::string Shape::get_name() const {
    return name;
}
