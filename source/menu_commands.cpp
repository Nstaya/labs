#include "menu_commands.hpp"
#include "shape_factory.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>

MenuCommand::MenuCommand(const std::string &description) : description_(description) {}

const std::string MenuCommand::get_description() const {
    return this->description_;
}

AddShapeCommand::AddShapeCommand(const std::string& description):MenuCommand(description) {}

void AddShapeCommand::execute(ShapeStorage &storage) {
    std::cout << "\nВыберите тип фигуры: ";

    std::string input;
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cout << "\nОшибка: введите число от 1 до 4" << std::endl;
        return;
    }
    try {
        int typeChoice = std::stoi(input);
        static const std::unordered_map<int, std::string> typeMap = {
            {1, "circle"},
            {2, "rectangle"},
            {3, "triangle"},
            {4, "polygon"}
        };

        auto it = typeMap.find(typeChoice);
        if (it == typeMap.end()) {
            std::cout << "\nОшибка: введите число от 1 до 4" << std::endl;
            return;
        }
        const std::string& type = it->second;

        std::cout << "\nВведите название фигуры: ";
        std::string name;
        std::getline(std::cin, name);

        std::cout << "\nВведите параметры фигуры через пробел: ";
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
            std::cout << "\nФигура успешно добавлена\n";
        } catch (const std::exception& e) {
            std::cout << "\nОшибка при создании фигуры: " << e.what() << "\n";
        }
    } catch (...) {
        std::cout << "\nОшибка: введите число от 1 до 4\n";
    }
}

ShowShapesCommand::ShowShapesCommand(const std::string& description):MenuCommand(description) {}

void ShowShapesCommand::execute(ShapeStorage& storage) {
    const auto& shapes = storage.getShapes();
    if (shapes.empty()) {
        std::cout << "Коллекция фигур пуста\n";
        return;
    }

    std::cout << "\nСписок фигур:\n";
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << i+1 << ". " << shapes[i]->parameters() << "\n";
    }
}

ShowPerimetersCommand::ShowPerimetersCommand(const std::string& description)
    : MenuCommand(description) {}

void ShowPerimetersCommand::execute(ShapeStorage& storage) {
    const auto& shapes = storage.getShapes();
    if (shapes.empty()) {
        std::cout << "Коллекция фигур пуста\n";
        return;
    }

    std::cout << "\nПериметры фигур:\n";
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << i+1 << ". " << shapes[i]->type() << " '" << shapes[i]->name
                  << "': " << shapes[i]->perimeter() << "\n";
    }
}

ShowSumOfPerimetersCommand::ShowSumOfPerimetersCommand(const std::string& description)
    : MenuCommand(description) {}

void ShowSumOfPerimetersCommand::execute(ShapeStorage& storage) {
    std::cout << "\nСумма периметров: " << storage.getTotalPerimeter() << "\n";
}

SortShapesCommand::SortShapesCommand(const std::string& description)
    : MenuCommand(description) {}

void SortShapesCommand::execute(ShapeStorage& storage) {
    storage.sortByPerimeter();
    std::cout << "Фигуры отсортированы по периметру\n";
}

DeleteShapeByPositionCommand::DeleteShapeByPositionCommand(const std::string& description)
    : MenuCommand(description) {}

void DeleteShapeByPositionCommand::execute(ShapeStorage& storage) {
    if (storage.count() == 0) {
        std::cout << "Коллекция фигур пуста\n";
        return;
    }

    std::cout << "Введите номер фигуры (1-" << storage.count() << "): ";
    std::string input;
    std::getline(std::cin, input);

    try {
        size_t index = std::stoul(input);
        if (index < 1 || index > storage.count()) {
            std::cout << "Неверный номер\n";
            return;
        }
        storage.removeShape(index - 1);
        std::cout << "Фигура удалена\n";
    }
    catch (...) {
        std::cout << "Ошибка при удалении\n";
    }
}

DeleteShapesByPerimeterCommand::DeleteShapesByPerimeterCommand(const std::string& description)
    : MenuCommand(description) {}

void DeleteShapesByPerimeterCommand::execute(ShapeStorage& storage) {
    if (storage.count() == 0) {
        std::cout << "Коллекция фигур пуста\n";
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
        std::cout << "Удалено фигур: " << removed << "\n";
    }
    catch (...) {
        std::cout << "Ошибка при удалении\n";
    }
}

ExitCommand::ExitCommand(const std::string& description, bool& is_running)
    : MenuCommand(description), is_running_(is_running) {}

void ExitCommand::execute(ShapeStorage&) {
    is_running_ = false;
}
