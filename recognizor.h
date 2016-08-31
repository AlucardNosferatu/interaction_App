#ifndef RECOGNIZOR_H
#define RECOGNIZOR_H
#include "gesture_modeling/gesture.h"
#include "dataprocessor.h"
#include <gesturelib.h>
#include "movement.h"

class Recognizor
{
private:
    int datacount,lasthead,startpoint;
    double lastangles[JOINTNUM];

    DataProcessor dataprocessor;

    double zeros[JOINTNUM],thresholds[JOINTNUM],motionRanges[JOINTNUM];
    QVector<QVector<double>> quatRaw;
    double deltas[BUFFERLEN][JOINTNUM];
    MovementType states[BUFFERLEN][JOINTNUM];
    double lastp[JOINTNUM][MOVEMENTNUM],newp[JOINTNUM][MOVEMENTNUM];

    GestureLib gesturelib;


    QString currentGesture;

public:
    Recognizor();
    QString getCurrentGesture();
    int gestureRecognition(const double angles[JOINTNUM], const double axes[JOINTNUM][3]);
    int addRawdata();
    int initialRealtimeRecognition();
    int saveData(const QString &filename);
    int loadFile(QString fileName);
    int reset();

    //sensor functions
    int connectSensor(int interval);
    int disconnectSensor();
    DataProcessor &getDataprocessor();
    int initReplay(QString fileName);
    int setReplayProcess(int startpoint);
    int update(bool FileMode, double *angles, double axes[][3]);
    GestureLib &getGesturelib();
};

#endif // RECOGNIZOR_H
