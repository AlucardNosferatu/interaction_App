#ifndef ANGLECITERION_H
#define ANGLECITERION_H
#include <QString>
#include <QJsonObject>

#define JOINTNUM 5

enum Joint{
    ELB,TWI,POL,AZI,OME,NEWJOINT
};
const char jointNames[JOINTNUM+1][10]={"ELBOW","TWIST","POLAR","AZIMUTHAL","OMEGA","NEW JOINT"};

class AngleCiterion
{
public:
    AngleCiterion();
    AngleCiterion(const Joint joint,double value);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool update(const Joint &joint, const double &value);

    Joint joint() const;
    double value() const;

    QString getCiterionString() const;
private:
    Joint mName;
    double mValue;
};

#endif // ANGLECITERION_H
