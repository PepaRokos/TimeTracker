#-------------------------------------------------
#
# Project created by QtCreator 2015-10-28T15:23:55
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timetracker
TEMPLATE = app

DEFINES += _GLIBCXX_USE_CXX11_ABI=1

CONFIG += c++11

include(../config_odb.pri)

win32 {
    INCLUDEPATH += $$ODB_INCLUDE_PREFIX/libodb-2.4.0
    INCLUDEPATH += $$ODB_INCLUDE_PREFIX/libodb-qt-2.4.0
    INCLUDEPATH += $$ODB_INCLUDE_PREFIX/libodb-sqlite-2.4.0
    INCLUDEPATH += $$ODB_INCLUDE_PREFIX/sqlite

    RC_FILE = timetracker.rc
}

SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    application.cpp \
    firststartdata.cpp \
    firststartwizard.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    application.h \
    firststartdata.h \
    firststartwizard.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    firststartwizard.ui

unix {
    target.path = /usr/local/bin
    INSTALLS += target
    QMAKE_CXXFLAGS += -Wno-unknown-pragmas
}

unix{
    ARCH_TYPE      = unix
    macx{
        ARCH_TYPE      = macx
    }
    linux{
        !contains(QT_ARCH, x86_64){
            ARCH_TYPE      = linux32
        }else{
            ARCH_TYPE      = linux64
        }
    }
}

unix {
    QMAKE_CXXFLAGS += -Wno-unknown-pragmas

    CONFIG(debug, debug|release) {
        LIBS += -L$$PWD/../3rd/LimeReport/build/$${QT_VERSION}/$${ARCH_TYPE}/debug/lib/ -llimereport -lQtZint
        #QMAKE_CXXFLAGS += -Wl,-rpath-link,$$PWD/../3rd/LimeReport/build/$${QT_VERSION}/$${ARCH_TYPE}/debug/lib/
    } else {
        LIBS += -L$$PWD/../3rd/LimeReport/build/$${QT_VERSION}/$${ARCH_TYPE}/release/lib/ -llimereport -lQtZint
        #QMAKE_CXXFLAGS += -Wl,-rpath-link,$$PWD/../3rd/LimeReport/build/$${QT_VERSION}/$${ARCH_TYPE}/release/lib/
    }
}

win32 {
    QMAKE_CXXFLAGS += -wd4995 -wd4068
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../application/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../application/debug/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../application/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rd/qdecimal/lib/ -lqdecimal -ldecnumber
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rd/qdecimal/lib/ -lqdecimal -ldecnumber
else:unix: LIBS += -L$$OUT_PWD/../3rd/qdecimal/lib/ -lqdecimal -ldecnumber

INCLUDEPATH += $$PWD/../3rd/qdecimal/src
INCLUDEPATH += $$PWD/../3rd/qdecimal/decnumber

RESOURCES += \
    appRc.qrc

TRANSLATIONS = translations/timetracker_cs_CZ.ts

DISTFILES += \
    timetracker.rc
