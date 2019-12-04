#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recognizor.h"

static float ahp[1]={
    1.0f
};
static float bhp[5]={
    static_cast<float>(0.0627402311),
    static_cast<float>(-0.2499714735),
    static_cast<float>(0.3744644353),
    static_cast<float>(-0.24997147355),
    static_cast<float>(0.062740231119)
};
static float anotch[7]={
    1.000000000000000,
    static_cast<float>(-1.699163423921474),
    static_cast<float>(3.464263380095651),
    static_cast<float>(-3.035006841250400),
    static_cast<float>(2.930889612822229),
    static_cast<float>(-1.213689963509197),
    static_cast<float>(0.604109699507278)
};
static float bnotch[7]={
    static_cast<float>(0.777337677403281),
    static_cast<float>(-1.441206975301750),
    static_cast<float>(3.222510786578553),
    static_cast<float>(-3.065671614896859),
    static_cast<float>(3.222258852356618),
    static_cast<float>(-1.440981638482467),
    static_cast<float>(0.777155376086710)
};
static float anotch1[3]={
    static_cast<float>(0.990498466402),
    static_cast<float>(-0.6121617180411),
    static_cast<float>(0.990498466402)
};
static float bnotch1[3]={
    1,
    static_cast<float>(-0.6121617180411),
    static_cast<float>(0.980996932804)
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    isplaying=false;
    ui->setupUi(this);

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

void MainWindow::on_beginButton_clicked()
{
    isplaying=false;
    recognizor.initRealtimeRecognition();
    recognizor.timerbegin(40);

    if (!updatetimer.isActive())
        updatetimer.start(100);
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

void MainWindow::on_stopButton_clicked()
{
	recognizor.timerstop();
    if (updatetimer.isActive())
        updatetimer.stop();
}

void MainWindow::on_pushButton_connectWifi_clicked()
{
    QString s = ui->lineEdit_port->text();
    QStringList ports = s.split(";");
    std::cout <<  s.toStdString().data() << std::endl;
    // init for cnn predict===
    row=100;
    col=16;
    count = 0;
    //读取权重-----
    conv1Filter = Filter(32, 1, 3, 1);
    conv1Filter = parseFilterWeight("conv1_weight.xml", 32, 1, 3, 1);
    convbias1 = parseBias("bias1_weight.xml", 32);

    conv2Filter = Filter(64, 32, 3, 1);
    conv2Filter = parseFilterWeight("conv2_weight.xml", 64, 32, 3, 1);
    convbias2 = parseBias("bias2_weight.xml", 64);

    conv3Filter = Filter(128, 64, 3, 1);
    conv3Filter = parseFilterWeight("conv3_weight.xml", 128, 64, 3, 1);
    convbias3 = parseBias("bias3_weight.xml", 128);

    fc1weight = parseFullConnWeight("fullconn1_weight.xml", 5*8*128, 256);
    fullbias1 = parseBias("fullconn1_bias.xml", 256);

    fc2weight = parseFullConnWeight("fullconn2_weight.xml", 256, 10);
    fullbias2 = parseBias("fullconn2_bias.xml", 10);

    bn1_weight = parseBias("bn1_weight.xml", 256);
    bn1_bias = parseBias("bn1_bias.xml", 256);
    bn1_running_mean = parseBias("bn1_running_mean.xml", 256);
    bn1_running_var = parseBias("bn1_running_var.xml", 256);

    p = new double*[row];

    for(int i=0; i<row; i++){
        p[i] = new double[col];
    }

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            p[i][j] = 0.0;
        }
    }

    Ads1298Decoder* ads = new Ads1298Decoder(static_cast<quint16>(ports[0].toUInt()),0,this);//create a pointer pointing to the class Ads1298Decoder
    module.append(ads);
    std::cout << "on_pushButton_connectWifi_clicked" << std::endl;
    connect(module[0],SIGNAL(hasNewDataPacket(int,double*)),this,SLOT(handleHasNewDataPacket(int,double*)));
    connect(module[0],SIGNAL(hasNewCmdReply(char)),this,SLOT(handleHasNewCmdReply(char)));
    connect(module[0],SIGNAL(hasNewWifiConnection(int)),this,SLOT(handleHasNewWifiConnection(int)));

    setCustomPlotPattern();
    refreshIIRFilters();
    refreshDataBuffer();
    plotCounter = timeCounter = 0;    // initialize
    replotTimer.start(100); //10fps
    ui->statusBar->showMessage(tr("Server Open successed"));
}

void MainWindow::setCustomPlotPattern()
{
    plots[0]=ui->c1Plot;
    plots[1]=ui->c2Plot;
    plots[2]=ui->c3Plot;
    plots[3]=ui->c4Plot;
    plots[4]=ui->c5Plot;
    plots[5]=ui->c6Plot;
    plots[6]=ui->c7Plot;
    plots[7]=ui->c8Plot;
    plots[8]=ui->c1Plot_2;
    plots[9]=ui->c2Plot_2;
    plots[10]=ui->c3Plot_2;
    plots[11]=ui->c4Plot_2;
    plots[12]=ui->c5Plot_2;
    plots[13]=ui->c6Plot_2;
    plots[14]=ui->c7Plot_2;
    plots[15]=ui->c8Plot_2;

    for (int i=0;i<16;i++)
    {
        plots[i]->clearGraphs();
        plots[i]->addGraph();
        plots[i]->graph(0)->setPen(QPen(Qt::red));
        plots[i]->graph(0)->setLineStyle(QCPGraph::lsLine);
        plots[i]->legend->setFont(QFont("Helvetica",9));
        plots[i]->legend->setMaximumSize(20,20);
        plots[i]->yAxis->setRange(-0.04,0);
        plots[i]->yAxis->setAutoTicks(true);
        plots[i]->yAxis->setLabel("Voltage(V)");
        plots[i]->xAxis->setRange(0,TIME_SPAN+TIME_BORDER);
        plots[i]->xAxis->setLabel("time(s)");
        plots[i]->replot();
    }
}

void MainWindow::refreshIIRFilters()
{
    int chNum = module.length()*CH_NUM;
    //Every module has 16 channels
    //There are 4 modules in typical instance of experiment
    //There are 4*16=64 channels in total
    //According to the number of modules
    for(int i=0;i<chNum;i++)//for every channel (64)
    {
        IIRFilter* nf_50 = new IIRFilter();
        IIRFilter* nf_100 = new IIRFilter();
        IIRFilter* hp = new IIRFilter();

        hp->initFilter(ahp,bhp,1,5);
        nf_50->initFilter(anotch,bnotch,7,7);
        nf_100->initFilter(anotch1,bnotch1,3,3);

        notchfilters_50.append(nf_50);
        notchfilters_100.append(nf_100);
        hpfilters.append(hp);
    }
}

void MainWindow::refreshDataBuffer()
{
    int chNum = module.length()*CH_NUM;
   //Accroding to chNum to assign the buffer size
    for(int i=0;i<chNum;i++)
    {
        QList<double>* rd = new QList<double>();
        QList<double>* fd = new QList<double>();
        QList<double>* dd = new QList<double>();
        rawData.append(rd);
        filterData.append(fd);
        detrendedData.append(dd);
    }
}
