#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "emgserver/Filter.hpp"
#include "emgserver/utils.hpp"
#include "emgserver/ads1298decoder.h"
#include "emgserver/iirfilter.h"

#include "qserialport.h"
#include "qserialportinfo.h"
#include <QTimer>
#include <QList>
#include "plot/qcustomplot.h"
#include "recognizor.h"

#include "camerawindow.h"
#include "gestureeditor.h"
#include "calibrationwindow.h"
#include "dataprocessor.h"


#define TIME_SPAN 5
#define TIME_BORDER 0
#define SAMPLE_Freq 250
#define PlotNum SAMPLE_Freq*TIME_SPAN

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    double **p; //semg data
    int count;
    int row, col;
    Filter conv1Filter;
    Filter conv2Filter;
    Filter conv3Filter;
    vector<double> convbias1;
    vector<double> convbias2;
    vector<double> convbias3;
    Matrix fc1weight;
    Matrix fc2weight;
    vector<double> fullbias1;
    vector<double> fullbias2;
    vector<double> bn1_weight;
    vector<double> bn1_bias;
    vector<double> bn1_running_mean;
    vector<double> bn1_running_var;

private slots:
    void updateUI();
    // serial port list slots
    void on_clearButton_clicked();
    void on_saveButton_clicked();
    void on_pushButton_2_clicked();
    // plot slots
    void addDatatoIMUPlots(float *angles,int n_datacount);
	void addDatatoaccelPlots(float *accel, int n_datacount);
    // gesture response slots
    void showGesture(QString gesture);
    void on_onIMUButton_clicked();
    void on_loadButton_clicked();
    void on_Slider_sliderReleased();
    void on_playButton_clicked();
    void on_editorButton_clicked();
    void on_pauseButton_clicked();
    void on_pushButton_clicked();
    void on_onRobotButton_clicked();
    void on_radioButton_toggled(bool checked);
    void on_radioButton_2_toggled(bool checked);
    void on_play3XButton_clicked();
    void on_stepButton_clicked();
    void on_beginButton_clicked();
    void on_stopButton_clicked();
    void on_pushButton_connectWifi_clicked();
    void handleHasNewDataPacket(int index, double* newDP);
    void handleHasNewCmdReply(char cmdR);
    void handleHasNewWifiConnection(int index);

private:
    Ui::MainWindow *ui;
    QSerialPortInfo portinfo;
    QSerialPort serialport;
    qint64 m_bytesWritten;
    qint64 m_bytesRead;
    QByteArray  m_readData;
    int imucount,emgcount;
    QTimer updatetimer;
    QCustomPlot* plots[16];
    Recognizor recognizor;
    int fileLength,datapoint;
    GestureEditor *gwin;
    CalibrationWindow *cawin;
    CameraWindow *cwin;
    bool isplaying;
    QList<Ads1298Decoder*> module; //the Ads1298Decoder is a QObject,store the QObject and its subclass's pointer
    void setCustomPlotPattern();
    void refreshIIRFilters();
    void refreshDataBuffer();
    string getMotionStr(int num);
    void log(QString &info);
    void updatePlotData();
    double getPlotMax(QQueue<double> &plotData);
    double getPlotMin(QQueue<double> &plotData);
    QList<QList<double>*> rawData;
    QList<QList<double>*> filterData;
    QList<QList<double>*> detrendedData;
    QList<IIRFilter*> notchfilters_50;
    QList<IIRFilter*> notchfilters_100;
    QList<IIRFilter*> hpfilters;
    QTimer replotTimer;
    int timeCounter;
    int plotCounter;
    QQueue<double> filterPlotData;
};

#endif // MAINWINDOW_H
