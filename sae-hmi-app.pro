QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp
SOURCES += pilot-view.cpp
SOURCES += system-configuration.cpp
SOURCES += can-interface/can-interface.cpp
SOURCES += base-plot.cpp
SOURCES += base-test-window.cpp
SOURCES += qcustomplot/qcustomplot.cpp
SOURCES += main-sae-hmi-app.cpp

HEADERS += main-sae-hmi-app.h
HEADERS += pilot-view.h
HEADERS += system-configuration.h
HEADERS += can-interface/can-interface.h
HEADERS += base-plot.h
HEADERS += base-test-window.h
HEADERS += qcustomplot/qcustomplot.h

FORMS += main-sae-hmi-app.ui
FORMS += pilot-view.ui
FORMS += system-configuration.ui
FORMS += base-plot.ui
FORMS += base-test-window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += icons.qrc
