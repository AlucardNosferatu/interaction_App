#include "parser.h"

Parser::Parser(QObject *parent): QObject(parent)
{
    currentstate=GET_HEAD;
}

int Parser::parse(unsigned char c)
{
    if (currentstate==GET_HEAD && c==0xff)
    {
        currentstate=GET_HEAD2;
        return PARSING;
    }
    if (currentstate==GET_HEAD2 && c==0xff)
    {
        currentstate=GET_TYPE;
        return PARSING;
    }
    if (currentstate==GET_TYPE)
    {
        if (c==0x03)
            type=COMMAND;
        else if (c==0x01)
            type=EMG;
        else if (c==0x02)
            type=IMU;
        else
        {
            currentstate=GET_HEAD;
            return ERROR;
        }
        currentstate=GET_DATA;
        dataindex=0;
        tmpsum=0;
        return PARSING;
    }
    if (currentstate==GET_DATA)
    {
        if (type==COMMAND)
        {
            commandBuffer[dataindex++]=c;
            if (dataindex==1)
                currentstate=GET_SUM;
        }
        else if (type==EMG)
        {
            emgDataBuffer[dataindex++]=c;
            if (dataindex==27)
                currentstate=GET_SUM;
        }
        else if (type==IMU)
        {
            imuDataBuffer[dataindex++]=c;
            if (dataindex==48)
                currentstate=GET_SUM;
        }
        tmpsum+=c;
        return PARSING;
    }
    if (currentstate==GET_SUM)
    {
        ParserResult res;
        currentstate=GET_HEAD;
        if (c==tmpsum)
        {

            if (type==IMU)
                res = NEWIMUDATA;
            else if (type==EMG)
                res = NEWEMGDATA;
            else
                res = NEWCOMMANDRES;
        }
        else
            res = ERROR;
        return res;
    }
}


int Parser::getLatestIMUData(float quat[])
{
    float *floatdata=(float*)(imuDataBuffer);
    for (int i=0;i<12;i++)
        quat[i]=floatdata[i];
    return 0;
}

int Parser::getLatestEMGData(float emgdata[])
{
    for (int i=0;i<8;i++)
    {
        int tmp=0,sig=1;
        if (emgDataBuffer[3+(i*3)]&0x80)
        {
            sig=-1;
            tmp=(emgDataBuffer[3+(i*3)]&0x7f);
        }
        else
            tmp=emgDataBuffer[3+(i*3)];
        for (int j=1;j<3;j++)
            tmp=tmp*256+emgDataBuffer[3+(i*3)+j];
        emgdata[i]=2.4*(sig*(float)tmp/(2<<23));
    }
    return 0;
}

unsigned char Parser::getLatestCommand()
{
    return commandBuffer[0];
}
