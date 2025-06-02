#ifndef MENU_H
#define MENU_H

#include "shape_factory.hpp"
#include <unordered_map>
#include <functional>
#include <vector>

#include "menu_commands.hpp"

enum class Action {
    ADD_SHAPE = 1,
    SHOW_SHAPES,
    SHOW_PERIMETERS,
    SHOW_SUM_OF_PERIMETERS,
    SORT_SHAPES,
    DELETE_SHAPE_BY_POSITION,
    DELETE_SHAPES_BY_PERIMETER,
    EXIT = 8
};

class Menu {
public:
    explicit Menu(ShapeStorage& storage);
    void run();
    bool isRunning() const;

private:
    ShapeStorage& storage_;
    bool isRunning_ = true;
    std::unordered_map<Action, menu_command_ptr> commands_;

private:
    void show_menu() const;
    void execute(Action action);
};

#endif // MENU_H
