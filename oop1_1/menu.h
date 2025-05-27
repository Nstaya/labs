#ifndef MENU_H
#define MENU_H

#include "storage.h"
#include "shape_factory.h"
#include <unordered_map>
#include <functional>
#include <vector>

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

    static void showMainMenu();
    static void showShapeTypes();

    void execute(Action action);
    void run();
    bool isRunning() const;

private:
    void addShape();
    void showShapes() const;
    void showPerimeters() const;
    void showSumOfPerimeters() const;
    void sortShapes();
    void deleteShapeByPosition();
    void deleteShapesByPerimeter();

    ShapeStorage& storage_;
    bool isRunning_ = true;
    std::unordered_map<Action, std::function<void()>> commands_;
};

#endif // MENU_H
