#include "storage.hpp"
#include <numeric>
#include <stdexcept>
#include <algorithm>

void ShapeStorage::addShape(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}

void ShapeStorage::removeShape(size_t index) {
    if (index >= shapes_.size())
        throw std::out_of_range("Invalid index");
    shapes_.erase(shapes_.begin() + index);
}

void ShapeStorage::removeIf(std::function<bool(const Shape&)> predicate) {
    shapes_.erase(
        std::remove_if(shapes_.begin(), shapes_.end(),
                       [&predicate](const std::unique_ptr<Shape>& shape) {
                           return predicate(*shape);
                       }),
        shapes_.end()
        );
}

void ShapeStorage::sortByPerimeter() {
    std::sort(shapes_.begin(), shapes_.end(),
              [](const std::unique_ptr<Shape>& a, const std::unique_ptr<Shape>& b) {
                  return a->perimeter() < b->perimeter();
              });
}

const std::vector<std::unique_ptr<Shape>>& ShapeStorage::getShapes() const {
    return shapes_;
}

double ShapeStorage::getTotalPerimeter() const {
    return std::accumulate(shapes_.begin(), shapes_.end(), 0.0,
                           [](double sum, const std::unique_ptr<Shape>& shape) {
                               return sum + shape->perimeter();
                           });
}

size_t ShapeStorage::count() const {
    return shapes_.size();
}
