#-------------------------------------------------
#
# Project created by QtCreator 2017-10-06T14:35:36
#
#-------------------------------------------------

QT       += widgets network sql
QT       -= gui

TARGET = addressbook
TEMPLATE = lib

DEFINES += ADDRESSBOOK_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += addressbook.cpp \
    data/address.cpp \
    addressgrid.cpp \
    addressform.cpp

HEADERS += addressbook.h\
        addressbook_global.h \
    data/address.h \
    data/addressbook-data.h \
    addressgrid.h \
    addressform.h


include(../config_plugin.pri)

ODB_FILES = addressbook/data/addressbook-data.h
H_DIR = $$PWD/data/*.h
#ODB_OTHER_INCLUDES = -I $$PWD/../shop
include(../odb.pri)

DISTFILES += \
    addressbook.json

RESOURCES += \
    addressbook.qrc

FORMS += \
    addressform.ui
