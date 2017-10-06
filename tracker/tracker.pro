#-------------------------------------------------
#
# Project created by QtCreator 2017-09-05T14:18:38
#
#-------------------------------------------------

QT       += widgets sql
QT       -= gui

TARGET = tracker
TEMPLATE = lib

DEFINES += TRACKER_LIBRARY

SOURCES += tracker.cpp \
    data/client.cpp \
    data/project.cpp \
    data/timelog.cpp \
    trackergrid.cpp \
    trackerform.cpp \
    projectdetail.cpp \
    startworkdialog.cpp \
    enddialog.cpp \
    trackerservice.cpp \
    clientdialog.cpp \
    trackeroverview.cpp

HEADERS += tracker.h\
        tracker_global.h \
    data/client.h \
    data/project.h \
    data/tracker-data.h \
    data/timelog.h \
    trackergrid.h \
    trackerform.h \
    projectdetail.h \
    startworkdialog.h \
    enddialog.h \
    trackerservice.h \
    clientdialog.h \
    trackeroverview.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(../config_plugin.pri)

ODB_FILES = tracker/data/tracker-data.h
H_DIR = $$PWD/data/*.h
#ODB_OTHER_INCLUDES = -I $$PWD/../shop
include(../odb.pri)

DISTFILES += \
    tracker.json

RESOURCES += \
    trackerrc.qrc

FORMS += \
    trackerform.ui \
    projectdetail.ui \
    startworkdialog.ui \
    enddialog.ui \
    clientdialog.ui \
    trackeroverview.ui
