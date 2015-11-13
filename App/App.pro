TEMPLATE = app
CONFIG += c++11

QT += widgets webkitwidgets webchannel websockets network

SOURCES += main.cpp \
    mainwindow.cpp \
    websocketclientwrapper.cpp \
    websockettransport.cpp \
    channel.cpp \
    parser.cpp \
    variable.cpp \
    tablavariables.cpp \
    test.cpp \
    comm.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    websocketclientwrapper.h \
    websockettransport.h \
    channel.h \
    parser.h \
    variable.h \
    tablavariables.h \
    test.h \
    comm.h

DISTFILES += \
    p_test.olinki \
    p_test_sino.olinki

