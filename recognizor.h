#ifndef RECOGNIZOR_H
#define RECOGNIZOR_H
#include <QObject>
#include "gesture_modeling/gesture.h"
#include "dataprocessor.h"
#include <gesturelib.h>
#include "imu/movement.h"
#include "ralsensor/ralsensor.h"
#include "windows/camerawindow.h"
#include "robot/mobilearm.h"
#include<iostream>
using namespace std;
#include <string>

#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override something,
//but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <sapi.h>

class Recognizor: public QObject
{
    Q_OBJECT;

private:
    int datacount,lasthead,startpoint;
    double lastangles[JOINTNUM];

    DataProcessor dataprocessor;

    double zeros[JOINTNUM],thresholds[JOINTNUM],motionRanges[JOINTNUM];
    QList<QList<float> > quatRaw;
    QList<QList<float> > accel;

    double deltas[BUFFERLEN][JOINTNUM];
    MovementType states[BUFFERLEN][JOINTNUM];
    double lastp[JOINTNUM][MOVEMENTNUM],newp[JOINTNUM][MOVEMENTNUM];

    GestureLib gesturelib;
    QString currentGesture;

    // Timer
    QTimer timer;
    bool fileMode;
    bool IMUconnected,robotConnected,grasptest;
	double oldAngle[6]; //记录之前的关节角
	double Angle[6]; //记录之前的关节角
public:
    Recognizor();
    QString getCurrentGesture();
    RalSensor ralsensor;

    // Robot
    MobileArm robot;

    // camera window
    CameraWindow *cwin;
    int setCameraWindow(CameraWindow *c);

    // file functions
    int saveData(const QString &filename);
    int loadFile(QString fileName);

    // reset, clear data
    int reset();

    //sensor functions
    int connectIMU(int interval);
    int disconnectIMU();
    bool isIMUConnected();

    // member variable functions
    DataProcessor &getDataprocessor();
    GestureLib &getGesturelib();

    // replay functions
    int initReplay(QString fileName);
    int setReplayProcess(int pos);

    // realtime recognition function
    int initRealtimeRecognition();

    // timer update function
    int timerbegin(int interval);
    int timerstop();

    // recognition function
    int gestureRecognition(const float angles[JOINTNUM], const float axes[AXISNUM][3]);

    // robot functions
    int connectRobot();
    int disconnectRobot();
    void enableGraspTest();
    void disableGraspTest();

    //int voiceOutPut(std::string voice);
    //LPCWSTR stringToLPCWSTR(std::string orig);


signals:
	void newaccel(float *accel,int datacount);
    void newIMUData(float *angles,int datacount);
    void newGesture(QString gesture);
    void changeToGrasp();

public slots:
    int update();

};

#endif // RECOGNIZOR_H
