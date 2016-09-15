#-------------------------------------------------
#
# Project created by QtCreator 2016-05-21T09:31:12
#
#-------------------------------------------------

QT       += core gui serialport multimedia multimediawidgets

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
    imu/movement.cpp \
    imu/quaternion.cpp \
    ralsensor/ralsensor.cpp \
    windows/calibrationwindow.cpp \
    windows/camerawindow.cpp \
    windows/gestureeditor.cpp \
    windows/mainwindow.cpp \
    recognizor.cpp \
    gesturelib.cpp \
    dataprocessor.cpp \
    ralsensor/ralfilter.cpp \
    ralsensor/ralparser.cpp \
    ralsensor/iirfilter.cpp \


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
    ralsensor/ralsensor.h \
    windows/calibrationwindow.h \
    windows/camerawindow.h \
    windows/gestureeditor.h \
    windows/mainwindow.h \
    recognizor.h \
    gesturelib.h \
    dataprocessor.h \
    yei/yei_threespace_api.h \
    ralsensor/ralfilter.h \
    ralsensor/ralparser.h \
    ralsensor/iirfilter.h \

win32: LIBS += -L$$PWD/yei/ -lThreeSpace_API
INCLUDEPATH += $$PWD/yei
DEPENDPATH += $$PWD/yei

FORMS    += windows/mainwindow.ui \
    windows/calibrationwindow.ui \
    windows/camerawindow.ui \
    windows/gestureeditor.ui \
