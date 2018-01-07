DEFINES += _GLIBCXX_USE_CXX11_ABI=1 \
            APP_NAME=timetracker

CONFIG += c++11


unix {
    target.path = /usr/local/lib/timetracker/plugins
    INSTALLS += target
    QMAKE_CXXFLAGS += -Wno-unknown-pragmas
}

win32 {
    QMAKE_CXXFLAGS += -wd4995 -wd4068
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../application/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../application/debug/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../application/ -lcore

INCLUDEPATH += $$PWD/core
INCLUDEPATH += $$PWD/core/data
DEPENDPATH += $$PWD/core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rd/qdecimal/lib/ -lqdecimal -ldecnumber
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rd/qdecimal/lib/ -lqdecimal -ldecnumber
else:unix: LIBS += -L$$OUT_PWD/../3rd/qdecimal/lib/ -lqdecimal -ldecnumber

INCLUDEPATH += $$PWD/3rd/qdecimal/src
INCLUDEPATH += $$PWD/3rd/qdecimal/decnumber
DEPENDPATH += $$PWD/3rd/qdecimal/src

DESTDIR = ../plugins
