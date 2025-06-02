TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    include/

SOURCES += \
    sourse/circle.cpp \
    sourse/main.cpp \
    sourse/menu.cpp \
    sourse/menu_commands.cpp \
    sourse/point.cpp \
    sourse/point_factory.cpp \
    sourse/polygon.cpp \
    sourse/rectangle.cpp \
    sourse/shape_factory.cpp \
    sourse/storage.cpp \
    sourse/triangle.cpp

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
