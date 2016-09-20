#include "gesturelib.h"
GestureLib::GestureLib()
{
    gestures.clear();
    numGesture=0;

}

void GestureLib::read(const QJsonObject &json)
{
    gestures.clear();
    QJsonArray gestureArray=json["gestures"].toArray();
    for(int i=0;i<gestureArray.size();i++)
    {
        Gesture g;
        g.read(gestureArray[i].toObject());
        gestures.append(g);
    }
    numGesture=gestures.size();
}

void GestureLib::write(QJsonObject &json) const
{
    QJsonArray gestureArray;
    foreach (const Gesture g,gestures)
    {
        QJsonObject gestureObject;
        g.write(gestureObject);
        gestureArray.append(gestureObject);
    }

    json["gestures"]=gestureArray;
}

bool GestureLib::saveLib(const QString &filename) const
{
    QFile saveFile(filename);

    if (!saveFile.open(QIODevice::WriteOnly)) {
         qWarning("Couldn't open save file.");
         return false;
     }

    QJsonObject libObject;
    this->write(libObject);
    QJsonDocument saveDoc(libObject);
    saveFile.write(saveDoc.toJson());

    return true;
}

bool GestureLib::loadLib(const QString &filename)
{
    QFile loadFile(filename);

    if (!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Couldn't open file.");
        return false;
    }

    QByteArray libData = loadFile.readAll();
    QJsonDocument libDoc(QJsonDocument::fromJson(libData));
    this->read(libDoc.object());
    return true;
}

int GestureLib::updateBestGesture(const float *angles, const float axes[6][3], const double mprobability[5][4],const float emg[EMGTYPENUM])
{
    double maxp=0;
    int newBestIndex=-1;

    // find the current best gesture for this data frame
    for (int i=0;i<gestures.size();i++)
    {
        double p=gestures[i].getLikelihood(angles,axes,mprobability,emg);
        if (p>maxp && p>0.8)
        {
            maxp=p;
            newBestIndex=i;
        }
    }

    // increase the probability of best gesture and decrease probabilities of others
    for (int i=0;i<gestures.size();i++)
    {
        if (i==newBestIndex){
            probabilities[i]+=0.1;
            if (maxp>probabilities[i])
                probabilities[i]=maxp;
        }else
            probabilities[i]-=0.1;
        if (probabilities[i]>1)
            probabilities[i]=1;
        if (probabilities[i]<0)
            probabilities[i]=0;
    }

    // find the gesture with the highest probability
    maxp=0;
    newBestIndex=-1;
    for (int i=0;i<gestures.size();i++)
    {
        if (probabilities[i]>maxp && probabilities[i]>0.5)
        {
            maxp=probabilities[i];
            newBestIndex=i;
        }
    }

    if (newBestIndex!=currentBestIndex && currentBestIndex==-1)
    {
        // new gesture is recognized
        currentBestIndex=newBestIndex;
        for (int i=0;i<gestures.size();i++)
            if (i!=currentBestIndex)
                probabilities[i]=0;
        return NEWGESTURE;
    }
    if (newBestIndex!=currentBestIndex && currentBestIndex!=-1){
        currentBestIndex=newBestIndex;
        return GESTUREEND;
    }

//    if (newBestIndex>=0)
//        return true;
//    else
//        return false;
    return SAMEGESTURE;
}

int GestureLib::resetGestureLikelihoods()
{
    for (int i=0;i<gestures.size();i++)
        probabilities[i]=0;
    return 0;
}


QString GestureLib::getBestGestureName()
{
    if (currentBestIndex>=0)
        return gestures[currentBestIndex].name();
    else
        return QString("");
}

QString GestureLib::getBestGestureCommand()
{
    if (currentBestIndex>=0)
        return gestures[currentBestIndex].command();
    else
        return NULL;
}

void GestureLib::addDefaultGestures()
{
    Gesture go(QString("GO"));
    //go.addAngleCiterion(ELB,3.14159/2);
    go.addMovementCiterion(ELB,RM);
    go.addAxisCiterion(FY,0,1,0);
    go.addAxisCiterion(UZ,0,-1,0);
    gestures.append(go);

    Gesture come(QString("COME"));
    come.addMovementCiterion(ELB,RM);
    come.addAxisCiterion(FY,0,1,0);
    come.addAxisCiterion(UZ,0,-1,0);
    gestures.append(come);

    Gesture no(QString("NO"));
    no.addAngleCiterion(ELB,3.1415926/2);
    no.addAxisCiterion(FY,0,1,0);
    no.addMovementCiterion(OME,RM);
    gestures.append(no);

    Gesture quiet(QString("QUIET"));
    quiet.addAngleCiterion(ELB,3.1415926/2);
    quiet.addAxisCiterion(FY,0,0,-1);
    quiet.addAxisCiterion(UZ,0,-1,0);
    quiet.addMovementCiterion(ELB,NM);
    gestures.append(quiet);

    Gesture down(QString("DOWN"));
    down.addMovementCiterion(ELB,NM);
    down.addMovementCiterion(OME,RM);
    down.addAxisCiterion(FY,0,0,-1);
    down.addAngleCiterion(ELB,3.1415926/2);
    gestures.append(down);

    numGesture=gestures.size();
    //saveLib(QString("default.json"));
}

int GestureLib::getBestureGestureIndex()
{
    return currentBestIndex;
}

int GestureLib::getGestureNumber() const
{
    return numGesture;
}

bool GestureLib::addEmptyGesture()
{
    gestures.append(Gesture(QString("NONAME")));
    return true;
}

bool GestureLib::removeGestureAt(const int &index)
{
    if (index>=0 && index<gestures.size())
    {
        gestures.removeAt(index);
        return true;
    }
    else
        return false;
}

//list function
Gesture & GestureLib::getGestureAt(const int &index)
{
    if (index>=0 && index<gestures.size())
        return gestures[index];
    return Gesture();
}

QStringList GestureLib::getGestureList() const
{
    QStringList gestureList;
    for (int i=0;i<gestures.size();i++)
    {
        gestureList<<QString("%1. %2").arg(i+1).arg(gestures[i].name());
    }
    return gestureList;
}

QStringList GestureLib::getGestureAxisCiteriaAt(const int &index)
{
    if (index>=0 && index<gestures.size())
        return gestures[index].getAxisCiteriaList();
    else
        return QStringList();
}

QStringList GestureLib::getGestureAngleCiteriaAt(const int &index)
{
    if (index>=0 && index<gestures.size())
        return gestures[index].getAngleCiteriaList();
    else
        return QStringList();
}

QStringList GestureLib::getGestureMoveCiteriaAt(const int &index)
{
    if (index>=0 && index<gestures.size())
        return gestures[index].getMoveCiteriaList();
    else
        return QStringList();
}
//test functions
void GestureLib::testWrite(const QString &filename)
{
    Gesture g(QString("GO"));
    g.addAngleCiterion(ELB,3.14159/2);
    g.addMovementCiterion(ELB,RM);
    g.addAxisCiterion(FY,0,-1,0);
    gestures.append(g);
    saveLib(filename);
}

void GestureLib::testRead()
{
    testWrite(QString("save.json"));
    loadLib(QString("save.json"));
    testWrite(QString("save1.json"));
}

