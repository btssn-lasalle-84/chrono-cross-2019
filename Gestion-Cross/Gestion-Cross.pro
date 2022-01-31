#-------------------------------------------------
#
# Project created by QtCreator 2019-05-29T15:18:52
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gestion-Cross
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += main.cpp \
        ihmgestioncross.cpp \
    ../BaseDeDonnees/basededonnees.cpp \
    gestionbdd.cpp

HEADERS += \
        ihmgestioncross.h \
    ../BaseDeDonnees/basededonnees.h \
    gestionbdd.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
