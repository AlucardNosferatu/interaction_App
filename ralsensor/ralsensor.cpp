#include "ralsensor.h"

RalSensor::RalSensor()
{

}

int RalSensor::setAndOpenSerialPort(QString portname)
{
    serialport.setPortName(portname);
    serialport.setBaudRate(921600);
    serialport.setDataBits(QSerialPort::Data8);
    serialport.setStopBits(QSerialPort::OneStop);
    serialport.setParity(QSerialPort::NoParity);
    serialport.setFlowControl(QSerialPort::NoFlowControl);
    connect(&serialport,SIGNAL(readyRead()),SLOT(handleReadyRead()));

    imucount=0;
    emgcount=0;
    if (serialport.open(QIODevice::ReadWrite))
        return 0;
    else
        return -1;
}

void RalSensor::closeSerialPort()
{
    serialport.close();
}

int RalSensor::setNormalMeasurement()
{
    const unsigned char normalcommand[4] = {0xff,0x01,0x06,0x06};
    if (!serialport.isOpen())
        return -1;
    serialport.write((char*)normalcommand,4);
    return 0;
}

int RalSensor::setSquareWaveTest()
{
    const unsigned char squarecommand[4] = {0xff,0x01,0x05,0x05};
    if (!serialport.isOpen())
        return -1;
    serialport.write((char*)squarecommand,4);
    return 0;
}

int RalSensor::setNoiseTest()
{
    unsigned char noisecommand[4] = {0xff,0x01,0x04,0x04};
    if (!serialport.isOpen())
        return -1;
    serialport.write((char*)noisecommand,4);
    return 0;
}

int RalSensor::startMeasurement()
{
    static unsigned char begin[4]={0xff,0x01,0x10,0x10};
    static unsigned char IOset[6]={0xff,0x03,0x40,0x00,0x01,0x00};
    if (!serialport.isOpen())
        return -1;
//    for (unsigned char i=0x05;i<=0x0c;i++)
//    {
//        IOset[3]=i;
//        IOset[5]=i+0x01+0x40;
//        serialport.write((char*)IOset,6);
//    }
    serialport.write((char*)begin,4);
    return 0;
}

int RalSensor::stopMeasurement()
{
    static unsigned char stop[4]={0xff,0x01,0x11,0x11};
    if (!serialport.isOpen())
        return -1;
    serialport.write((char*)stop,4);
    return 0;
}

void RalSensor::resetSensor()
{
    static unsigned char reset[4]={0xff,0x01,0x80,0x80};

    if (!serialport.isOpen())
        return;
    serialport.write((char*)reset,4);
}

int RalSensor::readRegister(int addr)
{
    bool ok;
    unsigned char rrcommand[5]={0xff,0x02,0x20,0x00,0x20};

    rrcommand[3]=addr;
    rrcommand[4]=0x20+addr;

    if (!serialport.isOpen())
        return -1;

    serialport.write((char*)rrcommand,5);
    return 0;
}

int RalSensor::getLatestIMUData(float *data)
{
    for (int i=0;i<4;i++)
        data[i]=imudata[i];
    return 0;
}

int RalSensor::getLatestEMGData(float *rawdata, float *data)
{
    for (int i=0;i<8;i++)
    {
        rawdata[i]=rawemg[i];
        data[i]=emgdata[i];
    }
    return 0;
}

void RalSensor::handleReadyRead()
{
    static float emg[8];
    int res;
    int gesture = 0;
    m_readData.clear();
    m_readData.append(serialport.readAll());

    for (int i=0;i<m_readData.length();i++)
    {
        res=parser.parse((unsigned char)m_readData.at(i));
        if (res==NEWIMUDATA)
        {
            imucount++;
            float quat[12];
            parser.getLatestIMUData(imudata);
        }
        if (res==NEWEMGDATA)
        {
            parser.getLatestEMGData(rawemg);
            for (int j=0;j<8;j++)
            {
                emgdata[j]=filter.iir_notch(rawemg[j],j);
                emgdata[j]=filter.fir_highpass(rawemg[j],j);
            }
            emgcount++;
        }
    }
}

void RalSensor::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
}
