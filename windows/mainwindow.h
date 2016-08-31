#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qserialport.h"
#include "qserialportinfo.h"
#include "parser.h"
#include <QTimer>
#include <QList>
#include "plot/qcustomplot.h"
#include "filter.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateUI();
    void on_freshButton_clicked();
    void handleReadyRead();
    void handleBytesWritten(qint64 bytes);
    void on_openButton_clicked();
    void on_closeButton_clicked();

    void on_beginButton_clicked();
    void on_stopButton_clicked();
    void response_received(ParserResult r);
    void on_ResetButton_clicked();
    void on_clearButton_clicked();
    void on_saveButton_clicked();
    void on_initButton_clicked();
    void on_pushButtonRLD_clicked();
    void on_pushButton_2_clicked();
    void on_noiseButton_clicked();
    void on_testButton_clicked();
    void on_normalMeaButton_clicked();

private:
    Ui::MainWindow *ui;
    Parser parser;
    QSerialPortInfo portinfo;
    QSerialPort serialport;
    qint64 m_bytesWritten;
    qint64 m_bytesRead;
    QByteArray  m_readData;
    int imucount,emgcount;
    QTimer updatetimer;
    Filter filter;

    QList<float> rawdata[8];
    QList<float> filtered[8];
    QList<QList<float>> quatRaw;

    QCustomPlot* plots[8];

};

#endif // MAINWINDOW_H
