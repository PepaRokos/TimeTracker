include(config_odb.pri)

win32 {
    LIBS += -L$$LIB_PATH
    INCLUDEPATH += $$ODB_INCLUDE_PREFIX/libodb-2.4.0
    INCLUDEPATH += $$ODB_INCLUDE_PREFIX/libodb-qt-2.4.0
    INCLUDEPATH += $$ODB_INCLUDE_PREFIX/libodb-sqlite-2.4.0
    INCLUDEPATH += $$ODB_INCLUDE_PREFIX/sqlite
}

win32 {
    CONFIG(debug, debug|release) {
        LIBS += -lodb-d -lodb-sqlite-d -lodb-qt-d
    }else {
        LIBS += -lodb -lodb-sqlite -lodb-qt
    }
}

unix {
    LIBS += -lodb -lodb-sqlite -lodb-qt
}

ODB_FLAGS += --database sqlite --profile qt --generate-schema --generate-query --generate-session --at-once --input-name $$TARGET --schema-format sql

win32 {
    ODB_PATH = $$ODB_INCLUDE_PREFIX\odb-2.4.0-i686-windows\bin\odb
}
unix {
    ODB_PATH = odb
}

# Select the database we are going to use.
#
DEFINES += DATABASE_SQLITE

# Suppress unknown pragmas GCC warnings.
#
#QMAKE_CXXFLAGS_WARN_ON = $$QMAKE_CXXFLAGS_WARN_ON -Wno-unknown-pragmas

# ODB compilation rules. Normally you don't need to change anything here.
#

# Add the Qt headers directory to the ODB include directory list.
#
ODB_FLAGS += -I $$[QT_INSTALL_HEADERS]
ODB_FLAGS += -I $$[QT_INSTALL_HEADERS]/QtCore
ODB_FLAGS += -I $$PWD/core
ODB_FLAGS += -I $$PWD/core/data
ODB_FLAGS += -I $$PWD/3rd/qdecimal/src
ODB_FLAGS += -I $$PWD/3rd/qdecimal/decnumber
ODB_FLAGS += $$ODB_OTHER_INCLUDES
ODB_FLAGS += -x -std=c++11 -x -fPIC

win32 {
    ODB_FLAGS += -I $$ODB_INCLUDE_PREFIX/libodb-2.4.0
}

# Newer versions of QtCreator do builds in a separate directory. As a
# result, we need to append the source directory to ODB files.
#
for(dir, ODB_FILES) {
  ODB_PWD_FILES += $$PWD/$${dir}
}

win32 {
    H_DIR ~= s,/,\\,g
}
export(H_DIR)


odb.name = odb ${QMAKE_FILE_IN}
odb.input = ODB_PWD_FILES
odb.output = $$TARGET-odb.cxx
odb.commands = $$ODB_PATH $$ODB_FLAGS ${QMAKE_FILE_IN}
odb.depends = $$ODB_PWD_FILES
odb.variable_out = SOURCES
odb.CONFIG = target_predeps
odb.clean = $$TARGET-odb.cxx $$TARGET-odb.hxx $$TARGET-odb.ixx $$TARGET.sql *.h *.sql
QMAKE_EXTRA_COMPILERS += odb

odbh.name = odb ${QMAKE_FILE_IN}
odbh.input = ODB_PWD_FILES
odbh.output = $$TARGET-odb.hxx
odbh.commands = @true
odbh.depends = $$TARGET-odb.cxx
odbh.CONFIG = no_link
QMAKE_EXTRA_COMPILERS += odbh

odbhc.target = odbhc
unix {
    odbhc.commands = $(COPY) -p $$H_DIR .
}
win32 {
    odbhc.commands = $(COPY) $$H_DIR .
}
QMAKE_EXTRA_TARGETS += odbhc

PRE_TARGETDEPS += odbhc
