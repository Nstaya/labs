#ifndef STORAGE_H
#define STORAGE_H

#include "shape.hpp"
#include <vector>
#include <memory>
#include <functional>


class ShapeStorage {
public:
    void addShape(std::unique_ptr<Shape> shape);
    void removeShape(size_t index);
    void removeIf(std::function<bool(const Shape&)> predicate);
    void sortByPerimeter();

    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
    double getTotalPerimeter() const;
    size_t count() const;

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};

#endif // STORAGE_H
