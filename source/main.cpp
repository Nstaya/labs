#include "storage.hpp"
#include "menu.hpp"
#include "shape_factory.hpp"
#include <iostream>

int main() {
    registerShapeCreators();
    ShapeStorage storage;
    Menu menu(storage);
    menu.run();
    return 0;
}
