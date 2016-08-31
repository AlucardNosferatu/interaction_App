#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <QLabel>
#include "gesture_modeling/gesture.h"
#include "dataprocessor.h"
#include "cyclequeue.h"

#define BUFFERLEN 15000

MovementType movementDetectionNew(int datacount,CycleQueue *states, double delta, float threshold);
float movementDetection(CycleQueue *states, QLabel* label, double delta, float threshold);
bool getmProbability(int head, int datacount, double newp[JOINTNUM][MOVEMENTNUM], double lastp[JOINTNUM][MOVEMENTNUM], const double deltas[][JOINTNUM],
                     MovementType states[BUFFERLEN][JOINTNUM]);
bool setParameters(double t[JOINTNUM], double r[JOINTNUM]);

#endif // MOVEMENT_H
