#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recognize.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->c1Plot->addGraph();
    ui->c1Plot->graph(0)->setName(QString("channel 1"));
    ui->c1Plot->xAxis->setRange(0,1000);

    ui->c2Plot->addGraph();
    ui->c2Plot->graph(0)->setName(QString("channel 2"));
    ui->c2Plot->xAxis->setRange(0,1000);

    ui->c3Plot->addGraph();
    ui->c3Plot->graph(0)->setName(QString("channel 3"));
    ui->c3Plot->xAxis->setRange(0,1000);

    ui->c4Plot->addGraph();
    ui->c4Plot->graph(0)->setName(QString("channel 4"));
    ui->c4Plot->xAxis->setRange(0,1000);

    ui->c5Plot->addGraph();
    ui->c5Plot->graph(0)->setName(QString("channel 5"));
    ui->c5Plot->xAxis->setRange(0,1000);

    ui->c6Plot->addGraph();
    ui->c6Plot->graph(0)->setName(QString("channel 6"));
    ui->c6Plot->xAxis->setRange(0,1000);

    ui->c7Plot->addGraph();
    ui->c7Plot->graph(0)->setName(QString("channel 7"));
    ui->c7Plot->xAxis->setRange(0,1000);

    ui->c8Plot->addGraph();
    ui->c8Plot->graph(0)->setName(QString("channel 8"));
    ui->c8Plot->xAxis->setRange(0,1000);

    plots[0]=ui->c1Plot;
    plots[1]=ui->c2Plot;
    plots[2]=ui->c3Plot;
    plots[3]=ui->c4Plot;
    plots[4]=ui->c5Plot;
    plots[5]=ui->c6Plot;
    plots[6]=ui->c7Plot;
    plots[7]=ui->c8Plot;

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

    for (int i=0;i<8;i++)
    {
        plots[i]->rescaleAxes();
        plots[i]->replot();
    }
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



void MainWindow::on_closeButton_clicked()
{
    serialport.close();
    updatetimer.stop();
}

void MainWindow::on_beginButton_clicked()
{

}

void MainWindow::on_stopButton_clicked()
{

}


void MainWindow::response_received(ParserResult r)
{
    if (r==NEWCOMMANDRES)
        ui->statusBar->showMessage(QString("Response received! res:%1").arg(parser.getLatestCommand()));
}

void MainWindow::on_ResetButton_clicked()
{

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

        QString fileName3=fileName.split('.')[0]+".imu";
        QFile f3(fileName3);
        if(!f3.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            ui->statusBar->showMessage(QString("Open failed."));
            return;
        }
        QTextStream txtOutput3(&f3);
        for (int i=0;i<imucount;i++)
        {
            for (int j=0;j<12;j++)
            {
                txtOutput3<<quatRaw.at(i).at(j)<<' ';
            }
            txtOutput3<<endl;
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
        plots[i]->graph(0)->clearData();
        plots[i]->replot();
    }

    quatRaw.clear();
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
    unsigned char addr = ui->lineEditAddr->text().toInt(&ok,16);
    printf("%x\n",addr);
}

void MainWindow::on_noiseButton_clicked()
{

}

void MainWindow::on_testButton_clicked()
{

}


