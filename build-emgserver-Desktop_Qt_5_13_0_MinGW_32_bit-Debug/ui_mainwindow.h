/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "plot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QComboBox *portBox;
    QPushButton *freshButton;
    QPushButton *onEMGButton;
    QPushButton *ResetButton;
    QCustomPlot *c1Plot;
    QPushButton *beginButton;
    QPushButton *stopButton;
    QPushButton *saveButton;
    QPushButton *clearButton;
    QPushButton *squaretestButton;
    QPushButton *initButton;
    QTextEdit *GestureEdit;
    QTextEdit *Mav0;
    QTextEdit *Threshold;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QCheckBox *checkBox1P;
    QCheckBox *checkBox2P;
    QCheckBox *checkBox3P;
    QCheckBox *checkBox4P;
    QCheckBox *checkBox1N;
    QCheckBox *checkBox2N;
    QCheckBox *checkBox3N;
    QCheckBox *checkBox4N;
    QPushButton *pushButtonRLD;
    QPushButton *pushButton_2;
    QLineEdit *lineEditAddr;
    QLabel *label;
    QPushButton *noiseButton;
    QPushButton *normalMeaButton;
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
    QPushButton *fb1Button;
    QPushButton *fb2Button;
    QPushButton *fb3Button;
    QPushButton *fb4Button;
    QPushButton *fb5Button;
    QGroupBox *groupBox;
    QLabel *gestureLabel;
    QPushButton *onRobotButton;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *play3XButton;
    QPushButton *stepButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1147, 778);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        portBox = new QComboBox(centralWidget);
        portBox->setObjectName(QString::fromUtf8("portBox"));
        portBox->setGeometry(QRect(40, 10, 69, 22));
        freshButton = new QPushButton(centralWidget);
        freshButton->setObjectName(QString::fromUtf8("freshButton"));
        freshButton->setGeometry(QRect(140, 10, 75, 23));
        onEMGButton = new QPushButton(centralWidget);
        onEMGButton->setObjectName(QString::fromUtf8("onEMGButton"));
        onEMGButton->setGeometry(QRect(20, 50, 75, 23));
        ResetButton = new QPushButton(centralWidget);
        ResetButton->setObjectName(QString::fromUtf8("ResetButton"));
        ResetButton->setGeometry(QRect(360, 50, 75, 23));
        c1Plot = new QCustomPlot(centralWidget);
        c1Plot->setObjectName(QString::fromUtf8("c1Plot"));
        c1Plot->setGeometry(QRect(20, 130, 361, 131));
        beginButton = new QPushButton(centralWidget);
        beginButton->setObjectName(QString::fromUtf8("beginButton"));
        beginButton->setGeometry(QRect(510, 60, 75, 23));
        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setGeometry(QRect(590, 60, 75, 23));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(590, 90, 75, 23));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(510, 90, 75, 23));
        squaretestButton = new QPushButton(centralWidget);
        squaretestButton->setObjectName(QString::fromUtf8("squaretestButton"));
        squaretestButton->setGeometry(QRect(100, 50, 75, 23));
        initButton = new QPushButton(centralWidget);
        initButton->setObjectName(QString::fromUtf8("initButton"));
        initButton->setGeometry(QRect(170, 780, 75, 23));
        GestureEdit = new QTextEdit(centralWidget);
        GestureEdit->setObjectName(QString::fromUtf8("GestureEdit"));
        GestureEdit->setGeometry(QRect(30, 770, 111, 31));
        Mav0 = new QTextEdit(centralWidget);
        Mav0->setObjectName(QString::fromUtf8("Mav0"));
        Mav0->setGeometry(QRect(320, 770, 231, 31));
        Threshold = new QTextEdit(centralWidget);
        Threshold->setObjectName(QString::fromUtf8("Threshold"));
        Threshold->setGeometry(QRect(650, 770, 121, 31));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(260, 780, 51, 21));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(570, 780, 71, 21));
        checkBox1P = new QCheckBox(centralWidget);
        checkBox1P->setObjectName(QString::fromUtf8("checkBox1P"));
        checkBox1P->setGeometry(QRect(30, 820, 71, 16));
        checkBox2P = new QCheckBox(centralWidget);
        checkBox2P->setObjectName(QString::fromUtf8("checkBox2P"));
        checkBox2P->setGeometry(QRect(90, 820, 71, 16));
        checkBox3P = new QCheckBox(centralWidget);
        checkBox3P->setObjectName(QString::fromUtf8("checkBox3P"));
        checkBox3P->setGeometry(QRect(150, 820, 71, 16));
        checkBox4P = new QCheckBox(centralWidget);
        checkBox4P->setObjectName(QString::fromUtf8("checkBox4P"));
        checkBox4P->setGeometry(QRect(210, 820, 71, 16));
        checkBox1N = new QCheckBox(centralWidget);
        checkBox1N->setObjectName(QString::fromUtf8("checkBox1N"));
        checkBox1N->setGeometry(QRect(270, 820, 71, 16));
        checkBox2N = new QCheckBox(centralWidget);
        checkBox2N->setObjectName(QString::fromUtf8("checkBox2N"));
        checkBox2N->setGeometry(QRect(330, 820, 71, 16));
        checkBox3N = new QCheckBox(centralWidget);
        checkBox3N->setObjectName(QString::fromUtf8("checkBox3N"));
        checkBox3N->setGeometry(QRect(390, 820, 71, 16));
        checkBox4N = new QCheckBox(centralWidget);
        checkBox4N->setObjectName(QString::fromUtf8("checkBox4N"));
        checkBox4N->setGeometry(QRect(450, 820, 71, 16));
        pushButtonRLD = new QPushButton(centralWidget);
        pushButtonRLD->setObjectName(QString::fromUtf8("pushButtonRLD"));
        pushButtonRLD->setGeometry(QRect(500, 820, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(720, 820, 91, 23));
        lineEditAddr = new QLineEdit(centralWidget);
        lineEditAddr->setObjectName(QString::fromUtf8("lineEditAddr"));
        lineEditAddr->setGeometry(QRect(660, 820, 51, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(620, 820, 31, 21));
        noiseButton = new QPushButton(centralWidget);
        noiseButton->setObjectName(QString::fromUtf8("noiseButton"));
        noiseButton->setGeometry(QRect(180, 50, 75, 23));
        normalMeaButton = new QPushButton(centralWidget);
        normalMeaButton->setObjectName(QString::fromUtf8("normalMeaButton"));
        normalMeaButton->setGeometry(QRect(260, 50, 91, 23));
        c2Plot = new QCustomPlot(centralWidget);
        c2Plot->setObjectName(QString::fromUtf8("c2Plot"));
        c2Plot->setGeometry(QRect(390, 130, 361, 131));
        c3Plot = new QCustomPlot(centralWidget);
        c3Plot->setObjectName(QString::fromUtf8("c3Plot"));
        c3Plot->setGeometry(QRect(20, 270, 361, 131));
        c4Plot = new QCustomPlot(centralWidget);
        c4Plot->setObjectName(QString::fromUtf8("c4Plot"));
        c4Plot->setGeometry(QRect(390, 270, 361, 131));
        c5Plot = new QCustomPlot(centralWidget);
        c5Plot->setObjectName(QString::fromUtf8("c5Plot"));
        c5Plot->setGeometry(QRect(20, 410, 361, 131));
        c6Plot = new QCustomPlot(centralWidget);
        c6Plot->setObjectName(QString::fromUtf8("c6Plot"));
        c6Plot->setGeometry(QRect(390, 410, 361, 131));
        c7Plot = new QCustomPlot(centralWidget);
        c7Plot->setObjectName(QString::fromUtf8("c7Plot"));
        c7Plot->setGeometry(QRect(20, 550, 361, 131));
        c8Plot = new QCustomPlot(centralWidget);
        c8Plot->setObjectName(QString::fromUtf8("c8Plot"));
        c8Plot->setGeometry(QRect(390, 550, 361, 131));
        elbowPlot = new QCustomPlot(centralWidget);
        elbowPlot->setObjectName(QString::fromUtf8("elbowPlot"));
        elbowPlot->setGeometry(QRect(760, 90, 361, 201));
        shoulderPlot = new QCustomPlot(centralWidget);
        shoulderPlot->setObjectName(QString::fromUtf8("shoulderPlot"));
        shoulderPlot->setGeometry(QRect(760, 300, 361, 201));
        editorButton = new QPushButton(centralWidget);
        editorButton->setObjectName(QString::fromUtf8("editorButton"));
        editorButton->setGeometry(QRect(620, 20, 80, 21));
        onIMUButton = new QPushButton(centralWidget);
        onIMUButton->setObjectName(QString::fromUtf8("onIMUButton"));
        onIMUButton->setGeometry(QRect(760, 60, 80, 21));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(710, 20, 80, 21));
        loadButton = new QPushButton(centralWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(60, 700, 61, 23));
        playButton = new QPushButton(centralWidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(130, 700, 61, 23));
        Slider = new QSlider(centralWidget);
        Slider->setObjectName(QString::fromUtf8("Slider"));
        Slider->setGeometry(QRect(370, 700, 441, 22));
        Slider->setOrientation(Qt::Horizontal);
        lengthLabel = new QLabel(centralWidget);
        lengthLabel->setObjectName(QString::fromUtf8("lengthLabel"));
        lengthLabel->setGeometry(QRect(830, 700, 81, 21));
        pauseButton = new QPushButton(centralWidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setGeometry(QRect(200, 700, 61, 23));
        gestureText = new QPlainTextEdit(centralWidget);
        gestureText->setObjectName(QString::fromUtf8("gestureText"));
        gestureText->setGeometry(QRect(760, 510, 361, 131));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(10);
        gestureText->setFont(font);
        fb1Button = new QPushButton(centralWidget);
        fb1Button->setObjectName(QString::fromUtf8("fb1Button"));
        fb1Button->setGeometry(QRect(20, 90, 75, 23));
        fb2Button = new QPushButton(centralWidget);
        fb2Button->setObjectName(QString::fromUtf8("fb2Button"));
        fb2Button->setGeometry(QRect(100, 90, 75, 23));
        fb3Button = new QPushButton(centralWidget);
        fb3Button->setObjectName(QString::fromUtf8("fb3Button"));
        fb3Button->setGeometry(QRect(180, 90, 75, 23));
        fb4Button = new QPushButton(centralWidget);
        fb4Button->setObjectName(QString::fromUtf8("fb4Button"));
        fb4Button->setGeometry(QRect(260, 90, 75, 23));
        fb5Button = new QPushButton(centralWidget);
        fb5Button->setObjectName(QString::fromUtf8("fb5Button"));
        fb5Button->setGeometry(QRect(340, 90, 75, 23));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(930, 650, 191, 80));
        gestureLabel = new QLabel(groupBox);
        gestureLabel->setObjectName(QString::fromUtf8("gestureLabel"));
        gestureLabel->setGeometry(QRect(20, 20, 151, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font1.setPointSize(16);
        gestureLabel->setFont(font1);
        onRobotButton = new QPushButton(centralWidget);
        onRobotButton->setObjectName(QString::fromUtf8("onRobotButton"));
        onRobotButton->setGeometry(QRect(510, 20, 91, 21));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(860, 20, 89, 16));
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(960, 20, 89, 16));
        play3XButton = new QPushButton(centralWidget);
        play3XButton->setObjectName(QString::fromUtf8("play3XButton"));
        play3XButton->setGeometry(QRect(10, 700, 41, 23));
        stepButton = new QPushButton(centralWidget);
        stepButton->setObjectName(QString::fromUtf8("stepButton"));
        stepButton->setGeometry(QRect(270, 700, 61, 23));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        freshButton->setText(QCoreApplication::translate("MainWindow", "Fresh", nullptr));
        onEMGButton->setText(QCoreApplication::translate("MainWindow", "Connect EMG", nullptr));
        ResetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        beginButton->setText(QCoreApplication::translate("MainWindow", "Begin", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        squaretestButton->setText(QCoreApplication::translate("MainWindow", "SquareTest", nullptr));
        initButton->setText(QCoreApplication::translate("MainWindow", "Initialize", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "mav0", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "threshold", nullptr));
        checkBox1P->setText(QCoreApplication::translate("MainWindow", "1P", nullptr));
        checkBox2P->setText(QCoreApplication::translate("MainWindow", "2P", nullptr));
        checkBox3P->setText(QCoreApplication::translate("MainWindow", "3P", nullptr));
        checkBox4P->setText(QCoreApplication::translate("MainWindow", "4P", nullptr));
        checkBox1N->setText(QCoreApplication::translate("MainWindow", "1N", nullptr));
        checkBox2N->setText(QCoreApplication::translate("MainWindow", "2N", nullptr));
        checkBox3N->setText(QCoreApplication::translate("MainWindow", "3N", nullptr));
        checkBox4N->setText(QCoreApplication::translate("MainWindow", "4N", nullptr));
        pushButtonRLD->setText(QCoreApplication::translate("MainWindow", "Set RLD", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Read Register", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Addr", nullptr));
        noiseButton->setText(QCoreApplication::translate("MainWindow", "NoiseTest", nullptr));
        normalMeaButton->setText(QCoreApplication::translate("MainWindow", "NormalMeasure", nullptr));
        editorButton->setText(QCoreApplication::translate("MainWindow", "Editor", nullptr));
        onIMUButton->setText(QCoreApplication::translate("MainWindow", "Connect IMU", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Calibration", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        lengthLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        fb1Button->setText(QCoreApplication::translate("MainWindow", "FeedBack1", nullptr));
        fb2Button->setText(QCoreApplication::translate("MainWindow", "FeedBack2", nullptr));
        fb3Button->setText(QCoreApplication::translate("MainWindow", "FeedBack3", nullptr));
        fb4Button->setText(QCoreApplication::translate("MainWindow", "FeedBack4", nullptr));
        fb5Button->setText(QCoreApplication::translate("MainWindow", "FeedBack5", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Result", nullptr));
        gestureLabel->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\236\234", nullptr));
        onRobotButton->setText(QCoreApplication::translate("MainWindow", "Connect Robot", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Path Test", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Grasp Test", nullptr));
        play3XButton->setText(QCoreApplication::translate("MainWindow", "3X", nullptr));
        stepButton->setText(QCoreApplication::translate("MainWindow", "Step", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
