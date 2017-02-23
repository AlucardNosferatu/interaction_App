#include "ralsensor.h"

RalSensor::RalSensor()
{

}

int RalSensor::setAndOpenSerialPort(QString portname)
{
    qDebug()<<portname;
    serialport.setPortName(portname);
    serialport.setBaudRate(115200);
    serialport.setDataBits(QSerialPort::Data8);
    serialport.setStopBits(QSerialPort::OneStop);
    serialport.setParity(QSerialPort::NoParity);
    serialport.setFlowControl(QSerialPort::NoFlowControl);
    connect(&serialport,SIGNAL(readyRead()),SLOT(handleReadyRead()));
    connect(&serialport,SIGNAL(bytesWritten(qint64)),SLOT(handleBytesWritten(qint64)));
    if (serialport.isOpen())
    {
        qDebug()<<"already open";
        serialport.close();
    }

    emgcount=0;
    if (serialport.open(QIODevice::ReadWrite))
        return 0;
    else
        return -1;
}

int RalSensor::openSerialPort()
{
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
    static float ahp[1]={1.0f};
    static float bhp[5]={0.0627402311,-0.2499714735,0.3744644353,-0.24997147355,0.062740231119};
    static float anotch[7]={1.000000000000000,-1.699163423921474,3.464263380095651,-3.035006841250400,
                         2.930889612822229,-1.213689963509197,0.604109699507278};
    static float bnotch[7]={0.777337677403281,-1.441206975301750,3.222510786578553,-3.065671614896859,
                         3.222258852356618,-1.440981638482467,0.777155376086710};
    if (!serialport.isOpen())
        return -1;

    // initial filter
    for (int i=0;i<ELECTRODENUM;i++)
    {
        emgMAV[i]=0;
        hpfilters[i].initFilter(ahp,bhp,1,5);
        notchfilters[i].initFilter(anotch,bnotch,7,7);
    }
    //qDebug()<<"filter ok";
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

int RalSensor::getLatestEMGData(float *rawdata)
{
    for (int i=0;i<ELECTRODENUM;i++)
    {
        rawdata[i]=emgMAV[i]/emgdataBuffer[i].length();
        if (rawdata[i]>MAXMAGNITUDE)
            rawdata[i]=MAXMAGNITUDE;
    }
    return 0;
}

int RalSensor::clearRawDataBuffer()
{
    for (int i=0;i<ELECTRODENUM;i++)
    {
        emgdataBuffer[i].clear();
        rawemgBuffer[i].clear();
    }

    return 0;
}

int RalSensor::saveRawData(const QString &filename)
{
    QString fname=QString("%1.rawemg").arg(filename);
    QFile f(fname);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        printf("Open failed.");
        return -1;
    }
    QTextStream txtOutput1(&f);
    for (int i=0;i<rawemgBuffer[0].length();i++)
    {
        for (int j=0;j<ELECTRODENUM;j++)
            txtOutput1<<rawemgBuffer[j][i]<<' ';
        txtOutput1<<endl;
    }
    f.close();
    return 0;
}

int RalSensor::triggerFeedback(int type)
{
    unsigned char fbcommand[4]={0xff,0x01,0x25,0x25};
    fbcommand[2]+=type;
    fbcommand[3]+=type;

    if (!serialport.isOpen())
        return -1;

    serialport.write((char*)fbcommand,4);
    return 0;
}

void RalSensor::handleReadyRead()
{
    int res;
    int gesture = 0;
    m_readData.clear();
    m_readData.append(serialport.readAll());

    for (int i=0;i<m_readData.length();i++)
    {
        res=parser.parse((unsigned char)m_readData.at(i));
        if (res==NEWEMGDATA)
        {
            parser.getLatestEMGData(rawemg);
            for (int j=0;j<ELECTRODENUM;j++)
                rawemgBuffer[j].append(rawemg[j]);
            emgcount++;
            handleNewEMGData(rawemg);
        }
        if (res==NEWCOMMANDRES)
        {
            emit newCommandResponse(parser.getLatestCommand());
        }
    }
}

void RalSensor::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
}

void RalSensor::handleNewEMGData(float emg[])
{
    for (int i=0;i<ELECTRODENUM;i++)
    {
        emg[i]=notchfilters[i].filter(emg[i]);
        emg[i]=hpfilters[i].filter(emg[i]);
        if (emg[i]<0)
            emg[i]=-emg[i];
        emgdataBuffer[i].push_front(emg[i]);
        emgMAV[i]+=emg[i];
        if (emgdataBuffer[i].length()>MAVLENGTH)
        {
            emgMAV[i]-=emgdataBuffer[i].last();
            emgdataBuffer[i].pop_back();
        }
    }
}
