QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/../../Lib/
DEPENDPATH += $$PWD/../../Lib/
LIBS += -L$$OUT_PWD/../../Lib/debug -lLib

SOURCES +=  tst_complexgraphtest.cpp
