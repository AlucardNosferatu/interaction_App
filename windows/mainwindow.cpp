#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recognizor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    isplaying=false;
    ui->setupUi(this);

    plots[0]=ui->c1Plot;
    plots[1]=ui->c2Plot;
    plots[2]=ui->c3Plot;
    plots[3]=ui->c4Plot;
    plots[4]=ui->c5Plot;
    plots[5]=ui->c6Plot;
    plots[6]=ui->c7Plot;
    plots[7]=ui->c8Plot;

    for (int i=0;i<8;i++)
    {
        plots[i]->addGraph();
        plots[i]->graph(0)->setName(QString("channel %1").arg(i+1));
        plots[i]->xAxis->setRange(0,100);
        plots[i]->yAxis->setRange(0,0.0005);
        plots[i]->legend->setVisible(true);
    }

    connect(&updatetimer,SIGNAL(timeout()),this,SLOT(updateUI()));
    connect(&recognizor,SIGNAL(newEMGData(float*,int)),this,SLOT(addDatatoEMGPlots(float*,int)));
    connect(&recognizor,SIGNAL(newIMUData(float*,int)),this,SLOT(addDatatoIMUPlots(float*,int)));
    connect(&(recognizor.ralsensor),SIGNAL(newCommandResponse(unsigned char)),this,SLOT(responseReceived(unsigned char)));

    cwin=new CameraWindow(this);
    cwin->move(100,300);
    cwin->show();
    gwin=new GestureEditor(this,recognizor.getGesturelib());
    cawin=new CalibrationWindow(this,recognizor.getDataprocessor());
    cawin->move(1400,300);
    recognizor.setCameraWindow(cwin);
    //cawin->show();

    //elbow plot
    ui->elbowPlot->addGraph();
    ui->elbowPlot->addGraph();
    ui->elbowPlot->graph(0)->setName(QString("epsilon"));
    ui->elbowPlot->graph(1)->setName(QString("tau"));
    ui->elbowPlot->graph(1)->setPen(QPen(Qt::red));
    ui->elbowPlot->legend->setVisible(true);
    ui->elbowPlot->xAxis->setRange(0,100);
    ui->elbowPlot->rescaleAxes(true);

    //shoulder plot
    ui->shoulderPlot->addGraph();
    ui->shoulderPlot->addGraph();
    ui->shoulderPlot->addGraph();
    ui->shoulderPlot->graph(0)->setName(QString("theta"));
    ui->shoulderPlot->graph(1)->setName(QString("phi"));
    ui->shoulderPlot->graph(2)->setName(QString("omega"));
    ui->shoulderPlot->graph(1)->setPen((QPen(Qt::red)));
    ui->shoulderPlot->graph(2)->setPen(QPen(Qt::black));
    ui->shoulderPlot->xAxis->setRange(0,100);
    ui->shoulderPlot->legend->setVisible(true);
    ui->shoulderPlot->rescaleAxes(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI()
{
    ui->emgNumber->display(emgcount);
    ui->countNumber->display(imucount);

    ui->elbowPlot->rescaleAxes();
    ui->shoulderPlot->rescaleAxes();
    ui->elbowPlot->replot();
    ui->shoulderPlot->replot();

    for (int i=0;i<8;i++)
    {
        plots[i]->xAxis->rescale();
        plots[i]->replot();
    }

    if (isplaying)
        ui->lengthLabel->setText(QString("%1/%2").arg(ui->Slider->value()).arg(fileLength));
}

void MainWindow::on_freshButton_clicked()
{
    serialport.close();
    QList<QSerialPortInfo> ports=portinfo.availablePorts();
    ui->portBox->clear();
    for (int i=0;i<ports.length();i++)
    {
        ui->portBox->addItem(ports.at(i).portName());
    }
}

void MainWindow::on_onEMGButton_clicked()
{
    // Connect to RALSensor (Serial Port)
    if (!recognizor.isEMGConnected())
    {
        if (ui->portBox->currentText().isEmpty())
            return;
        if (!recognizor.connectEMGSensor(ui->portBox->currentText()))
        {
            ui->statusBar->showMessage(QString("Series port opened"));
            ui->onEMGButton->setText(QString("Dis EMG"));
        }
        else
            ui->statusBar->showMessage(QString("Failed to open series port"));
    }else
    {
        recognizor.disconnectEMGSensor();
        ui->onEMGButton->setText(QString("Connect EMG"));
    }
}


void MainWindow::on_beginButton_clicked()
{
    isplaying=false;
    recognizor.initRealtimeRecognition();
    recognizor.ralsensor.startMeasurement();
    recognizor.timerbegin();

    if (!updatetimer.isActive())
        updatetimer.start(100);
}

void MainWindow::on_stopButton_clicked()
{
    recognizor.ralsensor.stopMeasurement();
    recognizor.timerstop();
    if (updatetimer.isActive())
        updatetimer.stop();
}

void MainWindow::on_ResetButton_clicked()
{
    recognizor.ralsensor.resetSensor();
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         QString("保存数据"),
         "",
         QString("数据文件 (*)"));
    if (!fileName.isNull())
    {
        int retval=recognizor.saveData(fileName);
        if (retval>=0)
            ui->statusBar->showMessage(QString("data saved."));
    }

    else
    {
     //点的是取消
    }
     return;
}

void MainWindow::on_clearButton_clicked()
{
    emgcount=0;
    for (int i=0;i<8;i++)
    {
        plots[i]->graph(0)->clearData();
        plots[i]->replot();
    }

    ui->shoulderPlot->graph(0)->clearData();
    ui->shoulderPlot->graph(1)->clearData();
    ui->shoulderPlot->graph(2)->clearData();
    ui->elbowPlot->graph(0)->clearData();
    ui->elbowPlot->graph(1)->clearData();
    ui->shoulderPlot->replot();
    ui->elbowPlot->replot();

    ui->statusBar->showMessage(QString("Raw data list cleared."));
}

void MainWindow::on_initButton_clicked()
{

}

void MainWindow::on_pushButtonRLD_clicked()
{
    unsigned char rldcommand[6] = {0xff,0x03,0x03,0x00,0x00,0x00};
    unsigned char rldp = 0x00,rldn=0x00;
//    if (ui->checkBox1P->isChecked()) rldp |= 0x01;
//    if (ui->checkBox2P->isChecked()) rldp |= 0x02;
//    if (ui->checkBox3P->isChecked()) rldp |= 0x04;
//    if (ui->checkBox4P->isChecked()) rldp = rldp | 0x08;

//    if (ui->checkBox1N->isChecked()) rldn |= 0x01;
//    if (ui->checkBox2N->isChecked()) rldn |= 0x02;
//    if (ui->checkBox3N->isChecked()) rldn |= 0x04;
//    if (ui->checkBox4N->isChecked()) rldn |= 0x08;

    rldn=0xfe;
    rldp=0xfe;

    if (!serialport.isOpen())
        return;

    rldcommand[3]=rldp;
    rldcommand[4]=rldn;
    rldcommand[5]=rldcommand[3]+rldcommand[4]+rldcommand[2];

    serialport.write((char*)rldcommand,6);
}

void MainWindow::on_pushButton_2_clicked()
{
    bool ok;
    unsigned char addr = ui->lineEditAddr->text().toInt(&ok,16);
    printf("%x\n",addr);
}

void MainWindow::on_noiseButton_clicked()
{
    recognizor.ralsensor.setNoiseTest();
}



void MainWindow::on_normalMeaButton_clicked()
{
    recognizor.ralsensor.setNormalMeasurement();
}

void MainWindow::addDatatoEMGPlots(float *emgdata, int n_datacount)
{
    // add data to plots
    // maximal NO. of data points is 100
    if (isplaying)
    {
        if (n_datacount>ui->Slider->value())
            ui->Slider->setValue(n_datacount);
    }
    for (int i=0;i<ELECTRODENUM;i++)
    {
        plots[i]->graph(0)->addData(n_datacount,emgdata[i]);
        if (n_datacount>=100)
            plots[i]->graph(0)->removeData(n_datacount-100);
    }
}

void MainWindow::addDatatoIMUPlots(float *angles, int n_datacount)
{
    ui->elbowPlot->graph(0)->addData(n_datacount,angles[ELB]);
    ui->elbowPlot->graph(1)->addData(n_datacount,angles[TWI]);
    ui->shoulderPlot->graph(0)->addData(n_datacount,angles[POL]);
    ui->shoulderPlot->graph(1)->addData(n_datacount,angles[AZI]);
    ui->shoulderPlot->graph(2)->addData(n_datacount,angles[OME]);

    if (n_datacount>ui->Slider->value())
        ui->Slider->setValue(n_datacount);
    if(n_datacount>=100)
    {
        ui->elbowPlot->graph(0)->removeData(n_datacount-100);
        ui->elbowPlot->graph(1)->removeData(n_datacount-100);
        ui->shoulderPlot->graph(0)->removeData(n_datacount-100);
        ui->shoulderPlot->graph(1)->removeData(n_datacount-100);
        ui->shoulderPlot->graph(2)->removeData(n_datacount-100);
    }

}

void MainWindow::responseReceived(unsigned char res)
{
    ui->statusBar->showMessage(QString("Response received! res:%1").arg(res));
}

void MainWindow::on_onIMUButton_clicked()
{
    if (!recognizor.isIMUConnected())
    {
        recognizor.connectIMU(40);
        ui->onIMUButton->setText(QString("Dis IMU"));
    }else
    {
        recognizor.disconnectIMU();
        ui->onIMUButton->setText(QString("Connect IMU"));
    }
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,
                "打开",
                "",
                "数据文件 (*.imu *.emg)");
    if (!fileName.isNull())
    {
        fileLength=recognizor.initReplay(fileName);
        ui->Slider->setMaximum(fileLength);
        ui->Slider->setSingleStep(1);
        ui->lengthLabel->setText(QString("Flie Length:%1").arg(fileLength));
    }
}

void MainWindow::on_Slider_sliderReleased()
{
    int startpoint=ui->Slider->value();
    recognizor.setReplayProcess(startpoint);
    ui->lengthLabel->setText(QString("%1/%2").arg(startpoint).arg(fileLength));
}

void MainWindow::on_playButton_clicked()
{
    recognizor.timerbegin();
    updatetimer.start(100);
}

void MainWindow::on_editorButton_clicked()
{
    gwin->show();
}

void MainWindow::on_pauseButton_clicked()
{
    recognizor.timerstop();
    updatetimer.stop();
}

void MainWindow::on_squaretestButton_clicked()
{
    recognizor.ralsensor.setSquareWaveTest();
}
