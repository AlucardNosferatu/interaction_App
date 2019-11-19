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

class Recognizor: public QObject
{
    Q_OBJECT;

private:
    int datacount,lasthead,startpoint;
    double lastangles[JOINTNUM];

    DataProcessor dataprocessor;

    double zeros[JOINTNUM],thresholds[JOINTNUM],motionRanges[JOINTNUM];
    QList<QList<float>> quatRaw;
	QList<QList<float>> accel;
    QList<QList<float>> emgraw;

    double deltas[BUFFERLEN][JOINTNUM];
    MovementType states[BUFFERLEN][JOINTNUM];
    double lastp[JOINTNUM][MOVEMENTNUM],newp[JOINTNUM][MOVEMENTNUM];

    GestureLib gesturelib;
    QString currentGesture;

    // Timer
    QTimer timer;

    bool fileMode;

    bool IMUconnected,EMGconnected,robotConnected,grasptest;

    int ban[ELECTRODENUM];
    float membership[ELECTRODENUM][3];



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

    int connectEMGSensor(QString portname);
    int disconnectEMGSensor();
    bool isEMGConnected();

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
    int gestureRecognition(const float angles[JOINTNUM], const float axes[AXISNUM][3], const float emg[ELECTRODENUM]);

    // robot functions
    int connectRobot();
    int disconnectRobot();
    void enableGraspTest();
    void disableGraspTest();


signals:
    void newEMGData(float *emgdata,int datacount);
	void newaccel(float *accel,int datacount);
    void newIMUData(float *angles,int datacount);
    void newGesture(QString gesture);
    void clearGesture();
    void changeToGrasp();

public slots:
    int update();

};

#endif // RECOGNIZOR_H
