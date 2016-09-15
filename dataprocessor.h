#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include <QTImer>
#include "yei/yei_threespace_api.h"
#include "imu/quaternion.h"
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QCameraInfo>
#include <QFileDialog>
#include "gesture_modeling/gesture.h"
#include "ralsensor/ralsensor.h"

//number of sensors
#define SENSORNUM 3


#define LEFT_DIRECTION        0
#define RIGHT_DIRECTION       1
#define UP_DIRECTION          2
#define DOWN_DIRECTION        3
#define FORWARD_DIRECTION     4
#define BACKWARD_DIRECTION    5
#define OTHERS_DIRECTION      -1

#define ORIENTATION_THRESHOLD 0.72

using namespace std;

class DataProcessor : public QObject
{
    Q_OBJECT
private:
public:
    TSS_Device_Id  upperArm,foreArm,body;
    QTimer *timer;
    float fquat[4],uquat[4],bquat[4];
    MyQuaternion farm,uarm,uarm0,farm0,qbody;
    QString fileName;
    qint64 IMUfilePos,EMGfilePos;

    float twist;
    float direction;
    MyQuaternion x,y,z;
    double zeros[JOINTNUM];

    QFile IMUinfile,EMGinfile;
    QTextStream IMUtextinput,EMGtextinput;

    RalSensor *ralsensor;

    explicit DataProcessor(QObject *parent = 0);
    ~DataProcessor();

    // IMU functions
    void connectIMU(int interval);
    void disconnectIMU();

    int getIMUData(float *angles, float axes[][3], float *quatRaw);
    int getIMUDataFromFile(float *angles, float axes[AXISNUM][3], float *quatRaw);
    int getOrientation(float *vector,float *forward,float *right,float *up);

    int process(float *angles, float axes[][3]);
    int processForCalibration(float *angles);
    int setZeros(double *angles);
    int getZeros(float *angles);
    int setDirection(float d);
    double getPolarAngle(MyQuaternion zu, MyQuaternion xu);
    double getAziAngle(MyQuaternion zu);
    double getOmegaAngle(MyQuaternion uy,double polar,double azi);
    double getElbowAngle(MyQuaternion uz, MyQuaternion fz);
    double getTwistAngle(MyQuaternion ux, MyQuaternion fx, MyQuaternion uz, double elbow);
    float tare();

    // EMG functions
    void setRalSensor(RalSensor *r);
    int connectEMGSensor(QString portname);
    int disconnectEMGSensor();
    int getEMGData(float *emgRaw);
    int getEMGDataFromFile(float *emgRaw);

    // File functions
    bool IMUfileExists,EMGfileExists;
    int resetFileStream(QString fname);
    int getFileLineNum();
    int setFilePos(int newpos);
};

#endif // DATAPROCESSOR_H
