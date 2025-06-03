TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    include/

SOURCES += \
    source/circle.cpp \
    source/main.cpp \
    source/menu.cpp \
    source/menu_commands.cpp \
    source/point.cpp \
    source/point_factory.cpp \
    source/polygon.cpp \
    source/rectangle.cpp \
    source/shape_factory.cpp \
    source/storage.cpp \
    source/triangle.cpp \
    source/shape.cpp

HEADERS += \
    include/circle.hpp \
    include/menu.hpp \
    include/menu_commands.hpp \
    include/point.hpp \
    include/point_factory.hpp \
    include/polygon.hpp \
    include/rectangle.hpp \
    include/shape.hpp \
    include/shape_factory.hpp \
    include/shapes.hpp \
    include/storage.hpp \
    include/triangle.hpp
