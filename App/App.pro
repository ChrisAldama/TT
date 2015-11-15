TEMPLATE = app
CONFIG += c++11

QT += widgets webkitwidgets serialport

SOURCES += main.cpp \
    mainwindow.cpp \
    parser.cpp \
    variable.cpp \
    tablavariables.cpp \
    test.cpp \
    comm.cpp \
    commserial.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    parser.h \
    variable.h \
    tablavariables.h \
    test.h \
    comm.h \
    commserial.h

DISTFILES += \
    p_test.olinki \
    p_test_sino.olinki

