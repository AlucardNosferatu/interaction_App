#include "movementciterion.h"



MovementCiterion::MovementCiterion()
{

}

MovementCiterion::MovementCiterion(const Joint name, MovementType move)
{
    mName=name;
    mMove=move;
}

void MovementCiterion::read(const QJsonObject &json)
{
    mName=Joint(qRound(json["name"].toDouble()));
    mMove=MovementType(qRound(json["move"].toDouble()));
}

void MovementCiterion::write(QJsonObject &json) const
{
    json["name"]=mName;
    json["move"]=mMove;
}

bool MovementCiterion::update(const Joint &name, const MovementType &move)
{
    mName=name;
    mMove=move;
    return true;
}

Joint MovementCiterion::joint() const
{
    return mName;
}

MovementType MovementCiterion::move() const
{
    return mMove;
}
QString MovementCiterion::getCiterionString() const
{
    return QString("%1     %2").arg(jointNames[mName]).arg(movementNames[mMove]);
}
