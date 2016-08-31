#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QMediaRecorder>
#include <QCameraImageCapture>
#include <QLabel>
#include <QDir>

namespace Ui {
class CameraWindow;
}

class CameraWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraWindow(QWidget *parent = 0);
    ~CameraWindow();

    int capture(int datacount);
    int loadPicture(int datacount);
    int savePictures(QString fileName);
    int setPictPath(QString fileName);
    int switchToRealtimeVideo();
    int switchToReplay();

private:
    Ui::CameraWindow *ui;

    // camera
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QLabel *pictureLabel;
    QCameraImageCapture *imageCapture;
    QDir pwd;
    QString picPath;
};

#endif // CAMERAWINDOW_H
