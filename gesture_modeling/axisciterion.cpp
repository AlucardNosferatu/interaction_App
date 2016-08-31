#include "axisciterion.h"

AxisCiterion::AxisCiterion()
{

}

AxisCiterion::AxisCiterion(const Axes name, double x, double y, double z)
{
    mName=name;
    mx=x;
    my=y;
    mz=z;
}

Axes AxisCiterion::axis() const
{
    return mName;
}

double AxisCiterion::x() const
{
    return mx;
}

double AxisCiterion::y() const
{
    return my;
}

double AxisCiterion::z() const
{
    return mz;
}

void AxisCiterion::read(const QJsonObject &json)
{
    mName=Axes(qRound(json["name"].toDouble()));
    mx=json["x"].toDouble();
    my=json["y"].toDouble();
    mz=json["z"].toDouble();
    double norm=sqrt(mx*mx+my*my+mz*mz);
    mx=mx/norm;
    my=my/norm;
    mz=mz/norm;
}

void AxisCiterion::write(QJsonObject &json) const
{
    json["name"]=mName;
    json["x"]=mx;
    json["y"]=my;
    json["z"]=mz;
}

bool AxisCiterion::update(const Axes &name, const double &x, const double &y, const double &z)
{
    mName=name;
    mx=x;
    my=y;
    mz=z;
    double norm=sqrt(x*x+y*y+z*z);
    mx=mx/norm;
    my=my/norm;
    mz=mz/norm;
    return true;
}

QString AxisCiterion::getCiterionString() const
{
    return QString("%1     (%2,%3,%4)").arg(axisNames[mName]).arg(mx).arg(my).arg(mz);
}
