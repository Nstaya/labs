#include "menu_commands.hpp"
#include "shape_factory.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <string>

MenuCommand::MenuCommand(const std::string &description) : description_(description) {}

const std::string MenuCommand::get_description() const {
    return this->description_;
}

AddShapeCommand::AddShapeCommand(const std::string& description):MenuCommand(description) {}

void AddShapeCommand::execute(ShapeStorage &storage) {
    std::cout << "Выберите тип фигуры: ";

    std::string input;
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cout << "Ошибка: введите число от 1 до 4" << std::endl;
        return;
    }
    try {
        int typeChoice = std::stoi(input);
        static const std::vector<std::string> shapeTypes = {
            "circle",
            "rectangle",
            "triangle",
            "polygon",
        };

        if ((typeChoice < 1) || (typeChoice > 4)) {
            std::cout << "Ошибка: введите число от 1 до 4" << std::endl;
            return;
        }

        const std::string& type = shapeTypes[typeChoice - 1];

        std::cout << "Введите название фигуры: ";
        std::string name;
        std::getline(std::cin, name);

        std::cout << "Введите параметры фигуры через пробел: ";
        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);

        std::vector<double> params;
        double param;
        while (iss >> param) {
            params.push_back(param);
        }

        try {
            auto shape = ShapeFactory::instance().create(type, name, params);
            storage.addShape(std::move(shape));
            std::cout << "Фигура успешно добавлена" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Ошибка при создании фигуры: " << e.what() << std::endl;
        }
    } catch (...) {
        std::cout << "Ошибка: введите число от 1 до 4" << std::endl;
    }
}

ShowShapesCommand::ShowShapesCommand(const std::string& description):MenuCommand(description) {}

void ShowShapesCommand::execute(ShapeStorage& storage) {
    const auto& shapes = storage.getShapes();
    if (shapes.empty()) {
        std::cout << "Коллекция фигур пуста" << std::endl;
        return;
    }

    std::cout << "Список фигур:" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << i+1 << ". " << shapes[i]->parameters() << std::endl;
    }
}

ShowPerimetersCommand::ShowPerimetersCommand(const std::string& description)
    : MenuCommand(description) {}

void ShowPerimetersCommand::execute(ShapeStorage& storage) {
    const auto& shapes = storage.getShapes();
    if (shapes.empty()) {
        std::cout << "Коллекция фигур пуста" << std::endl;
        return;
    }

    std::cout << "Периметры фигур:" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << i+1 << ". " << shapes[i]->type() << " '" << shapes[i]->get_name()
                  << "': " << shapes[i]->perimeter() << std::endl;
    }
}

ShowSumOfPerimetersCommand::ShowSumOfPerimetersCommand(const std::string& description)
    : MenuCommand(description) {}

void ShowSumOfPerimetersCommand::execute(ShapeStorage& storage) {
    std::cout << "Сумма периметров: " << storage.getTotalPerimeter() << std::endl;
}

SortShapesCommand::SortShapesCommand(const std::string& description)
    : MenuCommand(description) {}

void SortShapesCommand::execute(ShapeStorage& storage) {
    storage.sortByPerimeter();
    std::cout << "Фигуры отсортированы по периметру" << std::endl;
}

DeleteShapeByPositionCommand::DeleteShapeByPositionCommand(const std::string& description)
    : MenuCommand(description) {}

void DeleteShapeByPositionCommand::execute(ShapeStorage& storage) {
    if (storage.count() == 0) {
        std::cout << "Коллекция фигур пуста" << std::endl;
        return;
    }

    std::cout << "Введите номер фигуры (1-" << storage.count() << "): ";
    std::string input;
    std::getline(std::cin, input);

    try {
        size_t index = std::stoul(input);
        if (index < 1 || index > storage.count()) {
            std::cout << "Неверный номер" << std::endl;
            return;
        }
        storage.removeShape(index - 1);
        std::cout << "Фигура удалена" << std::endl;
    }
    catch (...) {
        std::cout << "Ошибка при удалении" << std::endl;
    }
}

DeleteShapesByPerimeterCommand::DeleteShapesByPerimeterCommand(const std::string& description)
    : MenuCommand(description) {}

void DeleteShapesByPerimeterCommand::execute(ShapeStorage& storage) {
    if (storage.count() == 0) {
        std::cout << "Коллекция фигур пуста" << std::endl;
        return;
    }

    std::cout << "Введите максимальный периметр: ";
    std::string input;
    std::getline(std::cin, input);

    try {
        double max_perimeter = std::stod(input);
        size_t before = storage.count();
        storage.removeIf([max_perimeter](const Shape& shape) {
            return shape.perimeter() > max_perimeter;
        });
        size_t removed = before - storage.count();
        std::cout << "Удалено фигур: " << removed << std::endl;
    }
    catch (...) {
        std::cout << "Ошибка при удалении" << std::endl;
    }
}

ExitCommand::ExitCommand(const std::string& description, bool& is_running)
    : MenuCommand(description), is_running_(is_running) {}

void ExitCommand::execute(ShapeStorage&) {
    is_running_ = false;
}
