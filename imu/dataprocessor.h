#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include <QTImer>
#include "yei/yei_threespace_api.h"
#include "quaternion.h"
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
public:
    TSS_Device_Id  upperArm,foreArm,body;
    QTimer *timer;
    float fquat[4],uquat[4],bquat[4];
    MyQuaternion farm,uarm,uarm0,farm0,qbody;
    QString fileName;
    qint64 filePos;
    float twist;
    float direction;
    MyQuaternion x,y,z;
    double zeros[JOINTNUM];

    QFile infile;
    QTextStream textinput;

    explicit DataProcessor(QObject *parent = 0);
    ~DataProcessor();
    void initiate(int interval);
    void disconnect();
    int getData(double *angles, double axes[AXISNUM][3], double *quatRaw);
    int getDataFromFile(double *angles, double axes[AXISNUM][3], double *quatRaw);
    int getOrientation(float *vector,float *forward,float *right,float *up);

    int resetFileStream(QString fname);
    int getFileLineNum();
    int setFilePos(int newpos);

    int process(double *angles, double axes[AXISNUM][3]);
    int processForCalibration(double *angles);
    int setZeros(double *angles);
    int getZeros(double *angles);
    int setDirection(float d);
    double getPolarAngle(MyQuaternion zu, MyQuaternion xu);
    double getAziAngle(MyQuaternion zu);
    double getOmegaAngle(MyQuaternion uy,double polar,double azi);
    double getElbowAngle(MyQuaternion uz, MyQuaternion fz);
    double getTwistAngle(MyQuaternion ux, MyQuaternion fx, MyQuaternion uz, double elbow);
    float tare();

};

#endif // DATAPROCESSOR_H
