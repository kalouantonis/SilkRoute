#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T16:14:13
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#Version data
VER_MAJ = 1
VER_MIN = 1
VER_PAT = 0

# Target build name
TARGET = SilkRoute
# Build type
TEMPLATE = app

# Add subdirectories
SUBDIRS += Suppliers \
            Users     \
            Database   \
            Stock       \
            Base#

# destination binary directory #########################
#debug:DESTDIR = ../bin/Debug
#release:DESTDIR = ../bin/Release
DESTDIR = ../bin

# Object build directory ###############################
#OBJECTS_DIR = ../obj
#MOC_DIR = ../obj/moc
#UI_DIR = ../obj/ui

# Post build dependencies
POST_TARGETDEPS += ../data.sqlite

# Include all files from current dir
INCLUDEPATH = ../

SOURCES += main.cpp\
        mainwindow.cpp \
    Users/logindialog.cpp \
    Database/dbconnector.cpp \
    Database/dbutils.cpp \
    preferencesdialog.cpp \
    Database/itable.cpp \
    Users/usertable.cpp \
    Suppliers/supplierwidget.cpp \
    Suppliers/supplieractiondialog.cpp \
    Stock/stockwidget.cpp \
    Suppliers/suppliertable.cpp \
    Database/itablemodel.cpp \
    Base/mdiwidget.cpp

HEADERS  += mainwindow.h \
    Users/logindialog.h \
    Database/dbconnector.h \
    Users/usertable.h \
    Database/dbutils.h \
    preferencesdialog.h \
    Database/itable.h \
    Suppliers/supplierwidget.h \
    Suppliers/supplieractiondialog.h \
    Stock/stockwidget.h \
    Suppliers/suppliertable.h \
    Database/itablemodel.h \
    Base/mdiwidget.h

FORMS    += mainwindow.ui \
    Users/logindialog.ui \
    preferencesdialog.ui \
    Suppliers/supplieractiondialog.ui \
    Base/mdiwidget.ui

# Pre-processor definitions
# Only add _DEBUG def when debug compilation is made
QMAKE_CXXFLAGS_DEBUG += "-D_DEBUG" \
                        "-D_TESTING"

QMAKE_CXXFLAGS_RELEASE += "-DNDEBUG"

# C++11 support
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    imageres.qrc
