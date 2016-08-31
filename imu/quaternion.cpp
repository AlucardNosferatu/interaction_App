#include "quaternion.h"
#define max(a,b)  (a>b?a:b)
#define min(a,b)  (a<b?a:b)
Vec3::Vec3()
{
    e[0]=0;
    e[1]=0;
    e[2]=0;
    norm=0;
}
Vec3::~Vec3()
{

}

Vec3::Vec3(float a, float b, float c)
{
    e[0]=a;
    e[1]=b;
    e[2]=c;
    norm=sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
}
void Vec3::operator=(const Vec3 &a)
{
    e[0]=a.e[0];
    e[1]=a.e[1];
    e[2]=a.e[2];
    norm=sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
}
Vec3 Vec3::operator *(const float a)
{
    return Vec3(a*e[0],a*e[1],a*e[2]);
}


Vec3 Vec3::operator /(const float a)
{
    return Vec3(e[0]/a,e[1]/a,e[2]/a);
}

float Vec3::dot (const Vec3 &a)
{
    return a.e[0]*e[0]+a.e[1]*e[1]+a.e[2]*e[2];
}

float Vec3::getNorm()
{
    this->norm=sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
    return this->norm;
}

Vec3 Vec3::operator +(const Vec3 &a)
{
    return Vec3(e[0]+a.e[0], e[1]+a.e[1], e[2]+a.e[2]);
}
Vec3 Vec3::operator -(const Vec3 &a)
{
    return Vec3(e[0]-a.e[0], e[1]-a.e[1], e[2]-a.e[2]);
}

Vec3 Vec3::cross(const Vec3 &a)
{
    float t1,t2,t3;
    t1=e[1]*a.e[2]-e[2]*a.e[1];
    t2=e[2]*a.e[0]-e[0]*a.e[2];
    t3=e[0]*a.e[1]-e[1]*a.e[0];
    return Vec3(t1,t2,t3);
}
void Vec3::printVec3()
{
    std::cout<<std::setw(15)<<e[0]<<' '<<std::setw(15)<<e[1]<<' '<<std::setw(15)<<e[2]<<std::endl;
}

void Vec3::normalize()
{
    e[0]/=norm;
    e[1]/=norm;
    e[2]/=norm;
}

float Vec3::getNormest()
{
    return norm;
}
float Vec3::getAngle(const Vec3 &a)
{
    float a1=this->dot(a);
    return acos(a1);
    return a1;
}

float Vec3::getAngle2(const Vec3 &a)
{
    //x-y plane rotation
    Vec3 tmp=this->cross(a);
    float ans=getAngle(a);
    if (tmp.e[2]>0)
        return ans*-1;
    else
        return ans;
}

MyQuaternion::MyQuaternion(float neww, Vec3 newe)
{
    w=neww;
    e=newe;
}

MyQuaternion::MyQuaternion()
{
    w=0;
    e=Vec3(0,0,0);
}

MyQuaternion::MyQuaternion(float *data)
{
    w=data[3];
    e=Vec3(data[0],data[1],data[2]);
}

MyQuaternion::~MyQuaternion()
{

}

MyQuaternion::MyQuaternion(float qw, float qx, float qy, float qz)
{
    w=qw;
    e=Vec3(qx,qy,qz);
}

void MyQuaternion::normalize()
{
    float norm=sqrt(w*w+e.getNormest()*e.getNormest());
    w=w/norm;
    e=e/norm;
}

MyQuaternion MyQuaternion::operator*(const MyQuaternion &q)
{
    Vec3 te=q.e;
    return MyQuaternion(w*q.w-e.dot(q.e),te*w+e*q.w+e.cross(te));
}

MyQuaternion MyQuaternion::conjugate()
{
    return MyQuaternion(w,e*-1);
}

MyQuaternion MyQuaternion::inverse()
{
    float norm=sqrt(w*w+e.getNormest()*e.getNormest());
    return MyQuaternion(w/norm,e*(-1/norm));
}

void MyQuaternion::printQuaternion()
{
    if(w<0.00001)
        std::cout<<std::setw(7)<<0<<' ';
    else
        std::cout<<std::setw(7)<<w<<' ';
    e.printVec3();
}

//something wrong in this function
void MyQuaternion::getEuler(float *euler)
{
    euler[0] = atan2(2.0f * (w * e.e[0] + e.e[1] * e.e[2]),
                                   1.0f - 2.0f * (e.e[1] * e.e[1] + e.e[1] * e.e[1]));
    euler[1] = asin(max(-1.0f, min(1.0f, 2.0f * (w * e.e[1] - e.e[2] * e.e[1]))));
    euler[2] = atan2(2.0f * (w * e.e[2] + e.e[1] * e.e[1]),
                                1.0f - 2.0f * (e.e[1] * e.e[1] + e.e[2] * e.e[2]));
}

int MyQuaternion::set(float qw, float qx, float qy, float qz)
{
    w=qw;
    e.e[0]=qx;
    e.e[1]=qy;
    e.e[2]=qz;
    return 0;
}
