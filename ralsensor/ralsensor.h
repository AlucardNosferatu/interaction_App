#ifndef RALSENSOR_H
#define RALSENSOR_H

#include <QSerialPort>

class RalSensor
{
    /*
     * process of data reading:
     * 1. Receive Signal "ReadyRead" from serialport
     * 2. Call Slot function handleReadyRead() to read data from serial port buffer
     * 3. Call parse() to parse the new data
     * 4. Emit Signal from handleReadyRead() according to the parsing result.
     */

public:
    RalSensor();
    void setSerialPort(QString portname);
    void closeSerialPort();
    void setNormalMeasurement();
    void setSquareWaveTest();
    void setNoiseTest();
    int startMeasurement();
    int stopMeasurement();
    void resetSensor();
    int readRegister(int addr);

    int getLatestIMUData(float *data);
    int getLatestEMGData(float *rawdata,float *data);

private:
    QSerialPort serialport;
    Parser parser;
    qint64 m_bytesWritten;
    qint64 m_bytesRead;
    QByteArray  m_readData;
    Filter filter;

    float imudata[4];
    float rawemg[8],emgdata[8];

    // serial port functions
    void handleReadyRead();
    void handleBytesWritten(qint64 bytes);

signals:
    void newIMUData();
    void newEMGData();
    void newCommandResponse();

};

#endif // RALSENSOR_H
