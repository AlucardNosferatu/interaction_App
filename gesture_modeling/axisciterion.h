#ifndef AXISCITERION_H
#define AXISCITERION_H

#include <QJsonObject>

#define AXISNUM 9
const char axisNames[AXISNUM+1][10]={"FX","FY","FZ","UX","UY","UZ","NEW AXIS"};

enum Axes{
    FX,FY,FZ,UX,UY,UZ,NEWAXIS
};

class AxisCiterion
{
public:
    AxisCiterion();
    AxisCiterion(const Axes axis,double x,double y,double z);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool update(const Axes &axis, const double &x, const double &y, const double &z);

    Axes axis() const;
    double x() const;
    double y() const;
    double z() const;

    QString getCiterionString() const;
private:
    Axes mName;
    double mx,my,mz;
};

#endif // AXISCITERION_H
