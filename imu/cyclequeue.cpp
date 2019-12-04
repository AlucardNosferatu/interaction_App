#include "cyclequeue.h"
int cyclePush(CycleQueue *queue,int state,int stime,int etime,float value)
{
    int top;
    top=getTopIndex(queue);
    if(queue->stateCount>0)
        if (!isValidState(queue,top) && state!=NM)
            popTopState(queue);


    queue->stateCount++;
    top=getTopIndex(queue);
    queue->endTime[top]=etime;
    queue->startTime[top]=stime;
    queue->state[top]=state;
    queue->amplitude[top]=value;
    return 0;
}

int sameAsTopState(const CycleQueue &queue, int state)
{
    if (queue.stateCount==0)
        return 0;
    if (state==queue.state[(queue.stateCount-1) % QUEUELEN])
    {
        return 1;
    }
    else
        return 0;
}

int updateTopState(CycleQueue *queue, int etime, float value)
{
    int top=getTopIndex(queue);
    queue->endTime[top]=etime;
    queue->amplitude[top]+=value;
    return 0;
}

int initQueue(CycleQueue *queue)
{
    queue->stateCount=0;
    return 0;
}

int isValidState(CycleQueue *queue, int index)
{
    //for a gesture lasts too short
    if (queue->endTime[index]-queue->startTime[index]<10 && queue->state[index]>900)
        return 0;

    //for a NM lasts too short
    if (((queue->endTime[index])-(queue->startTime[index])<10) && queue->state[index]==NM)
        return 0;

    //for other movements with too small amplitude
    if (queue->state[index]!=NM && queue->state[index]<900)
        if (abs(queue->amplitude[index])<0.3)
            return 0;
    return 1;
}

int getTopIndex(CycleQueue *queue)
{
    int ans=queue->stateCount% QUEUELEN-1;
    if (ans<0)
        return QUEUELEN-1;
    else
        return ans;
}

int popTopState(CycleQueue *queue)
{
    queue->stateCount--;
    return 0;
}
int getTopDuration(CycleQueue *queue)
{
    int index=getTopIndex(queue);
    return queue->endTime[index]-queue->startTime[index];
}

int getCurrentState(CycleQueue *queue, int *state, float *value)
{
    if (!isValidState(queue,getTopIndex(queue)))
        return -1;
    *state=queue->state[getTopIndex(queue)];
    *value=queue->amplitude[getTopIndex(queue)];
    return 0;
}

//获得前驱的下标
int getPreviousIndex(CycleQuele *queue,int index)
{
    int retval;
    if (index==0)
        if (queue->stateCount>1000)
            retval=999;
        else
            retval=-1;
    else
    {
        retval=index-1;
        if (!isValidState(queue,retval))
            return getPreviousIndex(queue,retval);
    }
    return retval;
}

//检测往复运动
int waveDectec(CycleQueue *queue,int *repeattime,float *amplitude,int *duration)
{
    int index=getTopIndex(queue),previous;
    int endtime=queue->endTime[index],starttime;
    *repeattime=0;
    *amplitude=abs(queue->amplitude[index]);
    if (queue->state[index]==NM)
    {
        //STILL, no wave
        return 0;
    }
    previous=getPreviousIndex(queue,index);
    while (previous!=-1)
    {
        int delta=((queue->state[index])+(queue->state[previous]));

        if (delta==3)
        {
            //是反方向的运动
            *repeattime+=1;
            *amplitude+=abs(queue->amplitude[previous]);
            starttime=queue->startTime[previous];
            index=previous;
            previous=getPreviousIndex(queue,index);
        }
        else
            break;
    }
    //计算平均运动幅度
    //*amplitude=*amplitude/(*repeattime);

    //计算持续时间
    *duration=endtime-starttime;
    return 0;
}
