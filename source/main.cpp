#include "menu.hpp"
#include <iostream>

int main() {
    std::cout << ";(" << std::endl;
    ShapeStorage storage;
    Menu menu(storage);
    menu.run();
    return 0;
}
