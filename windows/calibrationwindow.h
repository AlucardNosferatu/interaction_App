#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QMainWindow>
#include <movement.h>
#include <dataprocessor.h>
#include <gesture_modeling/gesture.h>
#include <QLineEdit>

namespace Ui {
class CalibrationWindow;
}

class CalibrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalibrationWindow(QWidget *parent ,DataProcessor &d);
    ~CalibrationWindow();

private:
    Ui::CalibrationWindow *ui;
    DataProcessor &dataprocessor;
    QLineEdit *thresholdEdits[JOINTNUM],*rangeEdits[JOINTNUM];
    QLabel *zerosEdits[JOINTNUM];

    double zeros[JOINTNUM],thresholds[JOINTNUM],motionRanges[JOINTNUM];

private slots:
    void on_calibrationButton_clicked();
    void on_savecaliButton_clicked();
    void on_loadcaliButton_clicked();
    void on_updateParaButton_clicked();
    void on_frontButton_toggled(bool checked);
    void on_backButton_toggled(bool checked);

};

#endif // CALIBRATIONWINDOW_H
