#ifndef QUATERNION
#define QUATERNION
#include <iostream>
#include <iomanip>

class Vec3
{

    public:
        float e[3],norm;
        Vec3();
        Vec3(float a,float b,float c);
        ~Vec3();
        void operator= (const Vec3 &a);
        Vec3 operator* (const float a);
//        Vec3 operator* (const int a);
        Vec3 operator/ (const float a);
        Vec3 operator+ (const Vec3 &a);
        Vec3 operator- (const Vec3 &a);
        Vec3 cross(const Vec3 &a);
        float dot (const Vec3 &a);
        void normalize();
        float getNorm();
        float getNormest();
        float getAngle(const Vec3 &a);
        float getAngle2(const Vec3 &a);
        void printVec3();
};

class MyQuaternion
{
    //class variables
    float w,s;


    public:
    Vec3 e;

    MyQuaternion();
    MyQuaternion(float neww,Vec3 newe);
    MyQuaternion(float qw, float qx,float qy,float qz);
    MyQuaternion(float* data);
    ~MyQuaternion();


    // math operations
    void normalize();
    MyQuaternion operator*(const MyQuaternion &q);
    MyQuaternion conjugate();
    MyQuaternion inverse();

    // translate to euler angle or rotation matrix
    void getEuler(float *euler);

    // get change
    void getChange(const MyQuaternion *q0);

    // print
    void printQuaternion();

    int set(float qw, float qx,float qy,float qz);
};
#endif // QUATERNION

