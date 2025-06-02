#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

#include "shape.hpp"
#include <memory>
#include <map>
#include <functional>
#include <vector>
#include <string>

class ShapeFactory {
public:
    using CreateFunction = std::function<std::unique_ptr<Shape>(const std::string&, const std::vector<double>&)>;

    static ShapeFactory& instance()  {
        static ShapeFactory factory;
        factory.registerDefaults();
        return factory;
    }

    void registerShape(const std::string& type, CreateFunction creator);
    std::unique_ptr<Shape> create(const std::string& type, const std::string& name, const std::vector<double>& params);
    std::vector<std::string> availableShapes() const;

private:
    std::map<std::string, CreateFunction> creators_;
    ShapeFactory() = default;
    void registerDefaults();
};

#endif // SHAPE_FACTORY_H
