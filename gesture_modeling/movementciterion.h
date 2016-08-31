#ifndef MOVEMENTCITERION_H
#define MOVEMENTCITERION_H
#include <QJsonObject>
#include "angleciterion.h"

#define MOVEMENTNUM 4

const char movementNames[MOVEMENTNUM+1][10]={"NM","FM","BM","RM","NULL"};

enum MovementType{
    NM,FM,BM,RM,NOMOVEMENT
};

class MovementCiterion
{
public:
    MovementCiterion();
    MovementCiterion(const Joint joint, MovementType move);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool update(const Joint &joint, const MovementType &move);

    Joint joint() const;
    MovementType move() const;

    QString getCiterionString() const;
private:
    Joint mName;
    MovementType mMove;
};


#endif // MOVEMENTCITERION_H
