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
    windows/calibrationwindow.cpp \
    windows/camerawindow.cpp \
    windows/gestureeditor.cpp \
    windows/mainwindow.cpp \
    recognizor.cpp \
    gesturelib.cpp \
    dataprocessor.cpp \
    robot/mobilearm.cpp \
    emgserver/Filter.cpp \
    emgserver/utils.cpp \
    emgserver/ads1298decoder.cpp \
    emgserver/Tensor.cpp \
    emgserver/Matrix.cpp \
    emgserver/tinyxml/tinystr.cpp \
    emgserver/tinyxml/tinyxml.cpp \
    emgserver/tinyxml/tinyxmlerror.cpp \
    emgserver/tinyxml/tinyxmlparser.cpp \
    emgserver/iirfilter.cpp \

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
    windows/calibrationwindow.h \
    windows/camerawindow.h \
    windows/gestureeditor.h \
    windows/mainwindow.h \
    recognizor.h \
    gesturelib.h \
    dataprocessor.h \
    yei/yei_threespace_api.h \
    robot/mobilearm.h \
    emgserver/Filter.hpp \
    emgserver/utils.hpp \
    emgserver/ads1298decoder.h \
    emgserver/Tensor.hpp \
    emgserver/Matrix.hpp \
    emgserver/sEMG.hpp \
    emgserver/tinyxml/tinystr.h \
    emgserver/tinyxml/tinyxml.h \
    emgserver/iirfilter.h \

win32: LIBS += -L$$PWD/yei/ -lThreeSpace_API
INCLUDEPATH += $$PWD/yei
DEPENDPATH += $$PWD/yei

FORMS    += windows/mainwindow.ui \
    windows/calibrationwindow.ui \
    windows/camerawindow.ui \
    windows/gestureeditor.ui \
