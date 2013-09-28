#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T16:14:13
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SilkRoute
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    dbconnector.cpp \
    dbutils.cpp \
    preferencesdialog.cpp \
    itable.cpp \
    usertable.cpp \
    supplierwidget.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    dbconnector.h \
    usertable.h \
    dbutils.h \
    preferencesdialog.h \
    itable.h \
    supplierwidget.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    preferencesdialog.ui \
    supplierwidget.ui

# Pre-processor definitions

# Only add _DEBUG def when debug compilation is made
QMAKE_CXXFLAGS_DEBUG += "-D_DEBUG" \
                        "-D_TESTING"

RESOURCES += \
    imageres.qrc
