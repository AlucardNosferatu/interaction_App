#include "gesture.h"

//Functions of class Gesture
Gesture::Gesture()
{

}

Gesture::Gesture(const QString &name)
{
    mName=name;
}

QString Gesture::name() const
{
    return mName;
}

QString Gesture::command() const
{
    return mCommand;
}

void Gesture::read(const QJsonObject &json)
{
    axisCiteria.clear();
    angleCiteria.clear();
    movementCiteria.clear();

    mName=json["name"].toString();
    mCommand=json["command"].toString();
    mDescription=json["description"].toString();
    QJsonArray axisArray=json["axisCiteria"].toArray();
    for (int i=0;i<axisArray.size();i++)
    {
        QJsonObject axisObject=axisArray[i].toObject();
        AxisCiterion citerion;
        citerion.read(axisObject);
        axisCiteria.append(citerion);
    }
    QJsonArray angleArray=json["angleCiteria"].toArray();
    for (int i=0;i<angleArray.size();i++)
    {
        QJsonObject angleObject=angleArray[i].toObject();
        AngleCiterion citerion;
        citerion.read(angleObject);
        angleCiteria.append(citerion);
    }
    QJsonArray movementArray=json["movementCiteria"].toArray();
    for (int i=0;i<movementArray.size();i++)
    {
        QJsonObject movementObject=movementArray[i].toObject();
        MovementCiterion citerion;
        citerion.read(movementObject);
        movementCiteria.append(citerion);
    }
    emgCiterion=json["EMG"].toInt();
}

void Gesture::write(QJsonObject &json) const
{
    json["name"]=mName;
    json["command"]=mCommand;
    json["description"]=mDescription;
    QJsonArray axisArray;
    foreach (const AxisCiterion citerion,axisCiteria)
    {
        QJsonObject axisObject;
        citerion.write(axisObject);
        axisArray.append(axisObject);
    }
    json["axisCiteria"]=axisArray;

    QJsonArray angleArray;
    foreach (const AngleCiterion citerion, angleCiteria)
    {
        QJsonObject angleObject;
        citerion.write(angleObject);
        angleArray.append(angleObject);
    }
    json["angleCiteria"]=angleArray;

    QJsonArray movementArray;
    foreach (const MovementCiterion citerion, movementCiteria)
    {
        QJsonObject movementObject;
        citerion.write(movementObject);
        movementArray.append(movementObject);
    }
    json["movementCiteria"]=movementArray;
    json["EMG"]=emgCiterion;
}

//CRUD functions
bool Gesture::updateGesture(QString name, QString command, QString description)
{
    mName=name;
    mCommand=command;
    mDescription=description;
    return true;
}

QString Gesture::description() const
{
    return mDescription;
}

AxisCiterion Gesture::getAxisCiterionAt(const int &index) const
{
    return axisCiteria[index];
}

void Gesture::addAxisCiterion(const Axes name, double x, double y, double z)
{
    AxisCiterion a(name,x,y,z);
    axisCiteria.append(a);
}

bool Gesture::removeAxisCiterionAt(const int &index)
{
    if (index>=0 && index<axisCiteria.size())
    {
        axisCiteria.removeAt(index);
        return true;
    }
    else
        return false;
}

bool Gesture::updateAxisCiterionAt(const int &index, const Axes name, const double &x, const double &y, const double &z)
{
    if (index>=0 && index<axisCiteria.size())
        return axisCiteria[index].update(name,x,y,z);
    else
         return false;
}

AngleCiterion Gesture::getAngleCiterionAt(const int &index) const
{
    return angleCiteria[index];
}

void Gesture::addAngleCiterion(const Joint name, double value)
{
    AngleCiterion a(name,value);
    angleCiteria.append(a);
}

bool Gesture::removeAngleCiterionAt(const int &index)
{
    if (index>=0 && index<angleCiteria.size())
    {
        angleCiteria.removeAt(index);
        return true;
    }
    else
        return false;
}

bool Gesture::updateAngleCiterionAt(const int &index, const Joint &name, const double &value)
{
    if (index>=0 && index<angleCiteria.size())
        return angleCiteria[index].update(name,value);
    else
        return false;
}

MovementCiterion Gesture::getMoveCiterionAt(const int &index) const
{
    return movementCiteria[index];
}
void Gesture::addMovementCiterion(const Joint name, MovementType move)
{
    MovementCiterion m(name,move);
    movementCiteria.append(m);
}

bool Gesture::removeMovementCiterionAt(const int &index)
{
    if (index>=0 && index<movementCiteria.size())
    {
        movementCiteria.removeAt(index);
        return true;
    }
    else
        return false;
}

bool Gesture::updateMovementCiterionAt(const int &index, const Joint &name, const MovementType move)
{
    if (index>=0 && index<movementCiteria.size())
        return movementCiteria[index].update(name,move);
    else
        return false;
}

bool Gesture::setEMGCiterion(int newEMG)
{
    emgCiterion=newEMG;
    return true;
}

int Gesture::getEMGGesture()
{
    return emgCiterion;
}

//list function
QStringList Gesture::getAxisCiteriaList()
{
    QStringList list;
    for (int index=0;index<axisCiteria.size();index++)
        list<<axisCiteria[index].getCiterionString();
    return list;
}

QStringList Gesture::getAngleCiteriaList()
{
    QStringList list;
    for (int index=0;index<angleCiteria.size();index++)
        list<<angleCiteria[index].getCiterionString();
    return list;
}

QStringList Gesture::getMoveCiteriaList()
{
    QStringList list;
    for (int index=0;index<movementCiteria.size();index++)
        list<<movementCiteria[index].getCiterionString();
    return list;
}

//likelihood function
double Gesture::getLikelihood(const double angles[JOINTNUM],const double axes[AXISNUM][3],const double mprobability[JOINTNUM][MOVEMENTNUM],int emg)
{
    double p=1;
    for (int i=0;i<angleCiteria.size();i++)
    {
        p=p*cos(angles[angleCiteria[i].joint()]-angleCiteria[i].value());
        if (p<0)
            return 0;
    }
    for (int i=0;i<axisCiteria.size();i++)
    {
        Axes a=axisCiteria[i].axis();
        p=p*(axes[a][0]*axisCiteria[i].x()+axes[a][1]*axisCiteria[i].y()+axes[a][2]*axisCiteria[i].z());
        if (p<0)
            return 0;
    }

    for (int i=0;i<movementCiteria.size();i++)
    {
        p=p*mprobability[movementCiteria[i].joint()][movementCiteria[i].move()];
        if (p<0)
            return 0;
    }

    if (p<0.5 || (emgCiterion!=0 && emg!=emgCiterion))
        p=0;
    else
        p=pow(p,1.0/(angleCiteria.size()+axisCiteria.size()+movementCiteria.size()));
    return p;
}

