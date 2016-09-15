#include "camerawindow.h"
#include "ui_camerawindow.h"

CameraWindow::CameraWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CameraWindow)
{
    ui->setupUi(this);

    //camera
    camera = new QCamera();
    viewfinder = new QCameraViewfinder(this);
    pictureLabel=new QLabel(this);
    pictureLabel->hide();

    ui->verticalLayout->addWidget(viewfinder);
    ui->verticalLayout->addWidget(pictureLabel);

    viewfinder->setStyleSheet("QCameraViewfinder{border:1px}");
    pictureLabel->setStyleSheet("QLabel{border:1px}");

    viewfinder->size().setWidth(80);
    viewfinder->size().setHeight(60);
    camera->setViewfinder(viewfinder);
    viewfinder->show();

    imageCapture = new QCameraImageCapture(camera);

    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->start(); // to start the viewfinder

    pwd=QDir::current();

}

CameraWindow::~CameraWindow()
{
    delete ui;
}

int CameraWindow::capture(int datacount)
{
    QString path=QDir::current().absolutePath();
    //qDebug()<<path;
    path=path+QString("/temp/%1.jpg").arg(datacount);
    imageCapture->capture(path);
    return 0;
}

int CameraWindow::loadPicture(int datacount)
{
    QPixmap img=QPixmap::fromImage(QImage(QString("%1/%2.jpg").arg(picPath).arg(datacount)));
    if (!img.isNull())
        pictureLabel->setPixmap(img.scaled(pictureLabel->size(),Qt::KeepAspectRatio));
    return 0;
}

int CameraWindow::savePictures(QString fileName)
{
    //pictures
    QDir::current().rename(QString("temp"),QFileInfo(fileName).baseName());
    QDir::current().mkdir(QString("temp"));
    return 0;
}

int CameraWindow::setPictPath(QString fileName)
{
    QString path=QFileInfo(fileName).path();
    QString name=QFileInfo(fileName).baseName();
    picPath=path+QString("/")+name;
    qDebug()<<picPath;
    return 0;
}

int CameraWindow::switchToRealtimeVideo()
{
    ui->verticalLayout->replaceWidget(pictureLabel,viewfinder);
    pictureLabel->hide();
    viewfinder->show();
    return 0;
}

int CameraWindow::switchToReplay()
{
    ui->verticalLayout->replaceWidget(viewfinder,pictureLabel);
    viewfinder->hide();
    ui->verticalLayout->addWidget(pictureLabel);
    pictureLabel->show();

    QDir dir=QDir(pwd);
    dir.cd(QString("temp"));
    dir.removeRecursively();
    pwd.mkdir(QString("temp"));

    return 0;
}
