#include "menu.hpp"
#include <iostream>

int main() {
    ShapeStorage storage;
    Menu menu(storage);
    menu.run();
    return 0;
}
