#include "recognizor.h"

Recognizor::Recognizor()
{
    EMGconnected=false;
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
    float emgdata[ELECTRODENUM];

    if (!fileMode)
    {
        if (IMUconnected)
        {
            // read IMU data and store it in QList
            dataprocessor.getIMUData(angles,axes,quat_temp);
            QList<float> qvector_temp;
            for (int i=0;i<SENSORNUM*4;i++)
                qvector_temp.append(quat_temp[i]);
            quatRaw.append(qvector_temp);
            emit newIMUData(angles,datacount);
        }
        if (EMGconnected)
        {
            // read EMG data and store it in QList
            dataprocessor.getEMGData(emgdata);
            QList<float> emgtmp;
            for (int i=0;i<ELECTRODENUM;i++)
                emgtmp.append(emgdata[i]);
            emgraw.append(emgtmp);
            emit newEMGData(emgdata,datacount);
        }
    }
    else
    {
        if (dataprocessor.IMUfileExists)
        {
            int retval = dataprocessor.getIMUDataFromFile(angles,axes,quat_temp);
            if (retval>=0)
                emit newIMUData(angles,datacount);
            else
                return -1;
        }
        if (dataprocessor.EMGfileExists)
        {
            int retval = dataprocessor.getEMGDataFromFile(emgdata);
            if (retval>=0)
                emit newEMGData(emgdata,datacount);
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
        //twistDeltas.append(angles[1]);
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
    //int retval=gestureRecognition(angles,axes);

    datacount++;

    return 0;
}
int Recognizor::gestureRecognition(const double angles[JOINTNUM],const double axes[AXISNUM][3])
{
    for (int joint=0;joint<JOINTNUM;joint++)
        for (int move=0;move<MOVEMENTNUM;move++)
            lastp[joint][move]=newp[joint][move];
    getmProbability(lasthead,datacount,newp,lastp,deltas,states);

#ifdef CONTROL
    int LINK_LENGTH=150;
    hx=-axes[UZ][0]*LINK_LENGTH-axes[FZ][0]*LINK_LENGTH;
    hy=-axes[UZ][1]*LINK_LENGTH-axes[FZ][1]*LINK_LENGTH;
    hz=-axes[UZ][2]*LINK_LENGTH-axes[FZ][2]*LINK_LENGTH;
#endif
    // todo: include emg result
    int ret=gesturelib.updateBestGesture(angles,axes,newp,0);
    if (ret==NEWGESTURE)
    {
        // if true, new best gesture is found
        if (gesturelib.getBestureGestureIndex()==-1)
            currentGesture=QString("");
        else
            currentGesture=gesturelib.getBestGestureName();
    }
    if (ret==GESTUREEND)
    {
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

int Recognizor::timerbegin()
{
    timer.start(40);
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
        for (int j=0;j<SENSORNUM*4;j++)
            txtOutput<<quatRaw[i][j]<<' ';
        txtOutput<<endl;
    }
    f.close();

    fname=QString("%1.emg").arg(filename);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
     printf("Open failed.");
     return -1;
    }
    QTextStream txtOutput1(&f);
    for (int i=0;i<emgraw.length();i++)
    {
        for (int j=0;j<ELECTRODENUM;j++)
            txtOutput1<<emgraw[i][j]<<' ';
        txtOutput1<<endl;
    }
    cwin->savePictures(filename);
    f.close();
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
    emgraw.clear();
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

int Recognizor::connectEMGSensor(QString portname)
{
    int retval=dataprocessor.connectEMGSensor(portname);
    EMGconnected=true;
    return retval;
}

int Recognizor::disconnectEMGSensor()
{
    dataprocessor.disconnectEMGSensor();
    EMGconnected=false;
    return 0;
}

bool Recognizor::isEMGConnected()
{
    return EMGconnected;
}

