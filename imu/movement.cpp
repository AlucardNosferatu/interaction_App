#include "movement.h"

double thresholds[JOINTNUM],motionRanges[JOINTNUM];

bool setParameters(double t[JOINTNUM], double r[JOINTNUM])
{
    for (int i=0;i<JOINTNUM;i++)
    {
        thresholds[i]=t[i];
        motionRanges[i]=r[i];
    }
    return true;
}

bool getmProbability(int head,int datacount,double newp[JOINTNUM][MOVEMENTNUM],double lastp[JOINTNUM][MOVEMENTNUM],const double deltas[][JOINTNUM],
                             MovementType states[BUFFERLEN][JOINTNUM])
{
    MovementType state;

    int currentIndex=datacount;
    if (datacount==0)
    {
        for (int i=0;i<JOINTNUM;i++)
        {
            for (int j=0;j<MOVEMENTNUM;j++)
                newp[i][j]=0;
            states[datacount][i]=NM;
        }
    }

    for (int joint=0;joint<JOINTNUM;joint++)
    {
        currentIndex=datacount;
        //case 1 |delta|<thresholds
		if (deltas[currentIndex][joint]>-thresholds[joint] && deltas[currentIndex][joint]<thresholds[joint])
        {
            newp[joint][FM]=lastp[joint][FM]-0.1;
            newp[joint][BM]=lastp[joint][BM]-0.1;
            int sum=0;
            while(1)
            {
                if (deltas[currentIndex % BUFFERLEN][joint]<-thresholds[joint] || deltas[currentIndex % BUFFERLEN][joint]>thresholds[joint])
                    break;
                sum++;
                currentIndex--;
                if (currentIndex<=head)
                    break;
            }
            newp[joint][NM]=lastp[joint][NM]+0.1;
//            if (0.5*sum>newp[joint][NM])
//                newp[joint][NM]=0.5*sum;
        }

        //case 2 delta>threshold
        else if (deltas[currentIndex][joint]>=thresholds[joint])
        {
            newp[joint][NM]=lastp[joint][NM]-0.1;
            newp[joint][BM]=lastp[joint][BM]-0.2;

            double a=0;
            while (1)
            {
                if (deltas[currentIndex % BUFFERLEN][joint]<thresholds[joint])
                    break;
                a+=deltas[currentIndex % BUFFERLEN][joint];
                currentIndex--;
                if (currentIndex<=head)
                    break;
            }
            newp[joint][FM]=lastp[joint][FM]+0.1;
            if (3*a/motionRanges[joint]>newp[joint][FM])
                newp[joint][FM]=3*a/motionRanges[joint];
        }
        //case 3 delta<-threshold
        else if (deltas[currentIndex][joint]<=-thresholds[joint])
        {
            newp[joint][NM]=lastp[joint][NM]-0.1;
            newp[joint][FM]=lastp[joint][FM]-0.2;

            double a=0;
            while (1)
            {
                if (deltas[currentIndex % BUFFERLEN][joint]>-thresholds[joint])
                    break;
                a+=deltas[currentIndex][joint];
                currentIndex--;
                if (currentIndex<=head)
                    break;
            }
            newp[joint][BM]=lastp[joint][BM]+0.1;
            if (-3*a/motionRanges[joint]>newp[joint][BM])
                newp[joint][BM]=-3*a/motionRanges[joint];
        }

        double maxp=0;
        newp[joint][RM]=0;
        for (int move=0;move<MOVEMENTNUM;move++)
        {
            if (newp[joint][move]<0)
                newp[joint][move]=0;
            if (newp[joint][move]>1)
                newp[joint][move]=1;
            if (newp[joint][move]>maxp)
            {
                states[datacount % BUFFERLEN][joint]=(MovementType)move;
                maxp=newp[joint][move];
                state=(MovementType)move;
            }
        }

        // RM probability caculation
        newp[joint][RM]=lastp[joint][RM]-0.1;
        if (newp[joint][RM]<0)
            newp[joint][RM]=0;
        currentIndex=datacount;
        if (state==FM || state==BM)
        {
            int num=0;
            double a=0;
            while (1)
            {
                if ((states[currentIndex % BUFFERLEN][joint]==FM && states[(currentIndex-1) % BUFFERLEN][joint]==BM) ||
                        (states[currentIndex  % BUFFERLEN][joint]==BM && states[(currentIndex-1) % BUFFERLEN][joint]==FM))
                {
                    num++;
                }
                a+=abs(deltas[currentIndex  % BUFFERLEN][joint]);
                currentIndex--;
                if (states[currentIndex % BUFFERLEN][joint]==NM || currentIndex<=head)
                    break;
            }
            a=a/(num+1)+0.1*num;
            if (num>=2 && 3*a/motionRanges[joint]>newp[joint][RM])
                newp[joint][RM]=3*a/motionRanges[joint];
            if (newp[joint][RM]>1)
                newp[joint][RM]=1;
        }
    }
    return true;
}
