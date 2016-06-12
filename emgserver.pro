#-------------------------------------------------
#
# Project created by QtCreator 2016-05-21T09:31:12
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = emgserver
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parser.cpp \
    plot/qcustomplot.cpp \
    filter.cpp \
    initial.cpp \
    neupr.cpp \
    recognize.cpp

HEADERS  += mainwindow.h \
    parser.h \
    plot/qcustomplot.h \
    filter.h \
    initial.h \
    neupr.h \
    recognize.h

FORMS    += mainwindow.ui
