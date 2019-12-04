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

//number of sensors
#define SENSORNUM 3
#define ACCELNUM 3




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
    TSS_Device_Id  upperArm,foreArm,body,wristHand;
    QTimer *timer;
    float fquat[7],uquat[7],bquat[7],aquat[7],accel[3];
    MyQuaternion farm,uarm,uarm0,farm0,wrist,wrist0,qbody;
    QString fileName;
    qint64 IMUfilePos,EMGfilePos;

    float twist;
    float direction;
    MyQuaternion x,y,z;
    double zeros[JOINTNUM];

    QFile IMUinfile,EMGinfile;
    QTextStream IMUtextinput,EMGtextinput;

    explicit DataProcessor(QObject *parent = 0);
    ~DataProcessor();

    // IMU functions
    void connectIMU(int interval);
    void disconnectIMU();

    int getIMUData(float *angles, float axes[][3], float *quatRaw,float*accel);
    int getIMUDataFromFile(float *angles, float axes[AXISNUM][3], float *quatRaw,float*accel);
    int getOrientation(float *vector,float *forward,float *right,float *up);

    int process(float *angles, float axes[][3],float*accel);
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

    // File functions
    bool IMUfileExists,EMGfileExists;
    int resetFileStream(QString fname);
    int getFileLineNum();
    int setFilePos(int newpos);
};

#endif // DATAPROCESSOR_H
