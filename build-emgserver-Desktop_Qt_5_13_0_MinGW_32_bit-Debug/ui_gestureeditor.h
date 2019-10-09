/********************************************************************************
** Form generated from reading UI file 'gestureeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTUREEDITOR_H
#define UI_GESTUREEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestureEditor
{
public:
    QWidget *centralwidget;
    QListView *angleCiteriaList;
    QLineEdit *zEdit;
    QLabel *label_4;
    QPushButton *updateGestureButton;
    QListView *gestureList;
    QComboBox *axisBox;
    QLabel *label_5;
    QPushButton *updateMoveButton;
    QPushButton *loadLibButton;
    QPushButton *deleteAxisButton;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_9;
    QPushButton *saveLibButton;
    QPushButton *newAxisButton;
    QLineEdit *angleEdit;
    QPushButton *addDefaultButton;
    QPushButton *newAngleButton;
    QLineEdit *commandEdit;
    QPushButton *updateAxisButton;
    QLabel *label_11;
    QPushButton *deleteMoveButton;
    QPlainTextEdit *descriptionEdit;
    QPushButton *updateAngleButton;
    QLabel *label_6;
    QPushButton *deleteAngleButton;
    QLabel *label_12;
    QComboBox *jointBox;
    QPushButton *deleteGestureButton;
    QLineEdit *xEdit;
    QLabel *label_3;
    QLineEdit *yEdit;
    QLineEdit *nameEdit;
    QPushButton *newMoveButton;
    QComboBox *moveBox;
    QListView *axisCiteriaList;
    QComboBox *jointBox2;
    QLabel *label;
    QLabel *label_7;
    QPushButton *newGestureButton;
    QLabel *label_2;
    QListView *movementCiteriaList;
    QLabel *label_13;
    QComboBox *EMGBox;
    QPushButton *updateEMGButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GestureEditor)
    {
        if (GestureEditor->objectName().isEmpty())
            GestureEditor->setObjectName(QString::fromUtf8("GestureEditor"));
        GestureEditor->resize(800, 639);
        centralwidget = new QWidget(GestureEditor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        angleCiteriaList = new QListView(centralwidget);
        angleCiteriaList->setObjectName(QString::fromUtf8("angleCiteriaList"));
        angleCiteriaList->setGeometry(QRect(70, 370, 256, 61));
        angleCiteriaList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        zEdit = new QLineEdit(centralwidget);
        zEdit->setObjectName(QString::fromUtf8("zEdit"));
        zEdit->setGeometry(QRect(660, 310, 61, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 450, 141, 16));
        updateGestureButton = new QPushButton(centralwidget);
        updateGestureButton->setObjectName(QString::fromUtf8("updateGestureButton"));
        updateGestureButton->setGeometry(QRect(600, 90, 71, 31));
        gestureList = new QListView(centralwidget);
        gestureList->setObjectName(QString::fromUtf8("gestureList"));
        gestureList->setGeometry(QRect(70, 51, 256, 181));
        gestureList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        axisBox = new QComboBox(centralwidget);
        axisBox->setObjectName(QString::fromUtf8("axisBox"));
        axisBox->setGeometry(QRect(380, 310, 69, 22));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(470, 310, 16, 20));
        updateMoveButton = new QPushButton(centralwidget);
        updateMoveButton->setObjectName(QString::fromUtf8("updateMoveButton"));
        updateMoveButton->setGeometry(QRect(560, 470, 71, 31));
        loadLibButton = new QPushButton(centralwidget);
        loadLibButton->setObjectName(QString::fromUtf8("loadLibButton"));
        loadLibButton->setGeometry(QRect(400, 30, 101, 41));
        deleteAxisButton = new QPushButton(centralwidget);
        deleteAxisButton->setObjectName(QString::fromUtf8("deleteAxisButton"));
        deleteAxisButton->setGeometry(QRect(470, 270, 71, 31));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(490, 410, 31, 20));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(390, 140, 31, 16));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(510, 510, 51, 20));
        saveLibButton = new QPushButton(centralwidget);
        saveLibButton->setObjectName(QString::fromUtf8("saveLibButton"));
        saveLibButton->setGeometry(QRect(510, 30, 91, 41));
        newAxisButton = new QPushButton(centralwidget);
        newAxisButton->setObjectName(QString::fromUtf8("newAxisButton"));
        newAxisButton->setGeometry(QRect(380, 270, 71, 31));
        angleEdit = new QLineEdit(centralwidget);
        angleEdit->setObjectName(QString::fromUtf8("angleEdit"));
        angleEdit->setGeometry(QRect(530, 410, 113, 20));
        angleEdit->setInputMethodHints(Qt::ImhDigitsOnly);
        addDefaultButton = new QPushButton(centralwidget);
        addDefaultButton->setObjectName(QString::fromUtf8("addDefaultButton"));
        addDefaultButton->setGeometry(QRect(610, 30, 91, 41));
        newAngleButton = new QPushButton(centralwidget);
        newAngleButton->setObjectName(QString::fromUtf8("newAngleButton"));
        newAngleButton->setGeometry(QRect(380, 370, 71, 31));
        commandEdit = new QLineEdit(centralwidget);
        commandEdit->setObjectName(QString::fromUtf8("commandEdit"));
        commandEdit->setGeometry(QRect(580, 140, 113, 20));
        updateAxisButton = new QPushButton(centralwidget);
        updateAxisButton->setObjectName(QString::fromUtf8("updateAxisButton"));
        updateAxisButton->setGeometry(QRect(560, 270, 71, 31));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(530, 140, 51, 20));
        deleteMoveButton = new QPushButton(centralwidget);
        deleteMoveButton->setObjectName(QString::fromUtf8("deleteMoveButton"));
        deleteMoveButton->setGeometry(QRect(470, 470, 71, 31));
        descriptionEdit = new QPlainTextEdit(centralwidget);
        descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));
        descriptionEdit->setEnabled(true);
        descriptionEdit->setGeometry(QRect(420, 170, 271, 71));
        descriptionEdit->setOverwriteMode(true);
        updateAngleButton = new QPushButton(centralwidget);
        updateAngleButton->setObjectName(QString::fromUtf8("updateAngleButton"));
        updateAngleButton->setGeometry(QRect(560, 370, 71, 31));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(560, 310, 16, 20));
        deleteAngleButton = new QPushButton(centralwidget);
        deleteAngleButton->setObjectName(QString::fromUtf8("deleteAngleButton"));
        deleteAngleButton->setGeometry(QRect(470, 370, 71, 31));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(350, 170, 71, 20));
        jointBox = new QComboBox(centralwidget);
        jointBox->setObjectName(QString::fromUtf8("jointBox"));
        jointBox->setGeometry(QRect(380, 410, 69, 22));
        deleteGestureButton = new QPushButton(centralwidget);
        deleteGestureButton->setObjectName(QString::fromUtf8("deleteGestureButton"));
        deleteGestureButton->setGeometry(QRect(510, 90, 71, 31));
        xEdit = new QLineEdit(centralwidget);
        xEdit->setObjectName(QString::fromUtf8("xEdit"));
        xEdit->setGeometry(QRect(480, 310, 61, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 350, 111, 16));
        yEdit = new QLineEdit(centralwidget);
        yEdit->setObjectName(QString::fromUtf8("yEdit"));
        yEdit->setGeometry(QRect(570, 310, 61, 20));
        nameEdit = new QLineEdit(centralwidget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setGeometry(QRect(420, 140, 91, 20));
        newMoveButton = new QPushButton(centralwidget);
        newMoveButton->setObjectName(QString::fromUtf8("newMoveButton"));
        newMoveButton->setGeometry(QRect(380, 470, 71, 31));
        moveBox = new QComboBox(centralwidget);
        moveBox->setObjectName(QString::fromUtf8("moveBox"));
        moveBox->setGeometry(QRect(570, 510, 69, 22));
        axisCiteriaList = new QListView(centralwidget);
        axisCiteriaList->setObjectName(QString::fromUtf8("axisCiteriaList"));
        axisCiteriaList->setGeometry(QRect(70, 270, 256, 61));
        axisCiteriaList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        jointBox2 = new QComboBox(centralwidget);
        jointBox2->setObjectName(QString::fromUtf8("jointBox2"));
        jointBox2->setGeometry(QRect(380, 510, 69, 22));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 30, 111, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(650, 310, 16, 20));
        newGestureButton = new QPushButton(centralwidget);
        newGestureButton->setObjectName(QString::fromUtf8("newGestureButton"));
        newGestureButton->setGeometry(QRect(420, 90, 71, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 250, 111, 16));
        movementCiteriaList = new QListView(centralwidget);
        movementCiteriaList->setObjectName(QString::fromUtf8("movementCiteriaList"));
        movementCiteriaList->setGeometry(QRect(70, 470, 256, 61));
        movementCiteriaList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(80, 550, 141, 16));
        EMGBox = new QComboBox(centralwidget);
        EMGBox->setObjectName(QString::fromUtf8("EMGBox"));
        EMGBox->setGeometry(QRect(170, 550, 69, 22));
        updateEMGButton = new QPushButton(centralwidget);
        updateEMGButton->setObjectName(QString::fromUtf8("updateEMGButton"));
        updateEMGButton->setGeometry(QRect(250, 540, 71, 31));
        GestureEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GestureEditor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        GestureEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(GestureEditor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GestureEditor->setStatusBar(statusbar);

        retranslateUi(GestureEditor);

        QMetaObject::connectSlotsByName(GestureEditor);
    } // setupUi

    void retranslateUi(QMainWindow *GestureEditor)
    {
        GestureEditor->setWindowTitle(QCoreApplication::translate("GestureEditor", "\346\211\213\345\212\277\347\274\226\350\276\221\345\231\250", nullptr));
        label_4->setText(QCoreApplication::translate("GestureEditor", "Movement Citeria List", nullptr));
        updateGestureButton->setText(QCoreApplication::translate("GestureEditor", "Update", nullptr));
        label_5->setText(QCoreApplication::translate("GestureEditor", "x", nullptr));
        updateMoveButton->setText(QCoreApplication::translate("GestureEditor", "Update", nullptr));
        loadLibButton->setText(QCoreApplication::translate("GestureEditor", "Load Library", nullptr));
        deleteAxisButton->setText(QCoreApplication::translate("GestureEditor", "Delete", nullptr));
        label_8->setText(QCoreApplication::translate("GestureEditor", "Angle", nullptr));
        label_10->setText(QCoreApplication::translate("GestureEditor", "Name", nullptr));
        label_9->setText(QCoreApplication::translate("GestureEditor", "Movement", nullptr));
        saveLibButton->setText(QCoreApplication::translate("GestureEditor", "Save Library", nullptr));
        newAxisButton->setText(QCoreApplication::translate("GestureEditor", "New", nullptr));
        addDefaultButton->setText(QCoreApplication::translate("GestureEditor", "Add Defaults", nullptr));
        newAngleButton->setText(QCoreApplication::translate("GestureEditor", "New", nullptr));
        updateAxisButton->setText(QCoreApplication::translate("GestureEditor", "Update", nullptr));
        label_11->setText(QCoreApplication::translate("GestureEditor", "Command", nullptr));
        deleteMoveButton->setText(QCoreApplication::translate("GestureEditor", "Delete", nullptr));
        descriptionEdit->setPlainText(QString());
        updateAngleButton->setText(QCoreApplication::translate("GestureEditor", "Update", nullptr));
        label_6->setText(QCoreApplication::translate("GestureEditor", "y", nullptr));
        deleteAngleButton->setText(QCoreApplication::translate("GestureEditor", "Delete", nullptr));
        label_12->setText(QCoreApplication::translate("GestureEditor", "Description", nullptr));
        deleteGestureButton->setText(QCoreApplication::translate("GestureEditor", "Delete", nullptr));
        label_3->setText(QCoreApplication::translate("GestureEditor", "Angle Citeria List", nullptr));
        newMoveButton->setText(QCoreApplication::translate("GestureEditor", "New", nullptr));
        label->setText(QCoreApplication::translate("GestureEditor", "Gesture List", nullptr));
        label_7->setText(QCoreApplication::translate("GestureEditor", "z", nullptr));
        newGestureButton->setText(QCoreApplication::translate("GestureEditor", "New", nullptr));
        label_2->setText(QCoreApplication::translate("GestureEditor", "Axis Citeria List", nullptr));
        label_13->setText(QCoreApplication::translate("GestureEditor", "EMG Citerion", nullptr));
        updateEMGButton->setText(QCoreApplication::translate("GestureEditor", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GestureEditor: public Ui_GestureEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTUREEDITOR_H
