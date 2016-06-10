#include "initial.h"


void re_initial(float x[N_FRENQUENCY][N_CHANNEL])
{
    float s1 = 0;
    float s = 0;
    float smav[N_CHANNEL];
    for (int i=1;i<N_FRENQUENCY;i++)
    {
        for (int j=0;j<N_CHANNEL;j++)
        {
            s1 = s1+x[i][j]-x[i-1][j];
            smav[j] = smav[j]+fabs(x[i][j]);
        }
        s = s+s1*s1;
    }
    for (int j=0;j<N_CHANNEL;j++)
    {
        mav0[j] = smav[j]/(N_FRENQUENCY-1);
    }
    threshold = 2*s/(N_FRENQUENCY-1);
}
