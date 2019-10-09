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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
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
    QCustomPlot *accelPlot;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1147, 1073);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        portBox = new QComboBox(centralWidget);
        portBox->setObjectName(QStringLiteral("portBox"));
        portBox->setGeometry(QRect(40, 10, 69, 22));
        freshButton = new QPushButton(centralWidget);
        freshButton->setObjectName(QStringLiteral("freshButton"));
        freshButton->setGeometry(QRect(140, 10, 75, 23));
        onEMGButton = new QPushButton(centralWidget);
        onEMGButton->setObjectName(QStringLiteral("onEMGButton"));
        onEMGButton->setGeometry(QRect(20, 50, 75, 23));
        ResetButton = new QPushButton(centralWidget);
        ResetButton->setObjectName(QStringLiteral("ResetButton"));
        ResetButton->setGeometry(QRect(360, 50, 75, 23));
        c1Plot = new QCustomPlot(centralWidget);
        c1Plot->setObjectName(QStringLiteral("c1Plot"));
        c1Plot->setGeometry(QRect(20, 130, 361, 131));
        beginButton = new QPushButton(centralWidget);
        beginButton->setObjectName(QStringLiteral("beginButton"));
        beginButton->setGeometry(QRect(510, 60, 75, 23));
        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(590, 60, 75, 23));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(590, 90, 75, 23));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setGeometry(QRect(510, 90, 75, 23));
        squaretestButton = new QPushButton(centralWidget);
        squaretestButton->setObjectName(QStringLiteral("squaretestButton"));
        squaretestButton->setGeometry(QRect(100, 50, 75, 23));
        initButton = new QPushButton(centralWidget);
        initButton->setObjectName(QStringLiteral("initButton"));
        initButton->setGeometry(QRect(170, 780, 75, 23));
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
        checkBox1P = new QCheckBox(centralWidget);
        checkBox1P->setObjectName(QStringLiteral("checkBox1P"));
        checkBox1P->setGeometry(QRect(30, 820, 71, 16));
        checkBox2P = new QCheckBox(centralWidget);
        checkBox2P->setObjectName(QStringLiteral("checkBox2P"));
        checkBox2P->setGeometry(QRect(90, 820, 71, 16));
        checkBox3P = new QCheckBox(centralWidget);
        checkBox3P->setObjectName(QStringLiteral("checkBox3P"));
        checkBox3P->setGeometry(QRect(150, 820, 71, 16));
        checkBox4P = new QCheckBox(centralWidget);
        checkBox4P->setObjectName(QStringLiteral("checkBox4P"));
        checkBox4P->setGeometry(QRect(210, 820, 71, 16));
        checkBox1N = new QCheckBox(centralWidget);
        checkBox1N->setObjectName(QStringLiteral("checkBox1N"));
        checkBox1N->setGeometry(QRect(270, 820, 71, 16));
        checkBox2N = new QCheckBox(centralWidget);
        checkBox2N->setObjectName(QStringLiteral("checkBox2N"));
        checkBox2N->setGeometry(QRect(330, 820, 71, 16));
        checkBox3N = new QCheckBox(centralWidget);
        checkBox3N->setObjectName(QStringLiteral("checkBox3N"));
        checkBox3N->setGeometry(QRect(390, 820, 71, 16));
        checkBox4N = new QCheckBox(centralWidget);
        checkBox4N->setObjectName(QStringLiteral("checkBox4N"));
        checkBox4N->setGeometry(QRect(450, 820, 71, 16));
        pushButtonRLD = new QPushButton(centralWidget);
        pushButtonRLD->setObjectName(QStringLiteral("pushButtonRLD"));
        pushButtonRLD->setGeometry(QRect(500, 820, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(720, 820, 91, 23));
        lineEditAddr = new QLineEdit(centralWidget);
        lineEditAddr->setObjectName(QStringLiteral("lineEditAddr"));
        lineEditAddr->setGeometry(QRect(660, 820, 51, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(620, 820, 31, 21));
        noiseButton = new QPushButton(centralWidget);
        noiseButton->setObjectName(QStringLiteral("noiseButton"));
        noiseButton->setGeometry(QRect(180, 50, 75, 23));
        normalMeaButton = new QPushButton(centralWidget);
        normalMeaButton->setObjectName(QStringLiteral("normalMeaButton"));
        normalMeaButton->setGeometry(QRect(260, 50, 91, 23));
        c2Plot = new QCustomPlot(centralWidget);
        c2Plot->setObjectName(QStringLiteral("c2Plot"));
        c2Plot->setGeometry(QRect(390, 130, 361, 131));
        c3Plot = new QCustomPlot(centralWidget);
        c3Plot->setObjectName(QStringLiteral("c3Plot"));
        c3Plot->setGeometry(QRect(20, 270, 361, 131));
        c4Plot = new QCustomPlot(centralWidget);
        c4Plot->setObjectName(QStringLiteral("c4Plot"));
        c4Plot->setGeometry(QRect(390, 270, 361, 131));
        c5Plot = new QCustomPlot(centralWidget);
        c5Plot->setObjectName(QStringLiteral("c5Plot"));
        c5Plot->setGeometry(QRect(20, 410, 361, 131));
        c6Plot = new QCustomPlot(centralWidget);
        c6Plot->setObjectName(QStringLiteral("c6Plot"));
        c6Plot->setGeometry(QRect(390, 410, 361, 131));
        c7Plot = new QCustomPlot(centralWidget);
        c7Plot->setObjectName(QStringLiteral("c7Plot"));
        c7Plot->setGeometry(QRect(20, 550, 361, 131));
        c8Plot = new QCustomPlot(centralWidget);
        c8Plot->setObjectName(QStringLiteral("c8Plot"));
        c8Plot->setGeometry(QRect(390, 550, 361, 131));
        elbowPlot = new QCustomPlot(centralWidget);
        elbowPlot->setObjectName(QStringLiteral("elbowPlot"));
        elbowPlot->setGeometry(QRect(760, 90, 361, 201));
        shoulderPlot = new QCustomPlot(centralWidget);
        shoulderPlot->setObjectName(QStringLiteral("shoulderPlot"));
        shoulderPlot->setGeometry(QRect(760, 300, 361, 201));
        editorButton = new QPushButton(centralWidget);
        editorButton->setObjectName(QStringLiteral("editorButton"));
        editorButton->setGeometry(QRect(620, 20, 80, 21));
        onIMUButton = new QPushButton(centralWidget);
        onIMUButton->setObjectName(QStringLiteral("onIMUButton"));
        onIMUButton->setGeometry(QRect(760, 60, 80, 21));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(710, 20, 80, 21));
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
        gestureText->setGeometry(QRect(760, 510, 361, 131));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(10);
        gestureText->setFont(font);
        fb1Button = new QPushButton(centralWidget);
        fb1Button->setObjectName(QStringLiteral("fb1Button"));
        fb1Button->setGeometry(QRect(20, 90, 75, 23));
        fb2Button = new QPushButton(centralWidget);
        fb2Button->setObjectName(QStringLiteral("fb2Button"));
        fb2Button->setGeometry(QRect(100, 90, 75, 23));
        fb3Button = new QPushButton(centralWidget);
        fb3Button->setObjectName(QStringLiteral("fb3Button"));
        fb3Button->setGeometry(QRect(180, 90, 75, 23));
        fb4Button = new QPushButton(centralWidget);
        fb4Button->setObjectName(QStringLiteral("fb4Button"));
        fb4Button->setGeometry(QRect(260, 90, 75, 23));
        fb5Button = new QPushButton(centralWidget);
        fb5Button->setObjectName(QStringLiteral("fb5Button"));
        fb5Button->setGeometry(QRect(340, 90, 75, 23));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(930, 650, 191, 80));
        gestureLabel = new QLabel(groupBox);
        gestureLabel->setObjectName(QStringLiteral("gestureLabel"));
        gestureLabel->setGeometry(QRect(20, 20, 151, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font1.setPointSize(16);
        gestureLabel->setFont(font1);
        onRobotButton = new QPushButton(centralWidget);
        onRobotButton->setObjectName(QStringLiteral("onRobotButton"));
        onRobotButton->setGeometry(QRect(510, 20, 91, 21));
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
        freshButton->setText(QApplication::translate("MainWindow", "Fresh", 0));
        onEMGButton->setText(QApplication::translate("MainWindow", "Connect EMG", 0));
        ResetButton->setText(QApplication::translate("MainWindow", "Reset", 0));
        beginButton->setText(QApplication::translate("MainWindow", "Begin", 0));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0));
        saveButton->setText(QApplication::translate("MainWindow", "Save", 0));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", 0));
        squaretestButton->setText(QApplication::translate("MainWindow", "SquareTest", 0));
        initButton->setText(QApplication::translate("MainWindow", "Initialize", 0));
        lineEdit_2->setText(QApplication::translate("MainWindow", "mav0", 0));
        lineEdit_3->setText(QApplication::translate("MainWindow", "threshold", 0));
        checkBox1P->setText(QApplication::translate("MainWindow", "1P", 0));
        checkBox2P->setText(QApplication::translate("MainWindow", "2P", 0));
        checkBox3P->setText(QApplication::translate("MainWindow", "3P", 0));
        checkBox4P->setText(QApplication::translate("MainWindow", "4P", 0));
        checkBox1N->setText(QApplication::translate("MainWindow", "1N", 0));
        checkBox2N->setText(QApplication::translate("MainWindow", "2N", 0));
        checkBox3N->setText(QApplication::translate("MainWindow", "3N", 0));
        checkBox4N->setText(QApplication::translate("MainWindow", "4N", 0));
        pushButtonRLD->setText(QApplication::translate("MainWindow", "Set RLD", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Read Register", 0));
        label->setText(QApplication::translate("MainWindow", "Addr", 0));
        noiseButton->setText(QApplication::translate("MainWindow", "NoiseTest", 0));
        normalMeaButton->setText(QApplication::translate("MainWindow", "NormalMeasure", 0));
        editorButton->setText(QApplication::translate("MainWindow", "Editor", 0));
        onIMUButton->setText(QApplication::translate("MainWindow", "Connect IMU", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Calibration", 0));
        loadButton->setText(QApplication::translate("MainWindow", "Load", 0));
        playButton->setText(QApplication::translate("MainWindow", "Play", 0));
        lengthLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        pauseButton->setText(QApplication::translate("MainWindow", "Pause", 0));
        fb1Button->setText(QApplication::translate("MainWindow", "FeedBack1", 0));
        fb2Button->setText(QApplication::translate("MainWindow", "FeedBack2", 0));
        fb3Button->setText(QApplication::translate("MainWindow", "FeedBack3", 0));
        fb4Button->setText(QApplication::translate("MainWindow", "FeedBack4", 0));
        fb5Button->setText(QApplication::translate("MainWindow", "FeedBack5", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Result", 0));
        gestureLabel->setText(QApplication::translate("MainWindow", "\347\273\223\346\236\234", 0));
        onRobotButton->setText(QApplication::translate("MainWindow", "Connect Robot", 0));
        radioButton->setText(QApplication::translate("MainWindow", "Path Test", 0));
        radioButton_2->setText(QApplication::translate("MainWindow", "Grasp Test", 0));
        play3XButton->setText(QApplication::translate("MainWindow", "3X", 0));
        stepButton->setText(QApplication::translate("MainWindow", "Step", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
