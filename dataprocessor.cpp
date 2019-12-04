#include "dataprocessor.h"
#include"qdebug"


DataProcessor::DataProcessor(QObject *parent) : QObject(parent)
{
    z.set(0,0,0,1);
    x.set(0,1,0,0);
    y.set(0,0,1,0);
    for (int i=0;i<JOINTNUM;i++)
        zeros[i]=0;
    direction = -1;
}

DataProcessor::~DataProcessor()
{

}

float DataProcessor::tare()
{
    TSS_Error tss_error;
    unsigned int timestamp;

    tss_error = tss_tareWithCurrentOrientation(upperArm,&timestamp);
    tss_error = tss_tareWithCurrentOrientation(foreArm,&timestamp);
	tss_error = tss_tareWithCurrentOrientation(wristHand,&timestamp);

    tss_getTaredOrientationAsQuaternion(upperArm,uquat,&timestamp);
    tss_getTaredOrientationAsQuaternion(foreArm,fquat,&timestamp);
	tss_getTaredOrientationAsQuaternion(wristHand,aquat,&timestamp);
    return 0;
}

int DataProcessor::setDirection(float d)
{
    direction=d;
    return 0;
}

void DataProcessor::connectIMU(int interval)
{
    TSS_Error tss_error;
    unsigned int timestamp;
	//tss_error=tss_setAxisDirections(body,000,NULL);
    foreArm  = tss_createTSDeviceStr("COM45",  TSS_TIMESTAMP_SENSOR);  //31 for hub 15 for usb2
    body     = tss_createTSDeviceStr("COM43", TSS_TIMESTAMP_SENSOR);    //25 for hub, 12 for usb2 COM30
    upperArm = tss_createTSDeviceStr("COM44", TSS_TIMESTAMP_SENSOR); //30 for hub 16for usb2
	//wristHand = tss_createTSDeviceStr("COM26", TSS_TIMESTAMP_SENSOR); //30 for hub 16for usb2||COM26||COM27
	
  
    TSS_Stream_Command stream_slots[8] = { TSS_GET_UNTARED_ORIENTATION_AS_QUATERNION,TSS_GET_CORRECTED_ACCELEROMETER_VECTOR,TSS_NULL, TSS_NULL,TSS_NULL,TSS_NULL,TSS_NULL,TSS_NULL};

    tss_setStreamingSlots(foreArm, stream_slots, NULL);
	
    tss_error=tss_setStreamingTiming(foreArm,interval*1000,TSS_INFINITE_DURATION,0,NULL);
    while(tss_error)
        tss_error=tss_setStreamingTiming(foreArm,interval*1000,TSS_INFINITE_DURATION,0,NULL);

    tss_error=tss_startStreaming(foreArm,NULL);
    while(tss_error)
    {
        Sleep(10);
        tss_error=tss_startStreaming(foreArm,NULL);
    }

	
    tss_setStreamingSlots(body, stream_slots, NULL);
    tss_error=tss_setStreamingTiming(body,interval*1000,TSS_INFINITE_DURATION,0,NULL);
    while(tss_error)
        tss_error=tss_setStreamingTiming(body,interval*1000,TSS_INFINITE_DURATION,0,NULL);
    tss_error=tss_startStreaming(body,NULL);
    while(tss_error)
    {
        Sleep(10);
        tss_error=tss_startStreaming(body,NULL);
    }

    tss_setStreamingSlots(upperArm, stream_slots, NULL);
    tss_error=tss_setStreamingTiming(upperArm,interval*1000,TSS_INFINITE_DURATION,0,NULL);
    while(tss_error)
        tss_error=tss_setStreamingTiming(upperArm,interval*1000,TSS_INFINITE_DURATION,0,NULL);
    tss_error=tss_startStreaming(upperArm,NULL);
    while(tss_error)
    {
        Sleep(10);
        tss_error=tss_startStreaming(upperArm,NULL);
    }
	/* tss_setStreamingSlots(wristHand, stream_slots, NULL);
	tss_error=tss_setStreamingTiming(wristHand,interval*1000,TSS_INFINITE_DURATION,0,NULL);
    while(tss_error)
        tss_error=tss_setStreamingTiming(wristHand,interval*1000,TSS_INFINITE_DURATION,0,NULL);

    tss_error=tss_startStreaming(wristHand,NULL);
    while(tss_error)
    {
        Sleep(10);
        tss_error=tss_startStreaming(wristHand,NULL);
    }
    //QueryPerformanceCounter(&t1);
	*/
    twist=0;
}
int DataProcessor::setZeros(double *angles)
{
    for (int i=0;i<JOINTNUM;i++)
        zeros[i]=angles[i];
    return 0;
}

void DataProcessor::disconnectIMU()
{
    tss_stopStreaming(upperArm,NULL);
    tss_stopStreaming(foreArm,NULL);
    tss_stopStreaming(body,NULL);
	tss_stopStreaming(wristHand,NULL);
    tss_closeTSDevice(upperArm);
    tss_closeTSDevice(foreArm);
    tss_closeTSDevice(body);
	 tss_closeTSDevice(wristHand);
}

int DataProcessor::getIMUData(float *angles, float axes[AXISNUM][3], float *quatRaw,float*accel)
{
    TSS_Error tss_error;
    unsigned int timestamp;

    //for integration
    farm0=MyQuaternion(fquat[3],fquat[0],fquat[1],fquat[2]);

    tss_error = tss_getLastStreamData(body, (char*)&bquat,sizeof(bquat),&timestamp);
    tss_error = tss_getLastStreamData(foreArm, (char*)&fquat,sizeof(fquat), &timestamp);
    tss_error = tss_getLastStreamData(upperArm,(char*)&uquat,sizeof(uquat),&timestamp);
	 tss_error = tss_getLastStreamData(wristHand,(char*)&aquat,sizeof(aquat),&timestamp);
    if (axes==NULL && quatRaw==NULL)
        processForCalibration(angles);
    else
    {
		//fquat[0]=faquat[0];fquat[1]=faquat[1];fquat[2]=faquat[2];fquat[3]=faquat[3];
        //body
        quatRaw[0]=bquat[0];quatRaw[1]=bquat[1];quatRaw[2]=bquat[2];quatRaw[3]=bquat[3];
        //upperarm
        quatRaw[4]=uquat[0];quatRaw[5]=uquat[1];quatRaw[6]=uquat[2];quatRaw[7]=uquat[3];
        //forearm
        quatRaw[8]=fquat[0];quatRaw[9]=fquat[1];quatRaw[10]=fquat[2];quatRaw[11]=fquat[3];
		//accel of forearm
		quatRaw[12]=fquat[4];quatRaw[13]=fquat[5];quatRaw[14]=fquat[6];quatRaw[15] = aquat[0];
		quatRaw[16]=aquat[1];quatRaw[17] = aquat[2];quatRaw[18] = aquat[3];
		accel[0]=quatRaw[12];accel[1]=quatRaw[13];accel[2]=quatRaw[14];
        process(angles,axes,accel);
    }
    return 0;
}

int DataProcessor::getZeros(float *angles)
{
    TSS_Error tss_error;
    unsigned int timestamp;
    tss_error = tss_getLastStreamData(foreArm, (char*)&fquat,sizeof(fquat), &timestamp);
    tss_error = tss_getLastStreamData(upperArm,(char*)&uquat,sizeof(uquat), &timestamp);
    process(angles,NULL,NULL);
    return 0;
}

int DataProcessor::resetFileStream(QString fname)
{
    // reset both IMU file and EMG file
    IMUfileExists=false;
    EMGfileExists=false;

    QFileInfo fi(fname);

    QString abpath=fi.absolutePath();
    QString fn=fi.baseName();

    QString IMUfname=abpath+"/"+fn+".imu";
    QFileInfo imufi(IMUfname);
    if (imufi.exists())
    {
        IMUfileExists=true;
        if (IMUinfile.isOpen())
            IMUinfile.close();
        IMUfilePos=0;
        IMUinfile.setFileName(IMUfname);
        if(!IMUinfile.open( QIODevice::ReadOnly | QIODevice::Text))
            return -1;
        IMUtextinput.setDevice(&IMUinfile);
    }

    QString EMGfname=abpath+"/"+fn+".emg";
    QFileInfo emgfi(EMGfname);
    if (emgfi.exists())
    {
        EMGfileExists=true;
        if (EMGinfile.isOpen())
            EMGinfile.close();
        EMGfilePos=0;
        EMGinfile.setFileName(EMGfname);
        if(!EMGinfile.open( QIODevice::ReadOnly | QIODevice::Text))
            return -1;
        EMGtextinput.setDevice(&EMGinfile);
    }
    return 0;
}

int DataProcessor::getFileLineNum()
{
    int linenum=0;
    if (IMUfileExists)
    {
        while (!IMUtextinput.atEnd())
        {
             IMUtextinput.readLine();
             linenum++;
        }
    }else
    {
        while (!EMGtextinput.atEnd())
        {
             EMGtextinput.readLine();
             linenum++;
        }
    }
    return linenum;
}

int DataProcessor::setFilePos(int newpos)
{
    if (IMUfileExists)
    {
        IMUinfile.seek(0);
        for (int i=0;i<newpos;i++)
            IMUinfile.readLine();
        IMUfilePos=IMUinfile.pos();
    }
    if (EMGfileExists)
    {
        EMGinfile.seek(0);
        for (int i=0;i<newpos;i++)
            EMGinfile.readLine();
        EMGfilePos=EMGinfile.pos();
    }
    return 0;
}

int DataProcessor::getIMUDataFromFile(float *angles, float axes[][3], float *quatRaw,float*accel)
{
    if (IMUfileExists)
    {
        farm0=MyQuaternion(fquat[3],fquat[0],fquat[1],fquat[2]);
        IMUtextinput.seek(IMUfilePos);
        IMUtextinput>>bquat[0]>>bquat[1]>>bquat[2]>>bquat[3]
                >>uquat[0]>>uquat[1]>>uquat[2]>>uquat[3]
                >>fquat[0]>>fquat[1]>>fquat[2]>>fquat[3]
				>>fquat[4]>>fquat[5]>>fquat[6];

        if(IMUtextinput.atEnd())
        {
            return -1;
        }
        IMUfilePos=IMUtextinput.pos();
        process(angles,axes,accel);
    }
    return 0;
}

int DataProcessor::getOrientation(float *vector,float *forward,float *right,float *up)
{
    Vec3 v(vector[0],vector[1],vector[2]);
    static Vec3 vectors[6]={Vec3(-1,0,0),Vec3(1,0,0),Vec3(0,0,1),Vec3(0,0,-1),
            Vec3(0,1,0),Vec3(0,-1,0)};
    static Vec3 leftvector(-1,0,0),rightvector(1,0,0),upvector(0,0,1),downvector(0,0,-1),
            forwardvector(0,1,0),backwardvector(0,-1,0);
    *forward=acos(v.dot(forwardvector));
    *right=acos(v.dot(rightvector));
    *up=acos(v.dot(upvector));
    float max=0,tmp;
    int ans=-1;
    for (int i=0;i<6;i++)
    {
        tmp=v.dot(vectors[i]);
        if (tmp>max)
        {
            max=tmp;
            ans=i;
        }
    }
    if (max>ORIENTATION_THRESHOLD)
        return ans;
    else
        return OTHERS_DIRECTION;
}


int DataProcessor::processForCalibration(float *angles)
{
    MyQuaternion fz,fx,fy,uz,ux,ux0,fx0,farmc,uarmc,uy,ax,ay,az,ax0,wristc;
    ux0=uarm.conjugate()*x*uarm;    //former xaxis
    fx0=farm.conjugate()*x*farm;
	ax0=wrist.conjugate()*x*wrist;
    qbody= MyQuaternion(bquat[3],bquat[0],bquat[1],bquat[2]);
    farm = MyQuaternion(fquat[3],fquat[0],fquat[1],fquat[2]);
    uarm = MyQuaternion(uquat[3],uquat[0],uquat[1],uquat[2]);
	wrist = MyQuaternion(aquat[3],aquat[0],aquat[1],aquat[2]);

	
    qbody=qbody.conjugate();
    farm=qbody*farm;
    uarm=qbody*uarm;
	wrist=qbody*wrist;
    farmc=farm.conjugate();
    uarmc=uarm.conjugate();
	wristc=wrist.conjugate();

    fz=farm*z*farmc;
    fx=farm*x*farmc;
    fy=farm*y*farmc;

    uz=uarm*z*uarmc;
    ux=uarm*x*uarmc;
    uy=uarm*y*uarmc;

	az=wrist*z*wristc;
	ax=wrist*x*wristc;
	ay=wrist*y*wristc;

    //angles=[epsilon,tau,theta,phi,omega]
    //angles=[elbow,twist,polar,amuzithal,utwist]
    angles[0]=getElbowAngle(uz,fz);
    angles[1]=getTwistAngle(ux,fx,uz,angles[0]);  //ftwist

    //shoulder
    angles[2]=getPolarAngle(uz,ux); //polar
    angles[3]=getAziAngle(uz);//azimuthal
    angles[4]=getOmegaAngle(uy,angles[2],angles[3]);

    return 0;
}

int DataProcessor::process(float *angles, float axes[AXISNUM][3],float*accel)
{
    MyQuaternion fz,fx,fy,uz,ux,ux0,fx0,farmc,uarmc,uy,q1,q2,q3,q1c,q2c,q3c,q4,ax,ay,az,ax0,wristc;
    ux0=uarm.conjugate()*x*uarm;    //former xaxis
    fx0=farm.conjugate()*x*farm;

    qbody= MyQuaternion(bquat[3],bquat[0],bquat[1],bquat[2]);
    farm = MyQuaternion(fquat[3],fquat[0],fquat[1],fquat[2]);
    uarm = MyQuaternion(uquat[3],uquat[0],uquat[1],uquat[2]);
	wrist = MyQuaternion(aquat[3],aquat[0],aquat[1],aquat[2]);

	accel[0]=fquat[4];accel[1]=fquat[5];accel[2]=fquat[6];
/*	q1= MyQuaternion(0.614307,0.0188239,0.788762,-0.0112587);//相对坐标转换
	q2= MyQuaternion(0.671501,0.006259,-0.740751,-0.0183077);
	q3= MyQuaternion(-0.417578,-0.0220954,-0.906284,-0.417578);
	q1c=q1.conjugate();
	q2c=q2.conjugate();
	q3c=q3.conjugate();
	qbody=qbody*q2c*q3;
	farm=farm*q1c*q3;
	*/
    qbody=qbody.conjugate();
    farm=qbody*farm;
    uarm=qbody*uarm;
	wrist = qbody*wrist;
    farmc=farm.conjugate();
    uarmc=uarm.conjugate();
	wristc=wrist.conjugate();
	q4=MyQuaternion(0,0,0,0);
    fz=farm*z*farmc;
    fx=(farm*x*farmc);
    fy=farm*y*farmc;
	
    uz=uarm*z*uarmc;
    ux=uarm*x*uarmc;
    uy=uarm*y*uarmc;

	az=wrist*z*wristc;
	ax=wrist*x*wristc;
	ay=wrist*y*wristc;

    if (axes!=NULL)
    {
        axes[0][0]=fx.e.e[0];
        axes[0][1]=direction*fx.e.e[1];
        axes[0][2]=fx.e.e[2];

        axes[1][0]=fy.e.e[0];
        axes[1][1]=direction*fy.e.e[1];
        axes[1][2]=direction*fy.e.e[2];

        axes[2][0]=direction*fz.e.e[0];
        axes[2][1]=fz.e.e[1];
        axes[2][2]=fz.e.e[2];

        axes[3][0]=direction*ux.e.e[0];
        axes[3][1]=ux.e.e[1];
        axes[3][2]=ux.e.e[2];

        axes[4][0]=direction*uy.e.e[0];
        axes[4][1]=uy.e.e[1];
        axes[4][2]=uy.e.e[2];

        axes[5][0]=direction*uz.e.e[0];
        axes[5][1]=uz.e.e[1];
        axes[5][2]=uz.e.e[2];

		axes[6][0]=ax.e.e[0];
        axes[6][1]=direction*ax.e.e[1];
        axes[6][2]=ax.e.e[2];

        axes[7][0]=ay.e.e[0];
        axes[7][1]=direction*ay.e.e[1];
        axes[7][2]=direction*ay.e.e[2];

        axes[8][0]=direction*az.e.e[0];
        axes[8][1]=az.e.e[1];
        axes[8][2]=az.e.e[2];
    }


    //angles=[epsilon,tau,theta,phi,omega]
    //angles=[elbow,twist,polar,amuzithal,utwist]
    angles[0]=getElbowAngle(uz,fz)-zeros[0];
    angles[1]=getTwistAngle(ux,fx,uz,angles[0])-zeros[1];  //ftwist

    //shoulder
    angles[2]=getPolarAngle(uz,ux);//-zeros[2]; //polar
    angles[3]=getAziAngle(uz);//azimuthal
    if (angles[2]<0.5)
        angles[3]=0;
    angles[4]=getOmegaAngle(uy,angles[2],angles[3]);//-zeros[4];

    return 0;
}

double DataProcessor::getPolarAngle(MyQuaternion zu, MyQuaternion xu)
{
    MyQuaternion zb(0,0,0,1);
    return acos(zb.e.dot(zu.e));
}

double DataProcessor::getAziAngle(MyQuaternion zu)
{
    MyQuaternion xb(0,1,0,0);
    Vec3 uz2(-zu.e.e[0],-zu.e.e[1],0);
    uz2.normalize();
    return acos(xb.e.dot(uz2));
}

double DataProcessor::getElbowAngle(MyQuaternion uz, MyQuaternion fz)
{
    float retval=acos(uz.e.dot(fz.e));
    return retval;
}
double DataProcessor::getOmegaAngle(MyQuaternion uy, double polar, double azi)
{
    MyQuaternion t(cos(polar/2),Vec3(0,0,1)*sin(polar/2));
    MyQuaternion bx=t*x*t.conjugate();
    t.set(cos(azi/2),sin(azi/2),0,0);
    bx=t*bx*t.conjugate();
    float retval=acos(bx.e.dot(uy.e));
    return retval;
}

double DataProcessor::getTwistAngle(MyQuaternion ux,MyQuaternion fx,MyQuaternion uz,double elbow)
{
    MyQuaternion t(cos(elbow/2),ux.e*sin(elbow/2));
    ux=t*ux*t.conjugate();
    MyQuaternion uz1=t*uz*t.conjugate();
    float retval=acos(ux.e.dot(fx.e)*direction);
    if ((ux.e.cross(fx.e*direction).dot(uz1.e))<0)
        retval*=-1;
    return retval;
}
