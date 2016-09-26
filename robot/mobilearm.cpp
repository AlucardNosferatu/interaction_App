#include "mobilearm.h"



/*****************************************************************
功能：初始化控制参量angle\oldAngle\xyz，并发送串命令
*******************************************************************/
void MobileArm::bend_initial()
{
  angle[0] = 0;
  angle[1] = -HALF_PI*0.8;
  angle[2] = PI*0.8;
  angle[3] = PI/6;
  angle[4] = 0;
  angle[5] = 0;

  for(int i=0;i<6;i++)//记录命令
  {
    oldAngle[i] = angle[i];
  }

  angle2xyz(); //同步手心位置
  T = 1000; //初始化，用较慢的速度
  QString cmd = "{G0" + arm_command() + "}";
  serialPort.write(cmd.toLatin1());
}

void MobileArm::straight_initial()
{
    angle[0] = 0;
    angle[1] = 0;
    angle[2] = 0;
    angle[3] = 0;
    angle[4] = 0;
    angle[5] = 0;

    for(int i=0;i<6;i++)//记录命令
    {
      oldAngle[i] = angle[i];
    }

    angle2xyz(); //同步手心位置
    T = 1000; //初始化，用较慢的速度
    QString cmd = "{G0" + arm_command() + "}";
    serialPort.write(cmd.toLatin1());
}

void MobileArm::beepOn()
{
    serialPort.write( QString("$BEEP_ON!").toLatin1());
}

// 绝对坐标控制
void MobileArm::setArm(double xv, double yv, double zv)
{
    double old_x, old_y, old_z;
    old_x = x; old_y = y; old_z = z;
    x = xv;
    y = yv;
    z = zv;
    if(sqrt(x*x+y*y)>200)
        beta = PI/2;
    else
        beta = PI/6;

    if( xyz2angle()!=0 ) //xyz转化为关节角，并进行安全检验
    {//不合法
        x = old_x; y = old_y;  z = old_z;
        beepOn();
    }
    else
    {
        safeT(); //机械臂安全检验
        QString cmd = "{G0" + arm_command() + "}";
        serialPort.write( cmd.toLatin1() ); //机械臂指令
    }
}

void MobileArm::turn(int n)
{
    int m = abs(n);
    int delay = 370;
    if(n>0)
    {
        left = -255;
        right = 255;
        serialPort.write( wheel_command().toLatin1() );
        delayTimer.start(delay*m);
    }
    else if(n<0)
    {
        left = 255;
        right = -255;
        serialPort.write( wheel_command().toLatin1() );
        delayTimer.start(delay*m);
    }
}

// 增量式控制
void MobileArm::moveArm(double xd, double yd, double zd)
{
    setArm(x+xd,y+yd,z+zd);
}

/****************************************************************
功能：控制小车的前进、停止、后退
v>0 前进
v<0 后退
v=0 静止
*****************************************************************/
void MobileArm::move(int v)
{
    if(v>0)
    {
        left = right = 255;
    }
    else if(v<0)
    {
        left = right = -255;
    }
    else
        left = right = 0;
    serialPort.write( wheel_command().toLatin1() );
}



/*****************************************************************
功能：由theta3和腕心位置计算前三个舵机的转角，同时进行安全检验
输入：舵机角度数组double[6]，腕心坐标x,y,z(单位与机器人手臂单位相同）,腕倾角alpha，手倾角beta
输出：六个舵机的角度数组，double[6](rad)，改变0~4
输出：0-有效,并改变angle和oldAngle
     1-超出操作域
     2-与底盘发生碰撞
*******************************************************************/
int MobileArm::xyz2angle()
{
    double t0,t1,t2;
    t0 = atan(y/x);
    double r = sqrt(x*x+y*y)-L0;
    if( sqrt(r*r+z*z)>L1+L2 )
        return 1;
    t2 = acos( (z*z+r*r-L1*L1-L2*L2)/(2*L1*L2) );
    t1 = atan2(r,z)-atan2(L2*sin(t2),L1+L2*cos(t2));

    if(t1>PI/2)
        return 2;

    if( z<=0 && y>=-wid/2 && y<=wid/2 && x>=-len/2 && x<= len/2 )
        return 2;

    double x3,y3,z3;
    x3 = x+L3*cos(alpha)*cos(t0);
    y3 = y+L3*cos(alpha)*sin(t0);
    z3 = z-L3*sin(alpha);
    if( z3<=0 && y3>=-wid/2 && y3<=wid/2 && x3>=-len/2 && x3<= len/2 )
        return 2;
    double x4,y4,z4;
    x4 = x3+L4*cos(beta)*cos(t0);
    y4 = y3+L4*cos(beta)*sin(t0);
    z4 = z3-L4*sin(beta);
    if( (z4<=0) && (y4>=-wid/2) && (y4<=wid/2) && (x4>=-len/2) && (x4<= len/2) )
        return 2;

    for(int i=0;i<5;i++)
        oldAngle[i] = angle[i];

    angle[0] = t0;
    angle[1] = t1;
    angle[2] = t2;
    angle[3] = PI/2+alpha-t1-t2;
    angle[4] = beta-alpha;

    return 0;

}

/*****************************************************************
功能：由前3个舵机的转角反算腕心位置
输入：舵机角度数组double[6]，腕心坐标x,y,z(单位与机器人手臂单位相同）
输出：腕心位置x,y,z
*******************************************************************/
void MobileArm::angle2xyz()
{
  double r = L0 + L1*sin(angle[1]) +  L2*sin( angle[1]+ angle[2] );
  z = L1*cos( angle[1] ) +  L2*cos( angle[1] + angle[2] );
  x = r*cos(angle[0]);
  y = r*sin(angle[0]);
}

/******************************************************************
功能：根据angle输出控制命令
输入：六个舵机的角度数组，double[6](rad),时间限制T
输出：字符串命令
******************************************************************/
QString MobileArm::arm_command()
{
  //0号舵机，控制腰关节，采用数字舵机-135~135度,并加入齿隙补偿，一圈24个齿
  int pwm = 1500 + ( angle[0]/PI+1.0/24)/1.5 * 2000;
  pwm = constrian(pwm);
  QString cmd0;
  cmd0 = QString("#0P%1T%2!").arg(pwm).arg(T);

  //1号舵机，控制肩关节，采用数字舵机-90~90度
  pwm = 1500 - ( angle[1]/PI+1.0/24) * 2000;
  pwm = constrian(pwm);
  QString cmd1;
  cmd1 = QString("#1P%1T%2!").arg(pwm).arg(T);

  //2号舵机，控制肘关节，采用数字舵机-90~90度
  pwm = 1500 -((angle[2]-HALF_PI)/ PI-1.0/24) * 2000;
  pwm = constrian(pwm);
  QString cmd2;
  cmd2 = QString("#2P%1T%2!").arg(pwm).arg(T);

  //3号舵机，控制腕关节，采用数字舵机-135~135度
  pwm = 1500 -( angle[3]/PI/1.5 ) * 2000;
  pwm = constrian(pwm);
  QString cmd3;
  cmd3 = QString("#3P%1T%2!").arg(pwm).arg(T);

  //4号舵机，控制腕关节，采用模拟舵机-90~90度，方向为右手（增加向外）
  pwm = 1500 +( angle[4]/PI ) * 2000;
  pwm = constrian(pwm);
  QString cmd4;
  cmd4 = QString("#4P%1T%2!").arg(pwm).arg(T);

  //6号舵机，控制机械爪开合，采用模拟舵机-90~90度，增加为合，减小为开
  pwm = 1500 +( angle[5]/PI ) * 2000;
  pwm = constrian(pwm);
  QString cmd6;
  cmd6 = QString("#6P%1T%2!").arg(pwm).arg(T);

  QString cmd = cmd0 + cmd1 + cmd2 + cmd3 + cmd4 + cmd6;

  return cmd;
}

//生成调试某个舵机的命令
QString MobileArm::servo_command(int i)
{
    int pwm;
    QString cmd;
    switch(i)
    {
    case 0:
        //0号舵机，控制腰关节，采用数字舵机-135~135度,并加入齿隙补偿，一圈24个齿
        pwm = 1500 + ( angle[0]/PI+1.0/24)/1.5 * 2000;
        pwm = constrian(pwm);
        cmd = QString("#0P%1T%2!").arg(pwm).arg(T);
        break;
    case 1:
        //1号舵机，控制肩关节，采用数字舵机-90~90度
        pwm = 1500 - ( angle[1]/PI+1.0/24) * 2000;
        pwm = constrian(pwm);
        cmd = QString("#1P%1T%2!").arg(pwm).arg(T);
        break;
    case 2:
        //2号舵机，控制肘关节，采用数字舵机-90~90度
        pwm = 1500 -((angle[2]-HALF_PI)/ PI-1.0/24) * 2000;
        pwm = constrian(pwm);
        cmd = QString("#2P%1T%2!").arg(pwm).arg(T);
        break;
    case 3:
        //3号舵机，控制腕关节，采用数字舵机-135~135度
        pwm = 1500 -( angle[3]/PI/1.5 ) * 2000;
        pwm = constrian(pwm);
        cmd = QString("#3P%1T%2!").arg(pwm).arg(T);
        break;
    case 4:
        //4号舵机，控制腕关节，采用模拟舵机-90~90度，方向为右手（增加向外）
        pwm = 1500 +( angle[4]/PI ) * 2000;
        pwm = constrian(pwm);
        cmd = QString("#4P%1T%2!").arg(pwm).arg(T);
        break;
    case 5:
        //6号舵机，控制机械爪开合，采用模拟舵机-90~90度，增加为合，减小为开
        pwm = 1500 +( angle[5]/PI ) * 2000;
        pwm = constrian(pwm);
        cmd = QString("#6P%1T%2!").arg(pwm).arg(T);
        break;
    }

    QString compile_cmd =  cmd;
    return compile_cmd;
}

/******************************************************************
功能：发送指令，控制左右轮转动
输入：两个轮的功率，向前为正，向后为负，最大为255
输出：舵机版字符命令
******************************************************************/
QString MobileArm::wheel_command()
{
  //确定左右轮的方向，左轮1-前，0-后，右轮相反
  int leftDirect;
  if(left>0)
  {
    leftDirect = 1;
  }
  else
  {
    leftDirect = 0;
    left = -left;
  }

  int rightDirect;
  if(right>0)
  {
    rightDirect = 0;
  }
  else
  {
    rightDirect = 1;
    right = -right;
  }

  //输出命令
  QString cmd;
  cmd = QString("$DCR:%1-%2,%3-%4!").arg(left).arg(right).arg(leftDirect).arg(rightDirect);
  return cmd;
}

/*****************************************************************************
功能：根据新旧angle确定指令时间T
输入：目标命令angle[6],和历史命令oldAngle[6]
输出：指令T (ms)
*****************************************************************************/
void MobileArm::safeT()
{
  T = 500;
  for(int i=0;i<6;i++)
  {
    int Ti = 5*1000.0/HALF_PI*abs(angle[i]-oldAngle[i]);  //设置最快速度是 90度/5秒
    T = T>Ti?T:Ti;
  }
}

int MobileArm::constrian(int pwm)
{
    if(pwm<1500)
        pwm = 1500;
    if(pwm>2500)
        pwm = 2500;
    return pwm;
}

void MobileArm::timeoutStop()
{
    move(0);
    delayTimer.stop();
}


/*****************************************************************************
功能：构造函数，定义相关几何参数
*****************************************************************************/
MobileArm::MobileArm()
{
    L0 = 19.0;
    L1 = 105.0;
    L2 = 98.0;
    L3 = 110.0;
    L4 = 110.0;

    wid = 300.0;
    len = 400.0;

    PI = acos(-1);
    HALF_PI = PI/2;

    alpha = PI/6; //腕倾角rad
    beta = PI/6; //手倾角rad

    T = 500;

    connect(&delayTimer,SIGNAL(timeout()),this,SLOT(timeoutStop()));
}

MobileArm::~MobileArm()
{
    serialPort.close();
}

//串口打开,并初始化
void MobileArm::openSerial(QString &com)
{
    serialPort.setBaudRate(9600);
    serialPort.setPortName(com);
    serialPort.open(QIODevice::ReadWrite);

    bend_initial();
}

void MobileArm::compileMotion(int i)
{
    QString cmd = "<G" + QString::number(i) + arm_command() + ">";
    serialPort.write(cmd.toLatin1());
    serialPort.write("$BEEP_ON!");
}

void MobileArm::executeMotions(int begin, int end)
{
    QString cmd = QString("$DGT:%1-%2,1!").arg(begin).arg(end);
    serialPort.write(cmd.toLatin1());
}

void MobileArm::executeMotion(int i)
{
   QString cmd = QString("$DGS:%1!").arg(i);
   serialPort.write(cmd.toLatin1());

}

void MobileArm::setServo(int i, double rad)
{
    angle[i] = rad;
    safeT();
    serialPort.write( servo_command(i).toLatin1() ); //机械臂指令
}

void MobileArm::setServo(int i, int deg)
{
    double rad = deg/180.0*PI;
    setServo(i,rad);
}

void MobileArm::setArm(double *a)
{
    for(int i=0;i<6;i++)
        angle[i] = a[i];
    safeT(); //机械臂安全检验
    QString cmd = "{G0" + arm_command() + "}";
    serialPort.write( cmd.toLatin1() ); //机械臂指令
}
