#include "menu_commands.hpp"
#include "shape_factory.hpp"
#include "storage.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

MenuCommand::MenuCommand(const std::string &description) : description_(description) {}

const std::string MenuCommand::get_description() const {
    return this->description_;
}

AddShapeCommand::AddShapeCommand(const std::string &description) : MenuCommand(description) {}

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

ShowShapesCommand::ShowShapesCommand(const std::string &description) : MenuCommand(description) {}

void ShowShapesCommand::execute(ShapeStorage &storage) {
}

DeleteShapeByPositionCommand::DeleteShapeByPositionCommand(const std::string &description) : MenuCommand(description) {}

void DeleteShapeByPositionCommand::execute(ShapeStorage &storage) {
}

ExitCommand::ExitCommand(const std::string &description) : MenuCommand(description) {}

void ExitCommand::execute(ShapeStorage &storage) {
}