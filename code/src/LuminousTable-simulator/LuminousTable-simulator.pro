#-------------------------------------------------
#
# Project created by QtCreator 2014-05-10T10:35:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LuminousTable-simulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qdotmatrix.cpp

HEADERS  += mainwindow.h \
    qdotmatrix.h \
    FakeHardware.h

#FORMS    +=

DEFINES += MODE_SIMULATOR