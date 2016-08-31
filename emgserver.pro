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
    plot/qcustomplot.cpp \
    gesture_modeling/angleciterion.cpp \
    gesture_modeling/axisciterion.cpp \
    gesture_modeling/gesture.cpp \
    gesture_modeling/movementciterion.cpp \
    imu/cyclequeue.cpp \
    imu/dataprocessor.cpp \
    imu/gesturelib.cpp \
    imu/movement.cpp \
    imu/quaternion.cpp \
    ralsensor/filter.cpp \
    ralsensor/parser.cpp \
    ralsensor/ralsensor.cpp \
    windows/calibrationwindow.cpp \
    windows/camerawindow.cpp \
    windows/gestureeditor.cpp \
    windows/mainwindow.cpp \
    recognizor.cpp


HEADERS  +=     plot/qcustomplot.h \
    gesture_modeling/angleciterion.h \
    gesture_modeling/axisciterion.h \
    gesture_modeling/gesture.h \
    gesture_modeling/movementciterion.h \
    imu/cyclequeue.h \
    imu/dataprocessor.h \
    imu/gesturelib.h \
    imu/movement.h \
    imu/quaternion.h \
    imu/recognizor.h \
    ralsensor/filter.h \
    ralsensor/parser.h \
    ralsensor/ralsensor.h \
    windows/calibrationwindow.h \
    windows/camerawindow.h \
    windows/gestureeditor.h \
    windows/mainwindow.h \
    recognizor.h


FORMS    += windows/mainwindow.ui \
    windows/calibrationwindow.ui \
    windows/camerawindow.ui \
    windows/gestureeditor.ui
