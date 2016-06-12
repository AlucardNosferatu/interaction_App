#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initial.h"
#include "recognize.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->c1Plot->addGraph();
    ui->c1Plot->graph(0)->setName(QString("channel 1"));
    ui->c1Plot->xAxis->setRange(0,1000);
    connect(&updatetimer,SIGNAL(timeout()),this,SLOT(updateUI()));
    filter.reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI()
{
    ui->emgNumber->display(emgcount);
    ui->countNumber->display(imucount);
    ui->c1Plot->rescaleAxes();
    ui->c1Plot->replot();
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

void MainWindow::on_openButton_clicked()
{
    if (ui->portBox->currentText().isEmpty())
        return;

    serialport.setPortName(ui->portBox->currentText());
    serialport.setBaudRate(921600);
    serialport.setDataBits(QSerialPort::Data8);
    serialport.setStopBits(QSerialPort::OneStop);
    serialport.setParity(QSerialPort::NoParity);
    serialport.setFlowControl(QSerialPort::NoFlowControl);
    connect(&serialport,SIGNAL(readyRead()),SLOT(handleReadyRead()));
    //connect(&parser,SIGNAL(parseFinish(ParserResult)),SLOT(response_received(ParserResult)));
    serialport.open(QIODevice::ReadWrite);
    imucount=0;
    emgcount=0;
    updatetimer.start(100);
    connect(&parser,SIGNAL(parseFinish(ParserResult)),this,SLOT(response_received(ParserResult)));
    ui->statusBar->showMessage(QString("Series port opened"));
}

void MainWindow::handleReadyRead()
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
            float quat[4];
            parser.getLatestIMUData(quat);
            //ui->textEdit->append(QString("%1, %2, %3, %4").arg(quat[0]).arg(quat[1]).arg(quat[2]).arg(quat[3]));

        }
        if (res==NEWEMGDATA)
        {
            //新的emg数据
            parser.getLatestEMGData(emg);
            for (int j=0;j<8;j++)
            {
                rawdata[j].append(emg[j]);
                float emgdata=emg[j];
                emg[j]=filter.iir_notch(emg[j],j);
                emg[j]=filter.fir_highpass(emg[j],j);
                filtered[j].append(emg[j]);
                if (j==0)
                    ui->c1Plot->graph(0)->addData(emgcount,emg[j]);
            }
            gesture = gesturerecognize0523(emg);
            ui->GestureEdit->setText(def_gesture[gesture]);
            if (emgcount>=1000)
                ui->c1Plot->graph(0)->removeData(emgcount-1000);
            emgcount++;
        }
        if (res==NEWCOMMANDRES)
        {
            ui->statusBar->showMessage(QString("Response received! res:%1").arg(parser.getLatestCommand(),0,16));
        }
    }
}


void MainWindow::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
}

void MainWindow::on_closeButton_clicked()
{
    serialport.close();
    updatetimer.stop();
}

void MainWindow::on_beginButton_clicked()
{
    static unsigned char begin[4]={0xff,0x01,0x10,0x10};
    static unsigned char IOset[6]={0xff,0x03,0x40,0x00,0x01,0x00};
    if (!serialport.isOpen())
        return;
//    for (unsigned char i=0x05;i<=0x0c;i++)
//    {
//        IOset[3]=i;
//        IOset[5]=i+0x01+0x40;
//        serialport.write((char*)IOset,6);
//    }
    serialport.write((char*)begin,4);
}

void MainWindow::on_stopButton_clicked()
{
    static unsigned char stop[4]={0xff,0x01,0x11,0x11};
    if (!serialport.isOpen())
        return;
    serialport.write((char*)stop,4);
}


void MainWindow::response_received(ParserResult r)
{
    if (r==NEWCOMMANDRES)
        ui->statusBar->showMessage(QString("Response received! res:%1").arg(parser.getLatestCommand()));
}

void MainWindow::on_ResetButton_clicked()
{
    static unsigned char reset[4]={0xff,0x01,0x80,0x80};

    if (!serialport.isOpen())
        return;
    serialport.write((char*)reset,4);
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("保存数据"),
         "",
         tr("数据文件 (*.dat)"));
    QString fileName2=fileName+'1';
    if (!fileName.isNull())
    {
        //fileName是文件名
        QFile f(fileName);
        QFile f2(fileName2);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ui->statusBar->showMessage(QString("Open failed."));
            return;
        }
        if(!f2.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ui->statusBar->showMessage(QString("Open failed."));
            return;
        }
        QTextStream txtOutput(&f);
        QTextStream txtOutput2(&f2);
        for (int i=0;i<emgcount;i++)
        {
            for (int j=0;j<8;j++)
            {
                txtOutput2<<filtered[j].at(i)<<' ';
                txtOutput<<rawdata[j].at(i)<<' ';
            }
            txtOutput2<<endl;
            txtOutput<<endl;
        }
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
        rawdata[i].clear();
        filtered[i].clear();
    }
    ui->c1Plot->graph(0)->clearData();
    ui->c1Plot->replot();
    ui->statusBar->showMessage(QString("Raw data list cleared."));
}

void MainWindow::on_initButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,
                    tr("打开"),
                    "",
                    tr("数据文件 (*.dat)"));
    QFile file(fileName);
    qDebug()<<file.exists();
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    QDataStream in(&file);
    float emgrow;
    int i = 0;
    int channel = 0;
    while((!file.atEnd()) && (i<N_FRENQUENCY)) {
        for (channel=0;channel<N_CHANNEL;channel++)
        {
            in>>emgrow;
            ini_emg[i][channel] = emgrow;
        }
        i++;
    }
    qDebug()<<"i:"<<i<<endl;
    re_initial(ini_emg);
    qDebug()<<"mav0:"<<mav0[0]<<" "<<mav0[1]<<" "<<mav0[2]<<" "<<mav0[3]<<endl;
    qDebug()<<"threshold"<<threshold<<endl;
}

void MainWindow::on_pushButtonRLD_clicked()
{
    unsigned char rldcommand[6] = {0xff,0x03,0x03,0x00,0x00,0x00};
    unsigned char rldp = 0x00,rldn=0x00;
    if (ui->checkBox1P->isChecked()) rldp |= 0x01;
    if (ui->checkBox2P->isChecked()) rldp |= 0x02;
    if (ui->checkBox3P->isChecked()) rldp |= 0x04;
    if (ui->checkBox4P->isChecked()) rldp = rldp | 0x08;

    if (ui->checkBox1N->isChecked()) rldn |= 0x01;
    if (ui->checkBox2N->isChecked()) rldn |= 0x02;
    if (ui->checkBox3N->isChecked()) rldn |= 0x04;
    if (ui->checkBox4N->isChecked()) rldn |= 0x08;

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
    unsigned char rrcommand[5]={0xff,0x02,0x20,0x00,0x20};
    unsigned char addr = ui->lineEditAddr->text().toInt(&ok,16);
    printf("%x\n",addr);
    rrcommand[3]=addr;
    rrcommand[4]=0x20+addr;

    if (!serialport.isOpen())
        return;

    serialport.write((char*)rrcommand,5);
}

void MainWindow::on_noiseButton_clicked()
{
    unsigned char noisecommand[4] = {0xff,0x01,0x04,0x04};
    if (!serialport.isOpen())
        return;
    serialport.write((char*)noisecommand,4);
}

void MainWindow::on_testButton_clicked()
{
    unsigned char squarecommand[4] = {0xff,0x01,0x05,0x05};
    if (!serialport.isOpen())
        return;
    serialport.write((char*)squarecommand,4);
}

void MainWindow::on_normalMeaButton_clicked()
{
    unsigned char normalcommand[4] = {0xff,0x01,0x06,0x06};
    if (!serialport.isOpen())
        return;
    serialport.write((char*)normalcommand,4);
}
