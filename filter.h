#ifndef FILTER_H
#define FILTER_H


class Filter
{
public:
    Filter();
    float iir_notch(float x, int channel);
    float fir_highpass(float x, int channel);
    void reset();

private:
    float w1_2[8], w1_1[8], w1[8];
    float w[8][47];
    int startindex[8];
};

#endif // FILTER_H
