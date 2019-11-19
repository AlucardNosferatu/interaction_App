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
        plots[i]->yAxis->setRange(0,MAXMAGNITUDE);
        plots[i]->legend->setVisible(true);
    }

    connect(&updatetimer,SIGNAL(timeout()),this,SLOT(updateUI()));
    connect(&recognizor,SIGNAL(newIMUData(float*,int)),this,SLOT(addDatatoIMUPlots(float*,int)));
	connect(&recognizor,SIGNAL(newaccel(float*,int)),this,SLOT(addDatatoaccelPlots(float*,int)));
    connect(&recognizor,SIGNAL(newGesture(QString)),this,SLOT(showGesture(QString)));

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
	//accelPlot
	ui->accelPlot->addGraph();
    ui->accelPlot->addGraph();
    ui->accelPlot->addGraph();
    ui->accelPlot->graph(0)->setName(QString("accel_x"));
    ui->accelPlot->graph(1)->setName(QString("accel_y"));
    ui->accelPlot->graph(2)->setName(QString("accel_z"));
    ui->accelPlot->graph(1)->setPen((QPen(Qt::red)));
    ui->accelPlot->graph(2)->setPen(QPen(Qt::black));
    ui->accelPlot->xAxis->setRange(0,100);
    ui->accelPlot->legend->setVisible(true);
    ui->accelPlot->rescaleAxes(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI()
{
    //ui->emgNumber->display(emgcount);
    //ui->countNumber->display(imucount);
    ui->elbowPlot->rescaleAxes();
    ui->shoulderPlot->rescaleAxes();
    ui->accelPlot->rescaleAxes();
    ui->elbowPlot->replot();
    ui->shoulderPlot->replot();
    ui->accelPlot->replot();
    for (int i=0;i<8;i++)
    {
        plots[i]->xAxis->rescale();
        plots[i]->replot();
    }

    if (isplaying)
        ui->lengthLabel->setText(QString("%1/%2").arg(ui->Slider->value()).arg(fileLength));
}

/////////////////////////////////////////////////////////////////////////
// Add data to plot


void MainWindow::addDatatoaccelPlots(float *accel, int n_datacount)
{
    // add data to plots
    // maximal NO. of data points is 100
    ui->accelPlot->graph(0)->addData(n_datacount,accel[0]);
    ui->accelPlot->graph(1)->addData(n_datacount,accel[1]);
    ui->accelPlot->graph(2)->addData(n_datacount,accel[2]);
    if (n_datacount>ui->Slider->value())
            ui->Slider->setValue(n_datacount);
	  if(n_datacount>=100)
    {
		 ui->accelPlot->graph(0)->removeData(n_datacount-100);
        ui->accelPlot->graph(1)->removeData(n_datacount-100);
        ui->accelPlot->graph(2)->removeData(n_datacount-100);
		 
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

///////////////////////////////////////////////////////////////////////////////////
// Buttons and Slider slots

void MainWindow::on_onIMUButton_clicked()
{
    std:cout << "";
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
        ui->Slider->setValue(0);
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

    isplaying=true;
    recognizor.timerbegin(40);
    updatetimer.start(100);
}

void MainWindow::on_editorButton_clicked()
{
    gwin->show();
}

void MainWindow::on_pauseButton_clicked()
{
    recognizor.timerstop();
    //updatetimer.stop();
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
    recognizor.reset();
    cwin->clearTemp();
    for (int i=0;i<8;i++)
    {
        plots[i]->graph(0)->clearData();
        plots[i]->replot();
    }

    ui->shoulderPlot->graph(0)->clearData();
    ui->shoulderPlot->graph(1)->clearData();
    ui->shoulderPlot->graph(2)->clearData();
	 ui->accelPlot->graph(0)->clearData();
    ui->accelPlot->graph(1)->clearData();
    ui->accelPlot->graph(2)->clearData();
    ui->elbowPlot->graph(0)->clearData();
    ui->elbowPlot->graph(1)->clearData();
    ui->shoulderPlot->replot();
	ui->accelPlot->replot();
    ui->elbowPlot->replot();

    ui->statusBar->showMessage(QString("Raw data list cleared."));
}

void MainWindow::on_initButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    bool ok;
    unsigned char addr = ui->lineEditAddr->text().toInt(&ok,16);
    printf("%x\n",addr);
}

////////////////////////////////////////////////////////////////////////////////
// gesture response slots

void MainWindow::showGesture(QString gesture)
{
    ui->statusBar->showMessage(gesture,1500);
    ui->gestureLabel->setText(gesture);
}

void MainWindow::on_pushButton_clicked()
{
    cawin->show();
}

void MainWindow::on_onRobotButton_clicked()
{
    if (ui->onRobotButton->text()=="Connect Robot")
    {
        recognizor.robot.openSerial(QString("COM7"));
        recognizor.robot.initPosition();
        ui->onRobotButton->setText(QString("Disconnect"));
        recognizor.connectRobot();
    }else
    {
        recognizor.robot.closeSerial();
        ui->onRobotButton->setText(QString("Connect Robot"));
        recognizor.disconnectRobot();
    }
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if (checked)
        recognizor.disableGraspTest();
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if (checked)
        recognizor.enableGraspTest();
}

void MainWindow::on_play3XButton_clicked()
{
    isplaying=true;
    recognizor.timerbegin(14);
    updatetimer.start(50);
}

void MainWindow::on_stepButton_clicked()
{
    recognizor.update();
}

void MainWindow::checkRadioButton()
{
    ui->radioButton_2->setChecked(true);
    ui->radioButton->setChecked(false);
}
