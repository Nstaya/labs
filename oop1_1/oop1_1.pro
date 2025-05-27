TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        circle.cpp \
        main.cpp \
        menu.cpp \
        point.cpp \
        point_factory.cpp \
        polygon.cpp \
        rectangle.cpp \
        shape_factory.cpp \
        storage.cpp \
        triangle.cpp

HEADERS += \
    circle.h \
    menu.h \
    point.h \
    point_factory.h \
    polygon.h \
    rectangle.h \
    shape.h \
    shape_factory.h \
    storage.h \
    triangle.h
