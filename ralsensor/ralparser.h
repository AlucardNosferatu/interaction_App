#ifndef PARSER_H
#define PARSER_H

#include <QObject>

enum STATE{
    GET_HEAD,GET_HEAD2,GET_TYPE,GET_DATA,GET_SUM
};


enum RESPONSETYPE{
    EMG,IMU,COMMAND
};

//enum ParserResult{
//    PARSING=0, NEWIMUDATA,NEWEMGDATA,NEWCOMMANDRES,ERROR
//};

enum ParserResult{INPROCESS, NEWIMUDATA,NEWEMGDATA,NEWCOMMANDRES,PARSINGERROR};

class RalParser : public QObject
{
    Q_OBJECT

public:
    explicit RalParser(QObject *parent = 0);
    int parse(unsigned char c);
    int getLatestIMUData(float quat[4]);
    int getLatestEMGData(float emgdata[8]);
    unsigned char getLatestCommand();

private:
    int currentstate,dataindex,type;
    unsigned char imuDataBuffer[50];
    unsigned char emgDataBuffer[27];
    unsigned char commandBuffer[5];
    unsigned char tmpsum;

};

#endif // PARSER_H
