QT += core gui
TARGET = ShapeMS
TEMPLATE = app

INCLUDEPATH += include
DEPENDPATH += include

SOURCES += \
    source/circle.cpp \
    source/main.cpp \
    source/menu.cpp \
    source/point.cpp \
    source/point_factory.cpp \
    source/polygon.cpp \
    source/rectangle.cpp \
    source/shape_factory.cpp \
    source/storage.cpp \
    source/triangle.cpp

HEADERS += \
    include/circle.hpp \
    include/menu.hpp \
    include/point.hpp \
    include/point_factory.hpp \
    include/polygon.hpp \
    include/rectangle.hpp \
    include/shape.hpp \
    include/shape_factory.hpp \
    include/storage.hpp \
    include/triangle.hpp