#include "dataprocessor.h"

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
    //零位
    tss_error = tss_tareWithCurrentOrientation(upperArm,&timestamp);
    tss_error = tss_tareWithCurrentOrientation(foreArm,&timestamp);

    tss_getTaredOrientationAsQuaternion(upperArm,uquat,&timestamp);
    tss_getTaredOrientationAsQuaternion(foreArm,fquat,&timestamp);
    return 0;
}

int DataProcessor::setDirection(float d)
{
    direction=d;
    return 0;
}

void DataProcessor::initiate(int interval)
{
    TSS_Error tss_error;
    unsigned int timestamp;

    foreArm  = tss_createTSDeviceStr("COM31",  TSS_TIMESTAMP_SENSOR );  //31 for hub 15 for usb2
    body     = tss_createTSDeviceStr("COM25", TSS_TIMESTAMP_SENSOR);    //25 for hub, 12 for usb2
    upperArm = tss_createTSDeviceStr("COM30", TSS_TIMESTAMP_SENSOR); //30 for hub 16for usb2

    TSS_Stream_Command stream_slots[8] = { TSS_GET_UNTARED_ORIENTATION_AS_QUATERNION,TSS_NULL,TSS_NULL, TSS_NULL,TSS_NULL,TSS_NULL,TSS_NULL,TSS_NULL};

    tss_setStreamingSlots(foreArm, stream_slots, NULL);
    tss_error=tss_setStreamingTiming(foreArm,interval*1000,TSS_INFINITE_DURATION,0,NULL);
    while(tss_error)
        tss_error=tss_setStreamingTiming(foreArm,interval*1000,TSS_INFINITE_DURATION,0,NULL);
    printf("timing succeed");
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

    //QueryPerformanceCounter(&t1);
    twist=0;
}
int DataProcessor::setZeros(double *angles)
{
    for (int i=0;i<JOINTNUM;i++)
        zeros[i]=angles[i];
    return 0;
}

void DataProcessor::disconnect()
{
    tss_stopStreaming(upperArm,NULL);
    tss_stopStreaming(foreArm,NULL);
    tss_stopStreaming(body,NULL);
    tss_closeTSDevice(upperArm);
    tss_closeTSDevice(foreArm);
    tss_closeTSDevice(body);
}

int DataProcessor::getData(double *angles, double axes[AXISNUM][3], double *quatRaw)
{
    TSS_Error tss_error;
    unsigned int timestamp;

    //for integration
    farm0=MyQuaternion(fquat[3],fquat[0],fquat[1],fquat[2]);

    tss_error = tss_getLastStreamData(body, (char*)&bquat,sizeof(bquat),&timestamp);
    tss_error = tss_getLastStreamData(foreArm, (char*)&fquat,sizeof(fquat), &timestamp);
    tss_error = tss_getLastStreamData(upperArm,(char*)&uquat,sizeof(uquat),&timestamp);

    if (axes==NULL && quatRaw==NULL)
        processForCalibration(angles);
    else
    {
        //body
        quatRaw[0]=bquat[0];quatRaw[1]=bquat[1];quatRaw[2]=bquat[2];quatRaw[3]=bquat[3];
        //upperarm
        quatRaw[4]=uquat[0];quatRaw[5]=uquat[1];quatRaw[6]=uquat[2];quatRaw[7]=uquat[3];
        //forearm
        quatRaw[8]=fquat[0];quatRaw[9]=fquat[1];quatRaw[10]=fquat[2];quatRaw[11]=fquat[3];
        process(angles,axes);
    }
    return 0;
}

int DataProcessor::getZeros(double *angles)
{
    TSS_Error tss_error;
    unsigned int timestamp;
    tss_error = tss_getLastStreamData(foreArm, (char*)&fquat,sizeof(fquat), &timestamp);
    tss_error = tss_getLastStreamData(upperArm,(char*)&uquat,sizeof(uquat), &timestamp);
    process(angles,NULL);
    return 0;
}

int DataProcessor::resetFileStream(QString fname)
{
    if (infile.isOpen())
        infile.close();
    fileName=fname;
    filePos=0;
    infile.setFileName(fileName);
    if(!infile.open( QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    textinput.setDevice(&infile);
    return 0;
}


int DataProcessor::getFileLineNum()
{
    int linenum=0;
    while (!textinput.atEnd())
    {
         textinput.readLine();
         linenum++;
    }
    return linenum;
}

int DataProcessor::setFilePos(int newpos)
{
    int linenum=0;
    infile.seek(0);
    for (int i=0;i<newpos;i++)
        infile.readLine();
    filePos=infile.pos();
    return 0;
}

int DataProcessor::getDataFromFile(double *angles, double axes[AXISNUM][3], double *quatRaw)
{
    farm0=MyQuaternion(fquat[3],fquat[0],fquat[1],fquat[2]);
    textinput.seek(filePos);    
    textinput>>bquat[0]>>bquat[1]>>bquat[2]>>bquat[3]
            >>uquat[0]>>uquat[1]>>uquat[2]>>uquat[3]
            >>fquat[0]>>fquat[1]>>fquat[2]>>fquat[3];

    if(textinput.atEnd())
    {
        return -1;
    }
    filePos=textinput.pos();
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    process(angles,axes);
    QueryPerformanceCounter(&t2);
    //printf("%f\n",(t2.QuadPart - t1.QuadPart)*1.0/tc.QuadPart);
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


int DataProcessor::processForCalibration(double *angles)
{
    MyQuaternion fz,fx,fy,uz,ux,ux0,fx0,farmc,uarmc,uy;
    ux0=uarm.conjugate()*x*uarm;    //former xaxis
    fx0=farm.conjugate()*x*farm;

    qbody= MyQuaternion(bquat[3],bquat[0],bquat[1],bquat[2]);
    farm = MyQuaternion(fquat[3],fquat[0],fquat[1],fquat[2]);
    uarm = MyQuaternion(uquat[3],uquat[0],uquat[1],uquat[2]);

    qbody=qbody.conjugate();
    farm=qbody*farm;
    uarm=qbody*uarm;
    farmc=farm.conjugate();
    uarmc=uarm.conjugate();

    fz=farm*z*farmc;
    fx=farm*x*farmc;
    fy=farm*y*farmc;

    uz=uarm*z*uarmc;
    ux=uarm*x*uarmc;
    uy=uarm*y*uarmc;

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

int DataProcessor::process(double *angles, double axes[AXISNUM][3])
{
    MyQuaternion fz,fx,fy,uz,ux,ux0,fx0,farmc,uarmc,uy;
    ux0=uarm.conjugate()*x*uarm;    //former xaxis
    fx0=farm.conjugate()*x*farm;

    qbody= MyQuaternion(bquat[3],bquat[0],bquat[1],bquat[2]);
    farm = MyQuaternion(fquat[3],fquat[0],fquat[1],fquat[2]);
    uarm = MyQuaternion(uquat[3],uquat[0],uquat[1],uquat[2]);

    qbody=qbody.conjugate();
    farm=qbody*farm;
    uarm=qbody*uarm;
    farmc=farm.conjugate();
    uarmc=uarm.conjugate();

    fz=farm*z*farmc;
    fx=farm*x*farmc;
    fy=farm*y*farmc;

    uz=uarm*z*uarmc;
    ux=uarm*x*uarmc;
    uy=uarm*y*uarmc;

    if (axes!=NULL)
    {
        axes[0][0]=direction*fx.e.e[0];
        axes[0][1]=direction*fx.e.e[1];
        axes[0][2]=direction*fx.e.e[2];

        axes[1][0]=direction*fy.e.e[0];
        axes[1][1]=direction*fy.e.e[1];
        axes[1][2]=direction*fy.e.e[2];

        axes[2][0]=fz.e.e[0];
        axes[2][1]=fz.e.e[1];
        axes[2][2]=fz.e.e[2];

        axes[3][0]=ux.e.e[0];
        axes[3][1]=ux.e.e[1];
        axes[3][2]=ux.e.e[2];

        axes[4][0]=uy.e.e[0];
        axes[4][1]=uy.e.e[1];
        axes[4][2]=uy.e.e[2];

        axes[5][0]=uz.e.e[0];
        axes[5][1]=uz.e.e[1];
        axes[5][2]=uz.e.e[2];
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
