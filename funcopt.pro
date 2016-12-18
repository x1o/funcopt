#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T13:33:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 warn_on

TEMPLATE = app

INCLUDEPATH += include gtest/include gtest

SOURCES += gtest/src/gtest-all.cc\
    tests/funcopt_unittest.cc\
    src/Point.cc\
    src/ScalarField.cc\
    src/Domain.cc \
    src/StopIterCriterion.cc \
    src/StopIterCriteria.cc \
    src/MaxIterCriterion.cc \
    src/RandomSearchBernoulli.cc \
    src/Function.cc \
    src/DirectionFunction.cc \
    src/ConjugateGradient.cc\
    src/ValDiffCriterion.cc \
    src/MainWindow.cc \
    src/ContourPlotRenderWidget.cc \
    src/GuiConfiguration.cc

HEADERS  +=\
    include/Point.h\
    include/ScalarField.h\
    include/IterResult.h\
    include/StopIterCriterion.h\
    include/StopIterCriteria.h\
    include/MaxIterCriterion.h\
    include/ValDiffCriterion.h\
    include/scalar_fields.h\
    include/RandomSearchBernoulli.h\
    include/OptMethods.h\
    include/Function.h\
    include/DirectionFunction.h\
    include/ConjugateGradient.h\
    include/Domain.h \
    include/MainWindow.h \
    include/ContourPlotRenderWidget.h \
    include/GuiConfiguration.h

FORMS    += \
    ui/MainWindow.ui

CFG_CLI {
    SOURCES += src/funcopt_cli.cc
    TARGET = funcopt_cli
}

CFG_GUI {
    SOURCES += src/main.cc
    TARGET = funcopt_gui
}
