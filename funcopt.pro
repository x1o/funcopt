#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T13:33:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 warn_on

TARGET = funcopt_gui
TEMPLATE = app


INCLUDEPATH = include gtest/include gtest


SOURCES += gtest/src/gtest-all.cc\
           src/funcopt_unittest.cc\
           src/main.cc\
           src/Point.cc\
           src/widget.cc

HEADERS  += include/Point.h\
            include/widget.h

FORMS    += ui/widget.ui
