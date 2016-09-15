#ifndef GESTURE_H
#define GESTURE_H

#include<QJsonObject>
#include<QJsonArray>
#include<QList>
#include "angleciterion.h"
#include "axisciterion.h"
#include "movementciterion.h"
#include "math.h"


class Gesture
{
public:
    Gesture();
    Gesture(const QString &name);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    //CRUD function
    QString name() const;
    QString command() const;
    bool updateGesture(QString name,QString command,QString description);
    QString description() const;

    AxisCiterion getAxisCiterionAt(const int &index) const;
    void addAxisCiterion(const Axes name,double x,double y, double z);
    bool removeAxisCiterionAt(const int &index);
    bool updateAxisCiterionAt(const int &index,const Axes name,const double &x, const double &y, const double &z);

    AngleCiterion getAngleCiterionAt(const int &index) const;
    void addAngleCiterion(const Joint name,double value);
    bool removeAngleCiterionAt(const int &index);
    bool updateAngleCiterionAt(const int &index, const Joint &name, const double &value);

    MovementCiterion getMoveCiterionAt(const int &index) const;
    void addMovementCiterion(const Joint name, MovementType move);
    bool removeMovementCiterionAt(const int &index);
    bool updateMovementCiterionAt(const int &index, const Joint &name, const MovementType move);

    bool setEMGCiterion(int newEMG);
    int getEMGGesture();


    //list function
    QStringList getAxisCiteriaList();
    QStringList getAngleCiteriaList();
    QStringList getMoveCiteriaList();

    //likelihood
    double getLikelihood(const double angles[JOINTNUM], const double axes[AXISNUM][3], const double mprobability[JOINTNUM][MOVEMENTNUM], int emg);

private:
    QString mName;
    QString mCommand;
    QList<AxisCiterion> axisCiteria;
    QList<AngleCiterion> angleCiteria;
    QList<MovementCiterion> movementCiteria;
    int emgCiterion;
    QString mDescription;
};


#endif // GESTURE_H
