#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T16:14:13
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#Version data
VER_MAJ = 1
VER_MIN = 1
VER_PAT = 1

# Target build name
TARGET = SilkRoute
# Build type
TEMPLATE = app

# Add subdirectories
SUBDIRS += Suppliers \
            Users     \
            Database   \
            Stock       \
            Base        \
            Transactions

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
#INCLUDEPATH += "../Dependencies/kdreports-1.5.0-source/include/KDReports"
#INCLUDEPATH += /usr/lib/qt4

SOURCES += main.cpp\
        mainwindow.cpp \
    preferencesdialog.cpp \
    Users/usertable.cpp \
    Users/logindialog.cpp \
    Stock/stockwidget.cpp \
    Suppliers/supplierwidget.cpp \
    Suppliers/supplieractiondialog.cpp \
    Suppliers/suppliertable.cpp \
    Database/itablemodel.cpp \
    Database/itable.cpp \
    Database/dbconnector.cpp \
    Database/dbutils.cpp \
    Base/mdiwidget.cpp \
    Transactions/transactionwidget.cpp \
    Transactions/transactiontable.cpp \
    Stock/stocktable.cpp \
    Transactions/transactionactiondialog.cpp \
    Stock/stockactiondialog.cpp \
    Types/typeactiondialog.cpp \
    Types/typestable.cpp \
    Types/typeswidget.cpp \
    Utils/Logger.cpp \
    Transactions/plusminuspushwidget.cpp \
    Base/dateformatdelegate.cpp \
    Base/mathutils.cpp \
    Reports/reportgeneratedialog.cpp \
    Reports/reporttable.cpp \
    Reports/reportview.cpp \
    Base/currencyformatdelegate.cpp

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
    Base/mdiwidget.h \
    Transactions/transactionwidget.h \
    Transactions/transactiontable.h \
    Stock/stocktable.h \
    Transactions/transactionactiondialog.h \
    Stock/stockactiondialog.h \
    Types/typeactiondialog.h \
    Types/typestable.h \
    Types/typeswidget.h \
    Utils/Logger.h \
    Database/imodel.h \
    Transactions/plusminuspushwidget.h \
    Base/dateformatdelegate.h \
    Base/mathutils.h \
    Reports/reportgeneratedialog.h \
    Reports/reporttable.h \
    Reports/reportview.h \
    Base/currencyformatdelegate.h \
    Base/itemreferencedexception.h

FORMS    += mainwindow.ui \
    Users/logindialog.ui \
    preferencesdialog.ui \
    Suppliers/supplieractiondialog.ui \
    Base/mdiwidget.ui \
    Transactions/transactionactiondialog.ui \
    Stock/stockactiondialog.ui \
    Types/typeactiondialog.ui \
    Reports/reportgeneratedialog.ui

# Pre-processor definitions
# Only add _DEBUG def when debug compilation is made
QMAKE_CXXFLAGS_DEBUG += "-D_DEBUG" \
                        "-D_TESTING" \
                        "-Wno-missing-field-initializers" \ # Get rid of pesky(useless) warnings in debug mode
                        "-ggdb"

QMAKE_CXXFLAGS_RELEASE += "-DNDEBUG"

# C++11 support
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    imageres.qrc

OTHER_FILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Dependencies/kdreports-1.5.0-source/lib/release/ -lkdreports
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Dependencies/kdreports-1.5.0-source/lib/debug/ -lkdreports
else:unix:!macx: LIBS += -L$$PWD/../Dependencies/kdreports-1.5.0-source/lib/ -lkdreports

INCLUDEPATH += $$PWD/../Dependencies/kdreports-1.5.0-source/include/KDReports
DEPENDPATH += $$PWD/../Dependencies/kdreports-1.5.0-source/include/KDReports
