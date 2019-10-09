#include "windows/mainwindow.h"
#include <QApplication>
#include "recognizor.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Recognizor c;
//    c.voiceOutPut("ok ok ok ok ok");
    return a.exec();
}
