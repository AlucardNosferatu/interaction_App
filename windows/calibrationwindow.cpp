#include "calibrationwindow.h"
#include "ui_calibrationwindow.h"

CalibrationWindow::CalibrationWindow(QWidget *parent, DataProcessor &d) :
    QMainWindow(parent),
    ui(new Ui::CalibrationWindow),
    dataprocessor(d)
{
    ui->setupUi(this);

    ui->elbow0->setText(QString("Elbow0: %1").arg(0));
    ui->twist0->setText(QString("Twist0: %1").arg(0));
    ui->polar0->setText(QString("Polar0: %1").arg(0));
    ui->azimuthal0->setText(QString("Azimuthal0: %1").arg(0));
    ui->omega0->setText(QString("Omega0: %1").arg(0));

    //zeros label
    zerosEdits[0]=ui->elbow0;
    zerosEdits[1]=ui->twist0;
    zerosEdits[2]=ui->polar0;
    zerosEdits[3]=ui->azimuthal0;
    zerosEdits[4]=ui->omega0;

    //motion range textedits
    rangeEdits[0]=ui->elbowText;
    rangeEdits[1]=ui->twistText;
    rangeEdits[2]=ui->polarText;
    rangeEdits[3]=ui->thetaText;
    rangeEdits[4]=ui->omegaText;

    //thresholds textedits
    thresholdEdits[0]=ui->elbowThreshold;
    thresholdEdits[1]=ui->twistThreshold;
    thresholdEdits[2]=ui->polarThreshold;
    thresholdEdits[3]=ui->thetaThreshold;
    thresholdEdits[4]=ui->omegaThreshold;

    for (int i=0;i<JOINTNUM;i++)
    {
        thresholds[i]=0.01;
        if (i!=Joint::OME)
            motionRanges[i]=3.14159;
        else
            motionRanges[i]=1.2;
        if (i==Joint::POL)
        {
            thresholds[i]=0.01;
            motionRanges[i]=1.6;
        }
        thresholdEdits[i]->setValidator(new QDoubleValidator());
        rangeEdits[i]->setValidator(new QDoubleValidator());
        thresholdEdits[i]->setText(QString("%1").arg(thresholds[i]));
        rangeEdits[i]->setText(QString("%1").arg(motionRanges[i]));
    }
    setParameters(thresholds,motionRanges);
}

CalibrationWindow::~CalibrationWindow()
{
    delete ui;
}


void CalibrationWindow::on_calibrationButton_clicked()
{
    float angles[5];
    for(int i=0;i<5;i++)
        zeros[i]=0;
    for (int i=0;i<10;i++)
    {
        dataprocessor.getIMUData(angles,NULL,NULL,NULL);
        for (int j=0;j<5;j++)
            zeros[j]+=angles[j];
        Sleep(100);
    }
    for (int i=0;i<5;i++)
        zeros[i]=zeros[i]/10;

    dataprocessor.setZeros(zeros);
    for (int i=0;i<JOINTNUM;i++)
        zerosEdits[i]->setText(QString("%1:%2").arg(jointNames[i]).arg(zeros[i]));
}

void CalibrationWindow::on_savecaliButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("保存校准数据"),
         "",
         tr("数据文件 (*.cal)"));
    if (!fileName.isNull())
    {
        //fileName是文件名
        QFile f(fileName);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            printf("Open failed.");
            return;
        }
        QTextStream txtOutput(&f);
        for (int i=0;i<JOINTNUM;i++)
        {
            txtOutput<<zeros[i]<<' '<<thresholds[i]<<' '<<motionRanges[i]<<endl;
        }
        f.close();
    }
}

void CalibrationWindow::on_loadcaliButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("打开校准数据"),
         "",
         tr("数据文件 (*.cal)"));
    if (!fileName.isNull())
    {
        //fileName是文件名
        QFile f(fileName);
        if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            printf("Open failed.");
            return;
        }
        QTextStream txtInput(&f);
        for (int i=0;i<JOINTNUM;i++)
        {
            txtInput>>zeros[i]>>thresholds[i]>>motionRanges[i];
        }
        f.close();
        //zeros

        dataprocessor.setZeros(zeros);
        setParameters(thresholds,motionRanges);

        //update text
        for (int i=0;i<JOINTNUM;i++)
        {
            zerosEdits[i]->setText(QString("%1:%2").arg(jointNames[i]).arg(zeros[i]));
            thresholdEdits[i]->setText(QString("%1").arg(thresholds[i]));
            rangeEdits[i]->setText(QString("%1").arg(motionRanges[i]));
        }
    }
}

void CalibrationWindow::on_updateParaButton_clicked()
{
    for (int i=0;i<JOINTNUM;i++)
    {
        thresholds[i]=thresholdEdits[i]->text().toDouble();
        motionRanges[i]=rangeEdits[i]->text().toDouble();
    }
    setParameters(thresholds,motionRanges);
}

void CalibrationWindow::on_frontButton_toggled(bool checked)
{
    if (checked)
        dataprocessor.setDirection(1.0);
}

void CalibrationWindow::on_backButton_toggled(bool checked)
{
    if (checked)
        dataprocessor.setDirection(-1.0);
}
