#ifndef MOBILEARM
#define MOBILEARM

#include <cmath>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QObject>



class MobileArm: public QObject
{
    Q_OBJECT
public:
    MobileArm();
    ~MobileArm();
    void bend_initial();
    void straight_initial();
    void beepOn();
    void setArm(double,double,double);
    void setArm(double* a);
    void moveArm(double,double,double);
    void move(int);
    void turn(int);
    void openSerial(QString &com);
    QSerialPort serialPort;
    double x,y,z;  //腕心坐标mm，垂直为z，向前为x，向左为y
    double PI, HALF_PI;//定义使用的常数
    double angle[6]; //rad
    void compileMotion(int i);
    void executeMotions(int begin, int end);
    void executeMotion(int i);
    void setServo(int i, double rad);
    void setServo(int i, int deg);


private:
    double L0, L1, L2, L3, L4;//机械臂尺寸(mm)
    double wid, len; //底盘尺寸


    // 机械臂控制量

    double alpha; //腕倾角rad，与水平面的夹角，向下为正
    double beta; //手倾角rad，同上
    double gamma; //机械手张角rad，-90度为闭合

    double oldAngle[6]; //记录之前的关节角
    int T; //每次角度改变的时间(ms)
    int left, right;  //占空比-255~255


    QTimer delayTimer;

private:
    int xyz2angle();
    void angle2xyz();
    QString arm_command();
    QString servo_command(int i);
    QString wheel_command();
    void safeT();
    int constrian(int pwm);
private slots:
    void timeoutStop();
};

#endif // MOBILEARM

