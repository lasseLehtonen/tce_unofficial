#-------------------------------------------------
#
# Project created by QtCreator 2015-09-02T13:25:09
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tce_aed
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    src/project.cpp \
    src/asmcodepage.cpp \
    src/asmcodecelldelegate.cpp \
    src/asmcodemodel.cpp \
    src/asmcodeslot.cpp

HEADERS  += mainwindow.h \
    src/project.h \
    src/asmcodepage.h \
    src/asmcodecelldelegate.h \
    src/asmcodemodel.h \
    src/asmcodeslot.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
