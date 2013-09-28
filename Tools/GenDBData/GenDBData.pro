#-------------------------------------------------
#
# Project created by QtCreator 2013-09-13T20:05:41
#
#-------------------------------------------------

QT       += core sql

QT       -= gui

TARGET = GenDBData
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    dbconnector.cpp

HEADERS += \
    dbconnector.h

QMAKE_CXXFLAGS_DEBUG += "-D_DEBUG"
