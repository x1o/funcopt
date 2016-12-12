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


INCLUDEPATH += include gtest/include gtest


SOURCES += gtest/src/gtest-all.cc\
           tests/funcopt_unittest.cc\
           src/main.cc\
           src/widget.cc\
           src/Point.cc\
           src/ScalarField.cc\
           src/Domain.cc \
    src/StopIterCriterion.cc \
    src/StopIterCriteria.cc \
    src/MaxIterCriterion.cc \
    src/ValDiffCriterion.cc

HEADERS  += include/widget.h\
            include/Point.h\
            include/ScalarField.h\
            include/IterResult.h\
            include/StopIterCriterion.h\
            include/StopIterCriteria.h\
            include/MaxIterCriterion.h\
            include/ValDiffCriterion.h\
            include/scalar_fields.h\
            include/Domain.h


FORMS    += ui/widget.ui
