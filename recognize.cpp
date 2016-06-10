#include "initial.h"
#include "recognize.h"
#include "neupr.h"

int gesturerecognize0523(float s[N_CHANNEL])
{
    const int Fs = N_FRENQUENCY;//采样率
    const int n = N_CHANNEL;//通道数
    static int n_a = 0;
    static float y[Fs*n];
    static float sc[Fs/5];
    int kk = 0;
    int xl = Fs;
    int xll = Fs/5;
    int windowSize = Fs/5;
    float sum1 = 0;
    float sum2 = 0;
    float DSMA = 0;
    float mav[n];
    float out[4];
    float abs = 0;
    for (int i = 0; i < xl-1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            y[i*n+j] = y[i*n+j+1];
        }
    }
    for (int j = 0; j < n; j++)
    {
        sum1 = sum1+s[j]-y[(xl-1)*n+j];
        y[(xl-1)*n+j] = s[j];
    }
    for (int j = 0; j < windowSize-1; j++)
    {
        sc[j] = sc[j+1];
    }
    sc[windowSize-1] = sum1*sum1;
    for (int j = 0; j < windowSize; j++)
    {
        DSMA = DSMA+sc[j];
    }
    if(DSMA>threshold) {
        n_a = n_a+1;
        if (n_a>xll) {
            if(n_a>=xl) {
                kk = 5;
                n_a = 0;
            }
            else {
                for(int i = 0;i<n;i++)
                {
                    for(int j = 0;j<xl;j++)
                    {
                        abs = fabs(y[n*(xl-j-1)+i]);
                        sum2 = sum2+abs;
                    }
                    mav[i] = sum2/xl;
                    mav[i] = mav[i]/mav0[i];
                }
                neutest(mav,out);
                if (out[0]>out[1]) {
                    if (out[0]>out[2]){
                        if (out[0]>out[3])
                            kk = 1;
                        else
                            kk = 4;
                    }
                    else {
                        if (out[2]>out[3])
                            kk = 3;
                        else
                            kk = 4;
                    }
                }
                else {
                    if (out[1]>out[2]){
                        if (out[1]>out[3])
                            kk = 2;
                        else
                            kk = 4;
                    }
                    else {
                        if (out[2]>out[3])
                            kk = 3;
                        else
                            kk = 4;
                    }
                }
            }
        }
    }
    else {
            n_a = 0;
            kk = 0;
    }
    return kk;
}

