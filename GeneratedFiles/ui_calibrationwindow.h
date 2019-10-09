/********************************************************************************
** Form generated from reading UI file 'calibrationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONWINDOW_H
#define UI_CALIBRATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationWindow
{
public:
    QWidget *centralwidget;
    QRadioButton *backButton;
    QPushButton *savecaliButton;
    QLabel *elbow0;
    QRadioButton *frontButton;
    QPushButton *loadcaliButton;
    QLabel *azimuthal0;
    QPushButton *calibrationButton;
    QGroupBox *groupBox;
    QLabel *label_17;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *twistText;
    QLineEdit *elbowText;
    QLineEdit *polarText;
    QLabel *label_13;
    QLineEdit *thetaText;
    QLabel *label_16;
    QLineEdit *omegaText;
    QLabel *polar0;
    QLabel *omega0;
    QPushButton *updateParaButton;
    QLabel *twist0;
    QGroupBox *groupBox_2;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLineEdit *twistThreshold;
    QLineEdit *elbowThreshold;
    QLineEdit *polarThreshold;
    QLabel *label_21;
    QLineEdit *thetaThreshold;
    QLabel *label_22;
    QLineEdit *omegaThreshold;

    void setupUi(QMainWindow *CalibrationWindow)
    {
        if (CalibrationWindow->objectName().isEmpty())
            CalibrationWindow->setObjectName(QStringLiteral("CalibrationWindow"));
        CalibrationWindow->resize(405, 405);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CalibrationWindow->sizePolicy().hasHeightForWidth());
        CalibrationWindow->setSizePolicy(sizePolicy);
        CalibrationWindow->setMinimumSize(QSize(405, 405));
        CalibrationWindow->setMaximumSize(QSize(405, 405));
        centralwidget = new QWidget(CalibrationWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        backButton = new QRadioButton(centralwidget);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(150, 150, 89, 16));
        backButton->setChecked(true);
        savecaliButton = new QPushButton(centralwidget);
        savecaliButton->setObjectName(QStringLiteral("savecaliButton"));
        savecaliButton->setGeometry(QRect(150, 80, 81, 31));
        elbow0 = new QLabel(centralwidget);
        elbow0->setObjectName(QStringLiteral("elbow0"));
        elbow0->setGeometry(QRect(20, 30, 111, 21));
        frontButton = new QRadioButton(centralwidget);
        frontButton->setObjectName(QStringLiteral("frontButton"));
        frontButton->setGeometry(QRect(270, 150, 89, 16));
        loadcaliButton = new QPushButton(centralwidget);
        loadcaliButton->setObjectName(QStringLiteral("loadcaliButton"));
        loadcaliButton->setGeometry(QRect(270, 30, 81, 31));
        azimuthal0 = new QLabel(centralwidget);
        azimuthal0->setObjectName(QStringLiteral("azimuthal0"));
        azimuthal0->setGeometry(QRect(20, 120, 111, 21));
        calibrationButton = new QPushButton(centralwidget);
        calibrationButton->setObjectName(QStringLiteral("calibrationButton"));
        calibrationButton->setEnabled(true);
        calibrationButton->setGeometry(QRect(150, 30, 81, 31));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 190, 181, 191));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 150, 54, 21));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 60, 54, 21));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 90, 54, 21));
        twistText = new QLineEdit(groupBox);
        twistText->setObjectName(QStringLiteral("twistText"));
        twistText->setGeometry(QRect(50, 60, 113, 20));
        twistText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        twistText->setMaxLength(10);
        elbowText = new QLineEdit(groupBox);
        elbowText->setObjectName(QStringLiteral("elbowText"));
        elbowText->setGeometry(QRect(50, 30, 113, 20));
        elbowText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        elbowText->setMaxLength(10);
        polarText = new QLineEdit(groupBox);
        polarText->setObjectName(QStringLiteral("polarText"));
        polarText->setGeometry(QRect(50, 90, 113, 20));
        polarText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        polarText->setMaxLength(10);
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 30, 54, 21));
        thetaText = new QLineEdit(groupBox);
        thetaText->setObjectName(QStringLiteral("thetaText"));
        thetaText->setGeometry(QRect(50, 120, 113, 20));
        thetaText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        thetaText->setMaxLength(10);
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 120, 54, 21));
        omegaText = new QLineEdit(groupBox);
        omegaText->setObjectName(QStringLiteral("omegaText"));
        omegaText->setGeometry(QRect(50, 150, 113, 20));
        omegaText->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        omegaText->setMaxLength(10);
        polar0 = new QLabel(centralwidget);
        polar0->setObjectName(QStringLiteral("polar0"));
        polar0->setGeometry(QRect(20, 90, 111, 21));
        omega0 = new QLabel(centralwidget);
        omega0->setObjectName(QStringLiteral("omega0"));
        omega0->setGeometry(QRect(20, 150, 111, 21));
        updateParaButton = new QPushButton(centralwidget);
        updateParaButton->setObjectName(QStringLiteral("updateParaButton"));
        updateParaButton->setGeometry(QRect(270, 80, 81, 31));
        twist0 = new QLabel(centralwidget);
        twist0->setObjectName(QStringLiteral("twist0"));
        twist0->setGeometry(QRect(20, 60, 111, 21));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(200, 190, 181, 191));
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(10, 150, 54, 21));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 60, 54, 21));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 90, 54, 21));
        twistThreshold = new QLineEdit(groupBox_2);
        twistThreshold->setObjectName(QStringLiteral("twistThreshold"));
        twistThreshold->setGeometry(QRect(50, 60, 113, 20));
        twistThreshold->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        twistThreshold->setMaxLength(10);
        elbowThreshold = new QLineEdit(groupBox_2);
        elbowThreshold->setObjectName(QStringLiteral("elbowThreshold"));
        elbowThreshold->setGeometry(QRect(50, 30, 113, 20));
        elbowThreshold->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        elbowThreshold->setMaxLength(10);
        polarThreshold = new QLineEdit(groupBox_2);
        polarThreshold->setObjectName(QStringLiteral("polarThreshold"));
        polarThreshold->setGeometry(QRect(50, 90, 113, 20));
        polarThreshold->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        polarThreshold->setMaxLength(10);
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(10, 30, 54, 21));
        thetaThreshold = new QLineEdit(groupBox_2);
        thetaThreshold->setObjectName(QStringLiteral("thetaThreshold"));
        thetaThreshold->setGeometry(QRect(50, 120, 113, 20));
        thetaThreshold->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        thetaThreshold->setMaxLength(10);
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 120, 54, 21));
        omegaThreshold = new QLineEdit(groupBox_2);
        omegaThreshold->setObjectName(QStringLiteral("omegaThreshold"));
        omegaThreshold->setGeometry(QRect(50, 150, 113, 20));
        omegaThreshold->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        omegaThreshold->setMaxLength(10);
        CalibrationWindow->setCentralWidget(centralwidget);

        retranslateUi(CalibrationWindow);

        QMetaObject::connectSlotsByName(CalibrationWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CalibrationWindow)
    {
        CalibrationWindow->setWindowTitle(QApplication::translate("CalibrationWindow", "Calibration Window", 0));
        backButton->setText(QApplication::translate("CalibrationWindow", "On the back", 0));
        savecaliButton->setText(QApplication::translate("CalibrationWindow", "Save Cali", 0));
        elbow0->setText(QApplication::translate("CalibrationWindow", "TextLabel", 0));
        frontButton->setText(QApplication::translate("CalibrationWindow", "On the front", 0));
        loadcaliButton->setText(QApplication::translate("CalibrationWindow", "Load Cali", 0));
        azimuthal0->setText(QApplication::translate("CalibrationWindow", "TextLabel", 0));
        calibrationButton->setText(QApplication::translate("CalibrationWindow", "Calibration", 0));
        groupBox->setTitle(QApplication::translate("CalibrationWindow", "Motion Range", 0));
        label_17->setText(QApplication::translate("CalibrationWindow", "Omega", 0));
        label_14->setText(QApplication::translate("CalibrationWindow", "Twist", 0));
        label_15->setText(QApplication::translate("CalibrationWindow", "Polar", 0));
        label_13->setText(QApplication::translate("CalibrationWindow", "Elbow", 0));
        label_16->setText(QApplication::translate("CalibrationWindow", "Theta", 0));
        polar0->setText(QApplication::translate("CalibrationWindow", "TextLabel", 0));
        omega0->setText(QApplication::translate("CalibrationWindow", "TextLabel", 0));
        updateParaButton->setText(QApplication::translate("CalibrationWindow", "Update Pars", 0));
        twist0->setText(QApplication::translate("CalibrationWindow", "TextLabel", 0));
        groupBox_2->setTitle(QApplication::translate("CalibrationWindow", "Thresholds", 0));
        label_18->setText(QApplication::translate("CalibrationWindow", "Omega", 0));
        label_19->setText(QApplication::translate("CalibrationWindow", "Twist", 0));
        label_20->setText(QApplication::translate("CalibrationWindow", "Polar", 0));
        label_21->setText(QApplication::translate("CalibrationWindow", "Elbow", 0));
        label_22->setText(QApplication::translate("CalibrationWindow", "Theta", 0));
    } // retranslateUi

};

namespace Ui {
    class CalibrationWindow: public Ui_CalibrationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONWINDOW_H
