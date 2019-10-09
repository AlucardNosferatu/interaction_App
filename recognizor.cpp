#include "recognizor.h"
extern int i = 0;
Recognizor::Recognizor()
{
    EMGconnected=false;
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
    float emgdata[ELECTRODENUM];

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

    float emglikelihoods[3];
    EMGrecognition(emgdata,emglikelihoods);
//    if (emglikelihoods[1]>0.66)
//    {
//        emit newGesture(QString("Fist!"));
//        qDebug()<<emglikelihoods[1];
//    }

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
    int retval=gestureRecognition(angles,axes,emglikelihoods);

    datacount++;

    return 0;
}
int Recognizor::gestureRecognition(const float angles[JOINTNUM], const float axes[AXISNUM][3], const float emg[ELECTRODENUM])
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

    //输出语音
    //voiceOutPut("这个很nice");

    for (int joint=0;joint<JOINTNUM;joint++)
        for (int move=0;move<MOVEMENTNUM;move++)
            lastp[joint][move]=newp[joint][move];
    getmProbability(lasthead,datacount,newp,lastp,deltas,states);
	//if(grasptest)
			//robot.motion_map( angles,axes);
    // todo: include emg result
    int ret=gesturelib.updateBestGesture(angles,axes,newp,emg);
    if (ret==NEWGESTURE)
    {
//        qDebug()<<"New Gesture";
        // if true, new best gesture is found
        if (gesturelib.getBestureGestureIndex()==-1)
        {
            emit newGesture(QString(""));
            currentGesture=QString("");
			//if(grasptest)
			//{
			//	robot.motion_map( angles,axes);
			//}
			
        }
        else
        {
            //qDebug()<<gesturelib.getBestGestureName();
            emit newGesture(gesturelib.getBestGestureName());
            currentGesture=gesturelib.getBestGestureName();

            if (robotConnected)
            {
                //ralsensor.closeSerialPort();
                //robot.openSerial(QString("COM17"));
                if (!grasptest)
                {
                    // navigation
                    if (gesturelib.getBestGestureCommand()=="SPEEDUP")
                    {
                        //qDebug()<<"speed up";
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
                    //if (gesturelib.getBestGestureCommand()=="SHRINK")
                    //    robot.postC();
                    if (gesturelib.getBestGestureCommand()=="STOP")
                        robot.move(0);
                    if (gesturelib.getBestGestureCommand()=="GETREADY")
                    {
                        emit changeToGrasp();
                        //robot.bend_initial();
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

    if (emgraw.length()>0)
    {
        fname=QString("%1.emg").arg(filename);
        f.setFileName(fname);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        {
         printf("Open failed.");
         return -1;
        }
        txtOutput.setDevice(&f);
        for (int i=0;i<emgraw.length();i++)
        {
            for (int j=0;j<ELECTRODENUM;j++)
                txtOutput<<emgraw[i][j]<<' ';
            txtOutput<<endl;
        }
        f.close();
        ralsensor.saveRawData(filename);
    }
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
    emgraw.clear();
    datacount=0;
    lasthead=0;
    for (int i=0;i<ELECTRODENUM;i++)
    {
        ban[i]=0;
        membership[i][0]=0;
        membership[i][1]=0;
        membership[i][2]=0;
    }
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

int Recognizor::EMGrecognition(float data[ELECTRODENUM],float result[3])
{
    static int idx[3][ELECTRODENUM]={{2,2,1,1,1,4,1,1},     // fist
                                     {4,4,4,0,0,5,5,5},     // wave in
                                     {0,0,0,0,1,2,2,2}};    // wave out


    int validNum=ELECTRODENUM;
    for (int i=0;i<ELECTRODENUM;i++)
    {
        if (data[i]>=MAXMAGNITUDE)
            ban[i]=25;
        else
            ban[i]--;

        if (ban[i]>0)
        {
            membership[i][0]=0;
            membership[i][1]=0;
            membership[i][2]=0;
            validNum--;
        }
        else{
            membership[i][0]=getLikelihood(data[i],-1e-4,-0.5e-4,0.2e-4,0.3e-4);
            membership[i][1]=getLikelihood(data[i],0.2e-4,0.5e-4,1.0e-4,1.4e-4);
            membership[i][2]=getLikelihood(data[i],1.1e-4,1.5e-4,100e-4,200e-4);
        }
    }

    // get likelihood for each gesture
    result[0]=0;
    result[1]=0;
    result[2]=0;

    if (validNum<=5)
        return 0;


    for (int c=0;c<ELECTRODENUM;c++)
        for (int g=0;g<3;g++)
        {
            if (idx[g][c]==4)
                result[g]+=membership[c][1]>membership[c][2]?membership[c][1]:membership[c][2];
            else if (idx[g][c]==5)
                result[g]+=membership[c][0]>membership[c][1]?membership[c][0]:membership[c][1];
            else
                result[g]+=membership[c][idx[g][c]];
        }
    for (int g=0;g<3;g++)
        result[g]/=validNum;
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

//int Recognizor::voiceOutPut(std::string voice)
//{
//    ISpVoice* pVoice = NULL;

//    if (FAILED(::CoInitialize(NULL)))
//        return FALSE;

//    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
//    if (SUCCEEDED(hr))
//    {
//        hr = pVoice->Speak(stringToLPCWSTR(voice), 0, NULL);
//        pVoice->Release();
//        pVoice = NULL;
//    }
//    std::cout << "done" << std::endl;
//    ::CoUninitialize();
//    return TRUE;
//}


//LPCWSTR Recognizor::stringToLPCWSTR(std::string orig)
//{
//    wchar_t *wcstring = 0;
//    try
//    {
//        size_t origsize = orig.length() + 1;
//        const size_t newsize = 100;
//        size_t convertedChars = 0;
//        if (orig == "")
//        {
//            wcstring = (wchar_t *)malloc(0);
//            mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
//        }
//        else
//        {
//            wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
//            mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
//        }
//    }
//    catch (std::exception e)
//    {
//    }
//    return wcstring;

//}
