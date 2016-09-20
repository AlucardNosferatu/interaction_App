#ifndef RALSENSOR_H
#define RALSENSOR_H

#include <QSerialPort>
#include "../ralsensor/ralparser.h"
#include "../ralsensor/ralfilter.h"
#include "iirfilter.h"
#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#define ELECTRODENUM 8
#define MAVLENGTH 30
#define MAXMAGNITUDE 0.0005

class RalSensor: public QObject
{
    Q_OBJECT
    /*
     * process of data reading:
     * 1. Receive Signal "ReadyRead" from serialport
     * 2. Call Slot function handleReadyRead() to read data from serial port buffer
     * 3. Call parse() to parse the new data
     * 4. Emit Signal from handleReadyRead() according to the parsing result.
     */

public:
    RalSensor();
    int setAndOpenSerialPort(QString portname);
    void closeSerialPort();
    int setNormalMeasurement();
    int setSquareWaveTest();
    int setNoiseTest();
    int startMeasurement();
    int stopMeasurement();
    void resetSensor();
    int readRegister(int addr);

    int getLatestEMGData(float *rawdata);

    // raw data functions
    int clearRawDataBuffer();
    int saveRawData(const QString &filename);

    // feedback function
    int triggerFeedback(int type);

private:
    QSerialPort serialport;
    RalParser parser;
    qint64 m_bytesWritten;
    qint64 m_bytesRead;
    QByteArray  m_readData;

    IIRFilter notchfilters[8];
    IIRFilter hpfilters[8];

    float rawemg[8];
    int emgcount;

    QList<float> emgdataBuffer[8];
    QList<float> rawemgBuffer[8];
    float emgMAV[8];


    void handleNewEMGData(float emg[8]);

signals:
    void newEMGData();
    void newCommandResponse(unsigned char res);

private slots:
    // serial port functions
    void handleReadyRead();
    void handleBytesWritten(qint64 bytes);
};

#endif // RALSENSOR_H
