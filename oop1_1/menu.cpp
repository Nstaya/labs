#include "menu.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>
#include <unordered_map>

Menu::Menu(ShapeStorage& storage) : storage_(storage) {
    commands_ = {
        {Action::ADD_SHAPE, [this]() { addShape(); }},
        {Action::SHOW_SHAPES, [this]() { showShapes(); }},
        {Action::SHOW_PERIMETERS, [this]() { showPerimeters(); }},
        {Action::SHOW_SUM_OF_PERIMETERS, [this]() { showSumOfPerimeters(); }},
        {Action::SORT_SHAPES, [this]() { sortShapes(); }},
        {Action::DELETE_SHAPE_BY_POSITION, [this]() { deleteShapeByPosition(); }},
        {Action::DELETE_SHAPES_BY_PERIMETER, [this]() { deleteShapesByPerimeter(); }},
        {Action::EXIT, [this]() { isRunning_ = false; }}
    };
}

void Menu::showMainMenu() {
    std::cout << "\nМеню:" << std::endl;
    std::cout << "1. Добавить фигуру" << std::endl;
    std::cout << "2. Вывести список фигур" << std::endl;
    std::cout << "3. Вывести периметры фигур" << std::endl;
    std::cout << "4. Вывести сумму периметров" << std::endl;
    std::cout << "5. Отсортировать фигуры по периметру" << std::endl;
    std::cout << "6. Удалить фигуру по номеру" << std::endl;
    std::cout << "7. Удалить фигуры с периметром больше заданного" << std::endl;
    std::cout << "8. Выход" << std::endl;
}

void Menu::showShapeTypes() {
    std::cout << "\nТипы фигур:" << std::endl;
    std::cout << "1. Круг" << std::endl;
    std::cout << "2. Прямоугольник" << std::endl;
    std::cout << "3. Треугольник" << std::endl;
    std::cout << "4. Многоугольник" << std::endl;
}

void Menu::execute(Action action) {
    try {
        auto it = commands_.find(action);
        if (it != commands_.end()) {
            it->second();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << std::endl;
    }
}

void Menu::run() {
    while (isRunning_) {
        showMainMenu();
        std::cout << "\nВыберите действие: ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        try {
            int choice = std::stoi(input);
            if (choice >= 1 && choice <= 8) {
                execute(static_cast<Action>(choice));
            } else {
                std::cout << "\nОшибка: введите число от 1 до 8" << std::endl;
            }
        } catch (const std::invalid_argument&) {
            std::cout << "\nОшибка: введите число от 1 до 8" << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "\nОшибка: число слишком большое" << std::endl;
        }
    }
}

bool Menu::isRunning() const {
    return isRunning_;
}

void Menu::addShape() {
    showShapeTypes();
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
            storage_.addShape(std::move(shape));
            std::cout << "\nФигура успешно добавлена\n";
        } catch (const std::exception& e) {
            std::cout << "\nОшибка при создании фигуры: " << e.what() << "\n";
        }
    } catch (...) {
        std::cout << "\nОшибка: введите число от 1 до 4\n";
    }
}

void Menu::showShapes() const {
    const auto& shapes = storage_.getShapes();
    if (shapes.empty()) {
        std::cout << "\nКоллекция фигур пуста" << std::endl;
        return;
    }

    std::cout << "\nСписок фигур:" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << i+1 << ". " << shapes[i]->parameters() << "" << std::endl;
    }
}

void Menu::showPerimeters() const {
    const auto& shapes = storage_.getShapes();
    if (shapes.empty()) {
        std::cout << "\nКоллекция фигур пуста" << std::endl;
        return;
    }

    std::cout << "\nПериметры фигур:" << std::endl;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << i+1 << ". " << shapes[i]->type() << " '" << shapes[i]->name
                  << "': Периметр = " << shapes[i]->perimeter() << "" << std::endl;
    }
}

void Menu::showSumOfPerimeters() const {
    std::cout << "\nСумма периметров всех фигур: " << storage_.getTotalPerimeter() << "" << std::endl;
}

void Menu::sortShapes() {
    storage_.sortByPerimeter();
    std::cout << "\nФигуры отсортированы по периметру" << std::endl;
}

void Menu::deleteShapeByPosition() {
    if (storage_.count() == 0) {
        std::cout << "\n Kоллекция фигур пуста " << std::endl;
        return;
    }

    std::cout << "\nВведите номер фигуры для удаления (1-" << storage_.count() << "): ";
    std::string input;
    std::getline(std::cin, input);

    try {
        size_t index = std::stoul(input);
        if (index < 1 || index > storage_.count()) {
            std::cout << "\nНеверный номер фигуры" << std::endl;
            return;
        }
        storage_.removeShape(index - 1);
        std::cout << "\nФигура удалена" << std::endl;
    } catch (...) {
        std::cout << "\nНеверный номер фигуры" << std::endl;
    }
}

void Menu::deleteShapesByPerimeter() {
    if (storage_.count() == 0) {
        std::cout << "Коллекция фигур пуста" << std::endl;
        return;
    }

    std::cout << "\nВведите максимальное значение периметра: ";
    std::string input;
    std::getline(std::cin, input);

    try {
        double maxPerimeter = std::stod(input);
        size_t before = storage_.count();
        storage_.removeIf([maxPerimeter](const Shape& shape) {
            return shape.perimeter() > maxPerimeter;
        });
        size_t after = storage_.count();
        std::cout << "\nУдалено " << (before - after) << " фигур" << std::endl;
    } catch (...) {
        std::cout << "\nНеверное значение" << std::endl;
    }
}
