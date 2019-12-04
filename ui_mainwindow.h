/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "plot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *c1Plot;
    QPushButton *beginButton;
    QPushButton *stopButton;
    QPushButton *saveButton;
    QPushButton *clearButton;
    QTextEdit *GestureEdit;
    QTextEdit *Mav0;
    QTextEdit *Threshold;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_2;
    QLineEdit *lineEditAddr;
    QLabel *label;
    QCustomPlot *c2Plot;
    QCustomPlot *c3Plot;
    QCustomPlot *c4Plot;
    QCustomPlot *c5Plot;
    QCustomPlot *c6Plot;
    QCustomPlot *c7Plot;
    QCustomPlot *c8Plot;
    QCustomPlot *elbowPlot;
    QCustomPlot *shoulderPlot;
    QPushButton *editorButton;
    QPushButton *onIMUButton;
    QPushButton *pushButton;
    QPushButton *loadButton;
    QPushButton *playButton;
    QSlider *Slider;
    QLabel *lengthLabel;
    QPushButton *pauseButton;
    QPlainTextEdit *gestureText;
    QGroupBox *groupBox;
    QLabel *gestureLabel;
    QPushButton *onRobotButton;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *play3XButton;
    QPushButton *stepButton;
    QCustomPlot *accelPlot;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_close;
    QPushButton *pushButton_connectWifi;
    QLineEdit *lineEdit_port;
    QVBoxLayout *verticalLayout_5;
    QTextBrowser *textBrowser_log;
    QPushButton *pushButton_clearLog;
    QCustomPlot *c3Plot_2;
    QCustomPlot *c1Plot_2;
    QCustomPlot *c5Plot_2;
    QCustomPlot *c2Plot_2;
    QCustomPlot *c4Plot_2;
    QCustomPlot *c8Plot_2;
    QCustomPlot *c6Plot_2;
    QCustomPlot *c7Plot_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1147, 1073);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        c1Plot = new QCustomPlot(centralWidget);
        c1Plot->setObjectName(QStringLiteral("c1Plot"));
        c1Plot->setGeometry(QRect(20, 100, 181, 131));
        beginButton = new QPushButton(centralWidget);
        beginButton->setObjectName(QStringLiteral("beginButton"));
        beginButton->setGeometry(QRect(390, 40, 91, 23));
        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(390, 70, 91, 23));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(490, 70, 81, 23));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setGeometry(QRect(490, 40, 81, 23));
        GestureEdit = new QTextEdit(centralWidget);
        GestureEdit->setObjectName(QStringLiteral("GestureEdit"));
        GestureEdit->setGeometry(QRect(30, 770, 111, 31));
        Mav0 = new QTextEdit(centralWidget);
        Mav0->setObjectName(QStringLiteral("Mav0"));
        Mav0->setGeometry(QRect(320, 770, 231, 31));
        Threshold = new QTextEdit(centralWidget);
        Threshold->setObjectName(QStringLiteral("Threshold"));
        Threshold->setGeometry(QRect(650, 770, 121, 31));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(260, 780, 51, 21));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(570, 780, 71, 21));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(720, 820, 91, 23));
        lineEditAddr = new QLineEdit(centralWidget);
        lineEditAddr->setObjectName(QStringLiteral("lineEditAddr"));
        lineEditAddr->setGeometry(QRect(660, 820, 51, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(620, 820, 31, 21));
        c2Plot = new QCustomPlot(centralWidget);
        c2Plot->setObjectName(QStringLiteral("c2Plot"));
        c2Plot->setGeometry(QRect(210, 100, 181, 131));
        c3Plot = new QCustomPlot(centralWidget);
        c3Plot->setObjectName(QStringLiteral("c3Plot"));
        c3Plot->setGeometry(QRect(20, 240, 181, 131));
        c4Plot = new QCustomPlot(centralWidget);
        c4Plot->setObjectName(QStringLiteral("c4Plot"));
        c4Plot->setGeometry(QRect(210, 240, 181, 131));
        c5Plot = new QCustomPlot(centralWidget);
        c5Plot->setObjectName(QStringLiteral("c5Plot"));
        c5Plot->setGeometry(QRect(20, 380, 181, 131));
        c6Plot = new QCustomPlot(centralWidget);
        c6Plot->setObjectName(QStringLiteral("c6Plot"));
        c6Plot->setGeometry(QRect(210, 380, 181, 131));
        c7Plot = new QCustomPlot(centralWidget);
        c7Plot->setObjectName(QStringLiteral("c7Plot"));
        c7Plot->setGeometry(QRect(20, 520, 181, 131));
        c8Plot = new QCustomPlot(centralWidget);
        c8Plot->setObjectName(QStringLiteral("c8Plot"));
        c8Plot->setGeometry(QRect(210, 520, 181, 131));
        elbowPlot = new QCustomPlot(centralWidget);
        elbowPlot->setObjectName(QStringLiteral("elbowPlot"));
        elbowPlot->setGeometry(QRect(780, 100, 341, 201));
        shoulderPlot = new QCustomPlot(centralWidget);
        shoulderPlot->setObjectName(QStringLiteral("shoulderPlot"));
        shoulderPlot->setGeometry(QRect(780, 310, 341, 201));
        editorButton = new QPushButton(centralWidget);
        editorButton->setObjectName(QStringLiteral("editorButton"));
        editorButton->setGeometry(QRect(490, 10, 80, 21));
        onIMUButton = new QPushButton(centralWidget);
        onIMUButton->setObjectName(QStringLiteral("onIMUButton"));
        onIMUButton->setGeometry(QRect(580, 40, 80, 21));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(580, 10, 80, 21));
        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setGeometry(QRect(60, 700, 61, 23));
        playButton = new QPushButton(centralWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(130, 700, 61, 23));
        Slider = new QSlider(centralWidget);
        Slider->setObjectName(QStringLiteral("Slider"));
        Slider->setGeometry(QRect(370, 700, 441, 22));
        Slider->setOrientation(Qt::Horizontal);
        lengthLabel = new QLabel(centralWidget);
        lengthLabel->setObjectName(QStringLiteral("lengthLabel"));
        lengthLabel->setGeometry(QRect(830, 700, 81, 21));
        pauseButton = new QPushButton(centralWidget);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        pauseButton->setGeometry(QRect(200, 700, 61, 23));
        gestureText = new QPlainTextEdit(centralWidget);
        gestureText->setObjectName(QStringLiteral("gestureText"));
        gestureText->setGeometry(QRect(780, 520, 341, 131));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(10);
        gestureText->setFont(font);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(930, 660, 191, 80));
        gestureLabel = new QLabel(groupBox);
        gestureLabel->setObjectName(QStringLiteral("gestureLabel"));
        gestureLabel->setGeometry(QRect(20, 20, 151, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font1.setPointSize(16);
        gestureLabel->setFont(font1);
        onRobotButton = new QPushButton(centralWidget);
        onRobotButton->setObjectName(QStringLiteral("onRobotButton"));
        onRobotButton->setGeometry(QRect(390, 10, 91, 21));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(860, 20, 89, 16));
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(960, 20, 89, 16));
        play3XButton = new QPushButton(centralWidget);
        play3XButton->setObjectName(QStringLiteral("play3XButton"));
        play3XButton->setGeometry(QRect(10, 700, 41, 23));
        stepButton = new QPushButton(centralWidget);
        stepButton->setObjectName(QStringLiteral("stepButton"));
        stepButton->setGeometry(QRect(270, 700, 61, 23));
        accelPlot = new QCustomPlot(centralWidget);
        accelPlot->setObjectName(QStringLiteral("accelPlot"));
        accelPlot->setGeometry(QRect(50, 850, 361, 201));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 361, 81));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton_close = new QPushButton(layoutWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));

        verticalLayout_2->addWidget(pushButton_close);

        pushButton_connectWifi = new QPushButton(layoutWidget);
        pushButton_connectWifi->setObjectName(QStringLiteral("pushButton_connectWifi"));

        verticalLayout_2->addWidget(pushButton_connectWifi);

        lineEdit_port = new QLineEdit(layoutWidget);
        lineEdit_port->setObjectName(QStringLiteral("lineEdit_port"));

        verticalLayout_2->addWidget(lineEdit_port);


        horizontalLayout_9->addLayout(verticalLayout_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        textBrowser_log = new QTextBrowser(layoutWidget);
        textBrowser_log->setObjectName(QStringLiteral("textBrowser_log"));
        textBrowser_log->setMaximumSize(QSize(16777215, 71));

        verticalLayout_5->addWidget(textBrowser_log);

        pushButton_clearLog = new QPushButton(layoutWidget);
        pushButton_clearLog->setObjectName(QStringLiteral("pushButton_clearLog"));

        verticalLayout_5->addWidget(pushButton_clearLog);


        horizontalLayout_9->addLayout(verticalLayout_5);

        c3Plot_2 = new QCustomPlot(centralWidget);
        c3Plot_2->setObjectName(QStringLiteral("c3Plot_2"));
        c3Plot_2->setGeometry(QRect(400, 240, 181, 131));
        c1Plot_2 = new QCustomPlot(centralWidget);
        c1Plot_2->setObjectName(QStringLiteral("c1Plot_2"));
        c1Plot_2->setGeometry(QRect(400, 100, 181, 131));
        c5Plot_2 = new QCustomPlot(centralWidget);
        c5Plot_2->setObjectName(QStringLiteral("c5Plot_2"));
        c5Plot_2->setGeometry(QRect(400, 380, 181, 131));
        c2Plot_2 = new QCustomPlot(centralWidget);
        c2Plot_2->setObjectName(QStringLiteral("c2Plot_2"));
        c2Plot_2->setGeometry(QRect(590, 100, 181, 131));
        c4Plot_2 = new QCustomPlot(centralWidget);
        c4Plot_2->setObjectName(QStringLiteral("c4Plot_2"));
        c4Plot_2->setGeometry(QRect(590, 240, 181, 131));
        c8Plot_2 = new QCustomPlot(centralWidget);
        c8Plot_2->setObjectName(QStringLiteral("c8Plot_2"));
        c8Plot_2->setGeometry(QRect(590, 520, 181, 131));
        c6Plot_2 = new QCustomPlot(centralWidget);
        c6Plot_2->setObjectName(QStringLiteral("c6Plot_2"));
        c6Plot_2->setGeometry(QRect(590, 380, 181, 131));
        c7Plot_2 = new QCustomPlot(centralWidget);
        c7Plot_2->setObjectName(QStringLiteral("c7Plot_2"));
        c7Plot_2->setGeometry(QRect(400, 520, 181, 131));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        beginButton->setText(QApplication::translate("MainWindow", "Begin", 0));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0));
        saveButton->setText(QApplication::translate("MainWindow", "Save", 0));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", 0));
        lineEdit_2->setText(QApplication::translate("MainWindow", "mav0", 0));
        lineEdit_3->setText(QApplication::translate("MainWindow", "threshold", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Read Register", 0));
        label->setText(QApplication::translate("MainWindow", "Addr", 0));
        editorButton->setText(QApplication::translate("MainWindow", "Editor", 0));
        onIMUButton->setText(QApplication::translate("MainWindow", "Connect IMU", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Calibration", 0));
        loadButton->setText(QApplication::translate("MainWindow", "Load", 0));
        playButton->setText(QApplication::translate("MainWindow", "Play", 0));
        lengthLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        pauseButton->setText(QApplication::translate("MainWindow", "Pause", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Result", 0));
        gestureLabel->setText(QApplication::translate("MainWindow", "\347\273\223\346\236\234", 0));
        onRobotButton->setText(QApplication::translate("MainWindow", "Connect Robot", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Path Test", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Grasp Test", 0));
        play3XButton->setText(QApplication::translate("MainWindow", "3X", 0));
        stepButton->setText(QApplication::translate("MainWindow", "Step", 0));
        pushButton_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", 0));
        pushButton_connectWifi->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", 0));
        lineEdit_port->setText(QApplication::translate("MainWindow", "8081;8082;8083;8084", 0));
        pushButton_clearLog->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
