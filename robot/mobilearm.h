#ifndef MOBILEARM
#define MOBILEARM
#define JOINTNUM 5
#define AXISNUM 9
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
    void bend_initial();    //初始姿势
    void straight_initial();
	void motion_map(const float angles[JOINTNUM],const float axes[AXISNUM][3]);
    void beepOn();
    void setArm(double,double,double);
    void setArm(double* a);
    void moveArm(double,double,double);
    void move(int);     //0 stop, 1 ahead, 2 fast ahead, -1 back
    void turn(int);     // 1=45 degree, positve left
    void openSerial(QString &com);
    void closeSerial();
    QSerialPort serialPort;
    double x,y,z;  //腕心坐标mm，垂直为z，向前为x，向左为y
    double PI, HALF_PI;//定义使用的常数
    double angle[6]; //rad
    void compileMotion(int i);
    void executeMotions(int begin, int end);
    void executeMotion(int i);
    void setServo(int i, double rad);
    void setServo(int i, int deg);
    void postC();       // 蜷缩，方便移动
    void motionA(int i);    //0 c-->up; 1 up-->down and grasp --> up; 2:turn left; 3: put down back to c
    void speedUp();
    void speedDown();

    void initPosition();


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
    int moveNum;


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

