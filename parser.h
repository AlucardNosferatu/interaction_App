#ifndef PARSER_H
#define PARSER_H

#include <QObject>

enum STATE{
    GET_HEAD,GET_HEAD2,GET_TYPE,GET_DATA,GET_SUM
};

typedef enum {
    PARSING,NEWIMUDATA,NEWEMGDATA,NEWCOMMANDRES,ERROR
}ParserResult;

enum RESPONSETYPE{
    EMG,IMU,COMMAND
};

class Parser: public QObject
{
    Q_OBJECT

public:
    explicit Parser(QObject *parent = 0);
    int parse(unsigned char c);
    int getLatestIMUData(float quat[4]);
    int getLatestEMGData(float emgdata[8]);
    unsigned char getLatestCommand();

private:
    int currentstate,dataindex,type;
    unsigned char imuDataBuffer[16];
    unsigned char emgDataBuffer[27];
    unsigned char commandBuffer[5];
    unsigned char tmpsum;

signals:
    void parseFinish(ParserResult result);
};

#endif // PARSER_H
