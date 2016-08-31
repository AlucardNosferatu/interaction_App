#ifndef CYCLEQUEUE
#define CYCLEQUEUE
#include "gesture_modeling/gesture.h"

//#define abs(a) ((a)>0?(a):-(a))
#define QUEUELEN 100


//#define FM 1
//#define BM 2
//#define TWISTPOSITIVE 1
//#define TWISTNEGATIVE 2
//#define NM 0
//#define RM 3

#define GO    999
#define COME  998
#define LEFT  997
#define RIGHT 996

typedef struct CycleQueue
{
    int state[QUEUELEN];
    int startTime[QUEUELEN];
    int endTime[QUEUELEN];
    float amplitude[QUEUELEN];
    int stateCount;
}CycleQuele;

int isValidState(CycleQueue *queue, int index);
int initQueue(CycleQueue *queue);
int updateTopState(CycleQueue *queue,int etime,float value);
int sameAsTopState(const CycleQueue &queue,int state);
int cyclePush(CycleQueue *queue, int state, int stime, int etime, float value);
int popTopState(CycleQueue *queue);
int getTopIndex(CycleQueue *queue);
int getTopDuration(CycleQueue *queue);
int getPreviousIndex(CycleQuele *queue,int index);
int getCurrentState(CycleQueue *queue,int *state,float *value);
int waveDectec(CycleQueue *queue, int *repeattime, float *amplitude, int *duration);


#endif // CYCLEQUEUE

