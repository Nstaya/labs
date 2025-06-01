#include "menu.hpp"
#include <iostream>
#include <stdexcept>

Menu::Menu(ShapeStorage& storage) : storage_(storage) {
    this->commands_[Action::ADD_SHAPE] = std::make_shared<AddShapeCommand>("Добавить фигуру");
    this->commands_[Action::SHOW_SHAPES] = std::make_shared<ShowShapesCommand>("Показать список фигур");
    this->commands_[Action::SHOW_PERIMETERS] = std::make_shared<ShowPerimetersCommand>("Показать периметры");
    this->commands_[Action::SHOW_SUM_OF_PERIMETERS] = std::make_shared<ShowSumOfPerimetersCommand>("Показать сумму периметров");
    this->commands_[Action::SORT_SHAPES] = std::make_shared<SortShapesCommand>("Отсортировать фигуры");
    this->commands_[Action::DELETE_SHAPE_BY_POSITION] = std::make_shared<DeleteShapeByPositionCommand>("Удалить фигуру по номеру");
    this->commands_[Action::DELETE_SHAPES_BY_PERIMETER] = std::make_shared<DeleteShapesByPerimeterCommand>("Удалить фигуры по периметру");
    this->commands_[Action::EXIT] = std::make_shared<ExitCommand>("Выход", isRunning_);
}

void Menu::show_menu() const {
    std::cout << "\nМеню:\n";
    for (const auto& [action, cmd] : commands_) {
        std::cout << static_cast<int>(action) << ". "
                  << cmd->get_description() << "\n";
    }
}

void Menu::execute(Action action) {
    try {
        commands_.at(action)->execute(storage_);
    }
    catch (const std::out_of_range&) {
        std::cout << "Неизвестная команда\n";
    }
}

void Menu::run() {
    while (isRunning()) {
        show_menu();
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
