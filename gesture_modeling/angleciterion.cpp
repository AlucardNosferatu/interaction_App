#include "angleciterion.h"


AngleCiterion::AngleCiterion()
{

}

AngleCiterion::AngleCiterion(const Joint name, double value)
{
    mName=name;
    mValue=value;
}

void AngleCiterion::read(const QJsonObject &json)
{
    mName=Joint(qRound(json["name"].toDouble()));
    mValue=json["value"].toDouble();
}

void AngleCiterion::write(QJsonObject &json) const
{
    json["name"]=mName;
    json["value"]=mValue;
}

bool AngleCiterion::update(const Joint &name, const double &value)
{
    mName=name;
    mValue=value;
    return true;
}

Joint AngleCiterion::joint() const
{
    return mName;
}

double AngleCiterion::value() const
{
    return mValue;
}

QString AngleCiterion::getCiterionString() const
{

    return QString("%1     %2").arg(jointNames[mName]).arg(mValue);
}
