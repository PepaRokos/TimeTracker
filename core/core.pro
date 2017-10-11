#-------------------------------------------------
#
# Project created by QtCreator 2015-10-28T15:25:33
#
#-------------------------------------------------

#iconset: https://www.iconfinder.com/iconsets/snipicons

QT       += widgets sql printsupport

TARGET = core
TEMPLATE = lib

DEFINES += CORE_LIBRARY \
           _GLIBCXX_USE_CXX11_ABI=1 \
           APP_NAME=\\\"timetracker\\\"

CONFIG += c++11

win32:CONFIG(release, debug|release): DESTDIR = ../application/release
else:win32:CONFIG(debug, debug|release): DESTDIR = ../application/debug
else:unix: DESTDIR = ../application

SOURCES += \
    data/user.cpp \
    context.cpp \
    imetadataplugin.cpp \
    transaction.cpp \
    emptystringvalidator.cpp \
    data/role.cpp \
    data/permission.cpp \
    coreplugin.cpp \
    igridform.cpp \
    defaultformhandler.cpp \
    formdialog.cpp \
    iform.cpp \
    users/users.cpp \
    users/usersui.cpp \
    users/tablemodel.cpp \
    users/userform.cpp \
    columndialog.cpp \
    roles/rolestablemodel.cpp \
    roles/roles.cpp \
    roles/rolesui.cpp \
    roles/rolesform.cpp \
    permissionservice.cpp \
    filterui.cpp \
    exprevaluator.cpp \
    samestringvalidator.cpp \
    savefilterdialog.cpp \
    filterdialog.cpp \
    itablemodel.cpp \
    iservice.cpp \
    combodata.cpp \
    data/comboitem.cpp \
    settingsservice.cpp \
    data/system.cpp \
    settings/globalsettings.cpp \
    settingsform.cpp \
    settings/globalsettingsform.cpp \
    permissionevaluator.cpp \
    objectbinder.cpp \
    data/numberseries.cpp \
    data/season.cpp \
    seasonservice.cpp \
    numberseriesservice.cpp \
    settings/seasonnamedialog.cpp \
    reporting/report.cpp \
    reporting/reportviewer.cpp \
    reporting/reportdialog.cpp \
    csvimporter.cpp \
    importdialog.cpp \
    importprogress.cpp \
    reporting/variablefiller.cpp

HEADERS += core.h\
        core_global.h \
    iplugin.h \
    service.h \
    data/user.h \
    context.h \
    imetadataplugin.h \
    autotablemodel.h \
    autoform.h \
    transaction.h \
    ivalidator.h \
    emptystringvalidator.h \
    data/role.h \
    data/permission.h \
    data/core-data.h \
    coreplugin.h \
    define.h \
    gridform.h \
    igridform.h \
    defaultformhandler.h \
    formdialog.h \
    iform.h \
    users/users.h \
    users/usersui.h \
    users/tablemodel.h \
    users/userform.h \
    columndialog.h \
    roles/rolestablemodel.h \
    roles/roles.h \
    roles/rolesui.h \
    roles/rolesform.h \
    permissionservice.h \
    filterui.h \
    exprevaluator.h \
    samestringvalidator.h \
    savefilterdialog.h \
    filterdialog.h \
    itablemodel.h \
    data/core_global.h \
    iservice.h \
    combodata.h \
    data/comboitem.h \
    settingsservice.h \
    data/system.h \
    enums.h \
    settings/globalsettings.h \
    settingsform.h \
    settings/globalsettingsform.h \
    formbinder.h \
    permissionevaluator.h \
    objectbinder.h \
    data/numberseries.h \
    data/season.h \
    seasonservice.h \
    numberseriesservice.h \
    settings/seasonnamedialog.h \
    reporting/report.h \
    reporting/reportviewer.h \
    reporting/reportdialog.h \
    iimporter.h \
    csvimporter.h \
    iimportprogress.h \
    importdialog.h \
    importprogress.h \
    reporting/variablefiller.h \
    idashboardwidget.h

unix {
    target.path = /usr/local/lib/timetracker
    INSTALLS += target

    ldconf.path = /etc/ld.so.conf.d
    ldconf.files = ld.conf/*
    INSTALLS += ldconf

    QMAKE_CXXFLAGS += -Wno-unknown-pragmas
}

win32 {
    QMAKE_CXXFLAGS += -wd4995 -wd4068
}

ODB_FILES = core/data/core-data.h
H_DIR = $$PWD/data/*.h
include(../odb.pri)

RESOURCES += \
    rc.qrc

DISTFILES += \
    metaData.json

FORMS += \
    gridform.ui \
    formdialog.ui \
    users/userform.ui \
    columndialog.ui \
    roles/rolesform.ui \
    filterui.ui \
    savefilterdialog.ui \
    filterdialog.ui \
    settingsform.ui \
    settings/globalsettingsform.ui \
    settings/seasonnamedialog.ui \
    reporting/reportviewer.ui \
    reporting/reportdialog.ui \
    importdialog.ui \
    importprogress.ui

OTHER_FILES += \
    users/metaData.json \
    roles/metaData.json

CONFIG(debug, release|debug):DEFINES += _DEBUG

win32:CONFIG(release, debug|release):DEFINES += PLUGIN_ROOT=\\\"/plugins\\\"

win32:CONFIG(release, debug|release):DEFINES += REPORT_ROOT=\\\"/reports\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qdecimal/lib/ -lqdecimal -ldecnumber
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qdecimal/lib/ -lqdecimal -ldecnumber
else:unix: LIBS += -L$$OUT_PWD/../qdecimal/lib/ -lqdecimal -ldecnumber

INCLUDEPATH += $$PWD/../qdecimal/src
INCLUDEPATH += $$PWD/../qdecimal/decnumber

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
win32 {
    ARCH_TYPE      = win32
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LimeReport/build/$${QT_VERSION}/$${ARCH_TYPE}/release/lib/ -llimereport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LimeReport/build/$${QT_VERSION}/$${ARCH_TYPE}/debug/lib/ -llimereport
else:unix: LIBS += -L$$PWD/../../LimeReport/build/$${QT_VERSION}/$${ARCH_TYPE}/debug/lib/ -llimereport

INCLUDEPATH += $$PWD/../../LimeReport/include
DEPENDPATH += $$PWD/../../LimeReport/include

TRANSLATIONS = translations/core_cs_CZ.ts
