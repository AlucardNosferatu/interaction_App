#include "filter.h"

Filter::Filter()
{

}

void Filter::reset()
{
    for (int i=0;i<8;i++)
    {
        w1[i]=0;
        w1_1[i]=0;
        w1_2[i]=0;
        for (int j=0;j<47;j++)
            w[i][j]=0;
        startindex[i]=0;
    }
}

float Filter::iir_notch(float x, int channel)
{
    float y=0;
    w1[channel] = x + 0.6102283041329*w1_1[channel] - 0.9747402739684*w1_2[channel];
    y= 0.9873701369842*w1[channel] - 0.6102283041329*w1_1[channel] + 0.9873701369842*w1_2[channel];
    w1_2[channel] = w1_1[channel];
    w1_1[channel] = w1[channel];
    return y;
}

float Filter::fir_highpass(float x, int channel)
{
    static float dv0[47]={
        -0.00943574891549, 0.007891804167995,  0.00632720993849, 0.004812114448026,
        0.002448157351737,-0.001078852188755,-0.005317383434893,-0.009164264704071,
        -0.01121582103833, -0.01018546578584,-0.005377632510712,  0.00287791966969,
          0.0130393577401,  0.02250223950841,  0.02805210790667,  0.02656412128635,
          0.0158130592237,-0.004832673742219,  -0.0340251804898, -0.06846761377065,
         -0.1034015571177,  -0.1334789241973,  -0.1538189912333,   0.8389922050215,
         -0.1538189912333,  -0.1334789241973,  -0.1034015571177, -0.06846761377065,
         -0.0340251804898,-0.004832673742219,   0.0158130592237,  0.02656412128635,
         0.02805210790667,  0.02250223950841,   0.0130393577401,  0.00287791966969,
       -0.005377632510712, -0.01018546578584, -0.01121582103833,-0.009164264704071,
       -0.005317383434893,-0.001078852188755, 0.002448157351737, 0.004812114448026,
         0.00632720993849, 0.007891804167995, -0.00943574891549
     };
    float y=0;
    //static int startindex[8] = 0;
    for (int k = 0; k < 47; k++) {
        y += dv0[k] * w[channel][k];
        if (k!=46)
            w[channel][k]=w[channel][k+1];
    }
    w[channel][46]=x;
    return y;
}
