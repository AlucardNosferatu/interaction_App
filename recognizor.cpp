#include "recognizor.h"
extern int i = 0;
Recognizor::Recognizor()
{
    IMUconnected=false;
    grasptest=false;
    robotConnected=false;
    dataprocessor.setRalSensor(&ralsensor);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
}

QString Recognizor::getCurrentGesture()
{
    return currentGesture;
}

int Recognizor::setCameraWindow(CameraWindow *c)
{
    cwin=c;
    return 0;
}

int Recognizor::update()
{
    float quat_temp[SENSORNUM*4];
    float angles[JOINTNUM],axes[AXISNUM][3];
	float accel[3];

    if (!fileMode)
    {
        if (IMUconnected)
        {
            // read IMU data and store it in QList
            dataprocessor.getIMUData(angles,axes,quat_temp,accel);
            QList<float> qvector_temp;
            for (int i=0;i<SENSORNUM*5;i++)
                qvector_temp.append(quat_temp[i]);
            quatRaw.append(qvector_temp);
            emit newIMUData(angles,datacount);
			emit newaccel(accel,datacount);
        }
        cwin->capture(datacount);
    }
    else
    {
        if (dataprocessor.IMUfileExists)
        {
            int retval = dataprocessor.getIMUDataFromFile(angles,axes,quat_temp,accel);
            if (retval>=0)
			{
                emit newIMUData(angles,datacount);
				emit newaccel(accel,datacount);
			}
            else
                return -1;
        }
        cwin->loadPicture(datacount);
    }

    if(datacount==0 || datacount==startpoint)
    {
        deltas[datacount][ELB]=0;
        deltas[datacount][TWI]=0;
        deltas[datacount][POL]=0;
        deltas[datacount][AZI]=0;
        deltas[datacount][OME]=0;
    }
    else
    {
        if (angles[ELB]-lastangles[ELB]>4)
            angles[ELB]-=2*3.1415926f;
        if (angles[ELB]-lastangles[ELB]<-4)
            angles[ELB]+=2*3.1416926f;
        if (angles[TWI]-lastangles[TWI]>4)
            angles[TWI]-=2*3.1415926f;
        if (angles[TWI]-lastangles[TWI]<-4)
            angles[TWI]+=2*3.1415926f;
        int index=datacount % BUFFERLEN;
        deltas[index][TWI]=angles[TWI]-lastangles[TWI];
        deltas[index][ELB]=angles[ELB]-lastangles[ELB];
        deltas[index][POL]=angles[POL]-lastangles[POL];
        deltas[index][AZI]=angles[AZI]-lastangles[AZI];
        deltas[index][OME]=angles[OME]-lastangles[OME];
    }

    lastangles[TWI]=angles[TWI];
    lastangles[ELB]=angles[ELB];
    lastangles[POL]=angles[POL];
    lastangles[AZI]=angles[AZI];
    lastangles[OME]=angles[OME];
    //recognitnion
    int retval=gestureRecognition(angles,axes);
    datacount++;
    return 0;
}

int Recognizor::gestureRecognition(const float angles[JOINTNUM], const float axes[AXISNUM][3])
{
    qDebug()<<axes[2][0]<<axes[8][0]<<axes[2][1]<<axes[8][1]<<axes[2][2]<<axes[8][2];

    if(i == 0){
        for(int j=0;j<6;j++){
            Angle[j] = 0;
        }
        //第一次控制手爪时使其长大到-1弧度
        Angle[5] = -1;
        Angle[2] = 1.5;
        Angle[3] = 0.5;
        Angle[1] = 0.1;
    }

    for (int joint=0;joint<JOINTNUM;joint++)
        for (int move=0;move<MOVEMENTNUM;move++)
            lastp[joint][move]=newp[joint][move];
    getmProbability(lasthead,datacount,newp,lastp,deltas,states);
    int ret=gesturelib.updateBestGesture(angles,axes,newp);
    if (ret==NEWGESTURE)
    {
        if (gesturelib.getBestureGestureIndex()==-1)
        {
            emit newGesture(QString(""));
            currentGesture=QString("");
        }
        else
        {
            emit newGesture(gesturelib.getBestGestureName());
            currentGesture=gesturelib.getBestGestureName();

            if (robotConnected)
            {
                if (!grasptest)
                {
                    // navigation
                    if (gesturelib.getBestGestureCommand()=="SPEEDUP")
                    {
                        robot.speedUp();
                    }
                    if (gesturelib.getBestGestureCommand()=="SLOWDOWN")
                        robot.speedDown();
                    if (gesturelib.getBestGestureCommand()=="TURNLEFT")
                        robot.turn(1);
                    if (gesturelib.getBestGestureCommand()=="TURNRIGHT")
                        robot.turn(-1);
                    if (gesturelib.getBestGestureCommand()=="BACK")
                        robot.move(-1);
                    if (gesturelib.getBestGestureCommand()=="STOP")
                        robot.move(0);
                    if (gesturelib.getBestGestureCommand()=="GETREADY")
                    {
                        emit changeToGrasp();
                        grasptest=true;
                    }
                }else
                {
                    i = 1;
                    // grasp
                    if (gesturelib.getBestGestureCommand()=="SPEEDUP")
                        //robot.motionA(0);
                    {
                        Angle[3] = Angle[3] + 0.2;
                        robot.setServo(3,Angle[3] );
                    }
                    if (gesturelib.getBestGestureCommand()=="SLOWDOWN")
                        //robot.motionA(1);
                    {
                    Angle[3] = Angle[3] - 0.2;
                        robot.setServo(3,Angle[3] );
                    }
                    if (gesturelib.getBestGestureCommand()=="TURNLEFT")
                        //robot.motionA(2);
                    {
                        Angle[0] = Angle[0] + 0.2;
                        robot.setServo(0,Angle[0] );
                    }
                    if (gesturelib.getBestGestureCommand()=="TURNRIGHT")
                        //robot.motionA(3);
                    {
                        Angle[0] = Angle[0] - 0.2;
                        robot.setServo(0,Angle[0] );
                    }
                    if (gesturelib.getBestGestureCommand()=="GO")
                        //robot.motionA(3);
                    {
                        //Angle[1] = Angle[1] + 0.1;
                        //robot.setServo(1,Angle[1] );
                        Angle[2] = Angle[2] + 0.1;
                        robot.setServo(2,Angle[2] );
                    }
                    if (gesturelib.getBestGestureCommand()=="BACK")
                        //robot.motionA(3);
                    {
                        //Angle[1] = Angle[1] - 0.05;
                        //robot.setServo(1,Angle[1] );
                        Angle[2] = Angle[2] - 0.1;
                        robot.setServo(2,Angle[2] );
                    }
                    if (gesturelib.getBestGestureCommand()=="TURNHAND")
                        //robot.motionA(3);
                    {
                        Angle[1] = Angle[1] + 0.2;
                        robot.setServo(1,Angle[1] );
//                        if(Angle[1]>=1)
//						{
//							Angle[1] = -1;
//						}
                    }
                    if (gesturelib.getBestGestureCommand()=="SHRINK")
                        //robot.motionA(3);
                    {
                        Angle[5] = Angle[5] + 0.1;
                        robot.setServo(5, Angle[5]);
                    }
                    if (gesturelib.getBestGestureCommand()=="OPEN")
                        //robot.motionA(3);
                    {
                        Angle[5] = Angle[5] - 0.1;
                        robot.setServo(5, Angle[5]);
                    }

                    //if(gesturelib.getBestGestureCommand()=="KEEPCALM")
                    //if((newp[0][0]>0.5&&newp[1][0]>0.5)&&((newp[2][0]>0.5)&&(newp[3][0]>0.5))&&(newp[4][0]>0.5))
                            //robot.motion_map( angles);
                    if (gesturelib.getBestGestureCommand()=="GETREADY")//change mode
                    {
                        emit changeToGrasp();
                        //robot.bend_initial();
                        grasptest=false;
                        //==TODO
                    }

                }
                //robot.closeSerial();
                //ralsensor.openSerialPort();
                //ralsensor.triggerFeedback(1);
            }

        }
    }
    if (ret==GESTUREEND)
    {
        emit newGesture(QString(""));
        currentGesture=QString("");
        lasthead=datacount;
        for (int joint=0;joint<JOINTNUM;joint++)
            for (int move=0;move<MOVEMENTNUM;move++){
                lastp[joint][move]=0;
                newp[joint][move]=0;
            }
    }
    return 0;
}

int Recognizor::initReplay(QString fileName)
{
    cwin->setPictPath(fileName);
    dataprocessor.resetFileStream(fileName);
    datacount=0;
    fileMode=true;
    lasthead=0;
    cwin->switchToReplay();
    for (int c=0;c<ELECTRODENUM;c++)
        ban[c]=0;
    return dataprocessor.getFileLineNum();
}

int Recognizor::setReplayProcess(int pos)
{
    startpoint=pos;
    dataprocessor.setFilePos(startpoint);
    datacount=startpoint;
    lasthead=startpoint;
    for (int joint=0;joint<JOINTNUM;joint++)
        for (int move=0;move<MOVEMENTNUM;move++)
        {
            lastp[joint][move]=0;
            newp[joint][move]=0;
        }
    gesturelib.resetGestureLikelihoods();
    return 0;
}

int Recognizor::initRealtimeRecognition()
{
    fileMode=false;
    datacount=0;
    lasthead=0;
    cwin->switchToRealtimeVideo();
    return 0;
}

int Recognizor::timerbegin(int interval)
{
    timer.start(interval);
    return 0;
}

int Recognizor::timerstop()
{
    timer.stop();
    return 0;
}

int Recognizor::saveData(const QString &filename)
{
    QString fname=QString("%1.imu").arg(filename);
    QFile f(fname);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
     printf("Open failed.");
     return -1;
    }
    QTextStream txtOutput(&f);
    for (int i=0;i<quatRaw.length();i++)
    {
        for (int j=0;j<SENSORNUM*5;j++)
            txtOutput<<quatRaw[i][j]<<' ';
        txtOutput<<endl;
    }
    f.close();
    cwin->savePictures(filename);
    return 0;
}

int Recognizor::loadFile(QString fileName)
{

    qDebug()<<fileName;
    dataprocessor.resetFileStream(fileName);
    int fileLength=dataprocessor.getFileLineNum()-1;
    datacount=0;
    lasthead=0;
    return fileLength;
}

int Recognizor::reset()
{
    quatRaw.clear();
    datacount=0;
    lasthead=0;
    for (int joint=0;joint<JOINTNUM;joint++)
        for (int move=0;move<MOVEMENTNUM;move++)
        {
            lastp[joint][move]=0;
            newp[joint][move]=0;
        }
    return 0;
}

DataProcessor& Recognizor::getDataprocessor()
{
    return dataprocessor;
}

GestureLib &Recognizor::getGesturelib()
{
    return gesturelib;
}

int Recognizor::connectIMU(int interval)
{
    dataprocessor.connectIMU(interval);
    IMUconnected=true;
    return 0;
}

int Recognizor::disconnectIMU()
{
    dataprocessor.disconnectIMU();
    IMUconnected=false;
    return 0;
}

bool Recognizor::isIMUConnected()
{
    return IMUconnected;
}

//////////////////////////////////////////////////////////////////////////

float Recognizor::getLikelihood(float data,float p0,float p1,float p2,float p3)
{
//    data=data*10000;
    if (data<p0)
        return 0;
    if (data>=p0 && data<p1)
        return (data-p0)/(p1-p0);
    if (data>=p1 && data<p2)
        return 1;
    if (data>=p2 && data<p3)
        return 1-(data-p2)/(p3-p2);
    if (data>=p3)
        return 0;
}

int Recognizor::connectRobot()
{
    robotConnected=true;
    return 0;
}

int Recognizor::disconnectRobot()
{
    robotConnected=false;
    return 0;
}

void Recognizor::enableGraspTest()
{
    grasptest=true;
    qDebug()<<"Grasp test!";
}

void Recognizor::disableGraspTest()
{
    grasptest=false;
}
