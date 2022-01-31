#-------------------------------------------------
#
# Project created by QtCreator 2019-03-14T10:27:28
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = Chrono-Cross
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += main.cpp \
        ihmchronocross.cpp \
        course.cpp \
    ../BaseDeDonnees/basededonnees.cpp \
    chrono.cpp

HEADERS += \
    course.h \
    ihmchronocross.h \
    ../BaseDeDonnees/basededonnees.h \
    chrono.h

FORMS +=

RESOURCES += \
    ressources.qrc
