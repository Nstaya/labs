#include "storage.h"
#include "menu.h"
#include "shape_factory.h"
#include <iostream>

int main() {

    try {
        registerShapeCreators();
        ShapeStorage storage;
        Menu menu(storage);
        menu.run();
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
