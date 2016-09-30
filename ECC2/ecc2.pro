QT += core
QT -= gui

TARGET = test
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    point.cpp \
    curve.cpp \
    algorithms.cpp

LIBS+= -L/usr/lib -lgmp -lgmp -lgivaro
LIBS+= -L/home/andante/Downloads/givaro-4.0.2/src -lgivaro

HEADERS += \
    mathobject.h \
    point.h \
    curve.h \
    algorithms.h

