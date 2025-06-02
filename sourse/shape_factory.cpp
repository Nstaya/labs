#include "shape_factory.hpp"
#include "shapes.hpp"
#include "point_factory.hpp"
#include <stdexcept>

void ShapeFactory::registerShape(const std::string& type, CreateFunction creator) {
    creators_[type] = creator;
}

std::unique_ptr<Shape> ShapeFactory::create(const std::string& type, const std::string& name, const std::vector<double>& params) {
    auto it = creators_.find(type);
    if (it == creators_.end()) {
        throw std::runtime_error("Неизвестный тип: " + type);
    }
    return it->second(name, params);
}

std::vector<std::string> ShapeFactory::availableShapes() const {
    std::vector<std::string> result;
    for (const auto& pair : creators_) {
        result.push_back(pair.first);
    }
    return result;
}

void ShapeFactory::registerDefaults() {
    if(creators_.empty()) {
        registerShape("circle", [](const std::string& name, const std::vector<double>& params) {
            if (params.size() != 3)
                throw std::invalid_argument("Для круга нужно 3 параметра (x, y, радиус)");
            auto center = PointFactory::create(params[0], params[1]);
            return std::make_unique<Circle>(name, *center, params[2]);
        });

        registerShape("rectangle", [](const std::string& name, const std::vector<double>& params) {
            if (params.size() != 4)
                throw std::invalid_argument("Для прямоугольника нужно 4 параметра (x1, y1, x2, y2)");
            return std::make_unique<Rectangle>(name, params[0], params[1], params[2], params[3]);
        });

        registerShape("triangle", [](const std::string& name, const std::vector<double>& params) {
            if (params.size() != 6)
                throw std::invalid_argument("Для треугольника нужно 6 параметров (x1, y1, x2, y2, x3, y3)");
            return std::make_unique<Triangle>(name, params[0], params[1], params[2], params[3], params[4], params[5]);
        });

        registerShape("polygon", [](const std::string& name, const std::vector<double>& params) {
            if (params.size() < 6 || params.size() % 2 != 0)
                throw std::invalid_argument("Для выпуклого многоугольника нужно минимум 6 координат (3 вершины)");
            return std::make_unique<Polygon>(name, params);
        });
    }
}
