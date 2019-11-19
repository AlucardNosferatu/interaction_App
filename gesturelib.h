#ifndef GESTURELIB_H
#define GESTURELIB_H
#include "gesture_modeling/gesture.h"
#include <QJsonDocument>
#include <QFile>

#define SAMEGESTURE 0
#define NEWGESTURE 1
#define GESTUREEND 2


class GestureLib
{
public:
    GestureLib();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool saveLib(const QString &filename) const;
    bool loadLib(const QString &filename);

    // gesture, probability
    QString getBestGestureName();
    int updateBestGesture(const float *angles, const float axes[AXISNUM][3],
                          const double mprobability[JOINTNUM][4]);
    QString getBestGestureCommand();
    int getBestureGestureIndex();
    int resetGestureLikelihoods();

    int getGestureNumber() const;
    void addDefaultGestures();
    bool addEmptyGesture();
    bool removeGestureAt(const int &index);

    //list functions
    QStringList getGestureList() const;
    QStringList getGestureAxisCiteriaAt(const int &index);
    QStringList getGestureAngleCiteriaAt(const int &index);
    QStringList getGestureMoveCiteriaAt(const int &index);
    Gesture & getGestureAt(const int &index);

    //test functions
    void testWrite(const QString &filename);
    void testRead();
private:
    int numGesture;
    int currentBestIndex;
    QList<Gesture> gestures;
    double probabilities[30];
};


#endif // GESTURELIB_H
