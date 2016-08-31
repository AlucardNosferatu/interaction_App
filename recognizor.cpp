#include "recognizor.h"

Recognizor::Recognizor()
{

}

QString Recognizor::getCurrentGesture()
{
    return currentGesture;
}

int Recognizor::update(bool FileMode, double *angles, double axes[][3])
{
    double quat_temp[SENSORNUM*4];
    if (!FileMode)
    {
        dataprocessor.getData(angles,axes,quat_temp);
        QVector<double> qvector_temp;
        for (int i=0;i<SENSORNUM*4;i++)
            qvector_temp.append(quat_temp[i]);
        quatRaw.append(qvector_temp);
    }
    else
    {
        int retval = dataprocessor.getDataFromFile(angles,axes,quat_temp);
        if (retval==-1)
            return -1;
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
            angles[ELB]-=2*3.1415926;
        if (angles[ELB]-lastangles[ELB]<-4)
            angles[ELB]+=2*3.1416926;
        if (angles[TWI]-lastangles[TWI]>4)
            angles[TWI]-=2*3.1415926;
        if (angles[TWI]-lastangles[TWI]<-4)
            angles[TWI]+=2*3.1415926;
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
    int retval=gestureRecognition(angles,axes);

    datacount++;

    if (datacount %10==0)
    {
        //do the control things
#ifdef CONTROL
        QByteArray writedate;
        QString writestr;
        //writestr.append(QString("{X%1 Y%2 Z%3 D0 E0 G0 S}").arg((int)hy).arg((int)-hx).arg((int)hz));
        writestr.append(QString("{%1}").arg(gestureName[gestures.last()]));
        writedate.append(writestr);
        spWriter.write(writedate);
        ui->controlMsg->clear();
        ui->controlMsg->appendPlainText(writestr);
#endif
    }
    return retval;
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

    int ret=gesturelib.updateBestGesture(angles,axes,newp);
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
    dataprocessor.resetFileStream(fileName);
    datacount=0;
    lasthead=0;
    return 0;
}

int Recognizor::setReplayProcess(int pos)
{
    startpoint=pos;
    dataprocessor.setFilePos(startpoint);
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

int Recognizor::initialRealtimeRecognition()
{
    startpoint=0;
    datacount=0;
    lasthead=0;
    return 0;
}

int Recognizor::saveData(const QString &filename)
{
    QFile f(filename);
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
    return 0;
}

int Recognizor::loadFile(QString fileName)
{
    QString path=QFileInfo(fileName).path();
    QString name=QFileInfo(fileName).baseName();
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

int Recognizor::connectSensor(int interval)
{
    dataprocessor.initiate(50);
    return 0;
}

int Recognizor::disconnectSensor()
{
    dataprocessor.disconnect();
    return 0;
}

