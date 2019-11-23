/********************************************************************************
** Form generated from reading UI file 'gestureeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTUREEDITOR_H
#define UI_GESTUREEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
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
            GestureEditor->setObjectName(QStringLiteral("GestureEditor"));
        GestureEditor->resize(800, 639);
        centralwidget = new QWidget(GestureEditor);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        angleCiteriaList = new QListView(centralwidget);
        angleCiteriaList->setObjectName(QStringLiteral("angleCiteriaList"));
        angleCiteriaList->setGeometry(QRect(70, 370, 256, 61));
        angleCiteriaList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        zEdit = new QLineEdit(centralwidget);
        zEdit->setObjectName(QStringLiteral("zEdit"));
        zEdit->setGeometry(QRect(660, 310, 61, 20));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(80, 450, 141, 16));
        updateGestureButton = new QPushButton(centralwidget);
        updateGestureButton->setObjectName(QStringLiteral("updateGestureButton"));
        updateGestureButton->setGeometry(QRect(600, 90, 71, 31));
        gestureList = new QListView(centralwidget);
        gestureList->setObjectName(QStringLiteral("gestureList"));
        gestureList->setGeometry(QRect(70, 51, 256, 181));
        gestureList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        axisBox = new QComboBox(centralwidget);
        axisBox->setObjectName(QStringLiteral("axisBox"));
        axisBox->setGeometry(QRect(380, 310, 69, 22));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(470, 310, 16, 20));
        updateMoveButton = new QPushButton(centralwidget);
        updateMoveButton->setObjectName(QStringLiteral("updateMoveButton"));
        updateMoveButton->setGeometry(QRect(560, 470, 71, 31));
        loadLibButton = new QPushButton(centralwidget);
        loadLibButton->setObjectName(QStringLiteral("loadLibButton"));
        loadLibButton->setGeometry(QRect(400, 30, 101, 41));
        deleteAxisButton = new QPushButton(centralwidget);
        deleteAxisButton->setObjectName(QStringLiteral("deleteAxisButton"));
        deleteAxisButton->setGeometry(QRect(470, 270, 71, 31));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(490, 410, 31, 20));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(390, 140, 31, 16));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(510, 510, 51, 20));
        saveLibButton = new QPushButton(centralwidget);
        saveLibButton->setObjectName(QStringLiteral("saveLibButton"));
        saveLibButton->setGeometry(QRect(510, 30, 91, 41));
        newAxisButton = new QPushButton(centralwidget);
        newAxisButton->setObjectName(QStringLiteral("newAxisButton"));
        newAxisButton->setGeometry(QRect(380, 270, 71, 31));
        angleEdit = new QLineEdit(centralwidget);
        angleEdit->setObjectName(QStringLiteral("angleEdit"));
        angleEdit->setGeometry(QRect(530, 410, 113, 20));
        angleEdit->setInputMethodHints(Qt::ImhDigitsOnly);
        addDefaultButton = new QPushButton(centralwidget);
        addDefaultButton->setObjectName(QStringLiteral("addDefaultButton"));
        addDefaultButton->setGeometry(QRect(610, 30, 91, 41));
        newAngleButton = new QPushButton(centralwidget);
        newAngleButton->setObjectName(QStringLiteral("newAngleButton"));
        newAngleButton->setGeometry(QRect(380, 370, 71, 31));
        commandEdit = new QLineEdit(centralwidget);
        commandEdit->setObjectName(QStringLiteral("commandEdit"));
        commandEdit->setGeometry(QRect(580, 140, 113, 20));
        updateAxisButton = new QPushButton(centralwidget);
        updateAxisButton->setObjectName(QStringLiteral("updateAxisButton"));
        updateAxisButton->setGeometry(QRect(560, 270, 71, 31));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(530, 140, 51, 20));
        deleteMoveButton = new QPushButton(centralwidget);
        deleteMoveButton->setObjectName(QStringLiteral("deleteMoveButton"));
        deleteMoveButton->setGeometry(QRect(470, 470, 71, 31));
        descriptionEdit = new QPlainTextEdit(centralwidget);
        descriptionEdit->setObjectName(QStringLiteral("descriptionEdit"));
        descriptionEdit->setEnabled(true);
        descriptionEdit->setGeometry(QRect(420, 170, 271, 71));
        descriptionEdit->setOverwriteMode(true);
        updateAngleButton = new QPushButton(centralwidget);
        updateAngleButton->setObjectName(QStringLiteral("updateAngleButton"));
        updateAngleButton->setGeometry(QRect(560, 370, 71, 31));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(560, 310, 16, 20));
        deleteAngleButton = new QPushButton(centralwidget);
        deleteAngleButton->setObjectName(QStringLiteral("deleteAngleButton"));
        deleteAngleButton->setGeometry(QRect(470, 370, 71, 31));
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(350, 170, 71, 20));
        jointBox = new QComboBox(centralwidget);
        jointBox->setObjectName(QStringLiteral("jointBox"));
        jointBox->setGeometry(QRect(380, 410, 69, 22));
        deleteGestureButton = new QPushButton(centralwidget);
        deleteGestureButton->setObjectName(QStringLiteral("deleteGestureButton"));
        deleteGestureButton->setGeometry(QRect(510, 90, 71, 31));
        xEdit = new QLineEdit(centralwidget);
        xEdit->setObjectName(QStringLiteral("xEdit"));
        xEdit->setGeometry(QRect(480, 310, 61, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 350, 111, 16));
        yEdit = new QLineEdit(centralwidget);
        yEdit->setObjectName(QStringLiteral("yEdit"));
        yEdit->setGeometry(QRect(570, 310, 61, 20));
        nameEdit = new QLineEdit(centralwidget);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));
        nameEdit->setGeometry(QRect(420, 140, 91, 20));
        newMoveButton = new QPushButton(centralwidget);
        newMoveButton->setObjectName(QStringLiteral("newMoveButton"));
        newMoveButton->setGeometry(QRect(380, 470, 71, 31));
        moveBox = new QComboBox(centralwidget);
        moveBox->setObjectName(QStringLiteral("moveBox"));
        moveBox->setGeometry(QRect(570, 510, 69, 22));
        axisCiteriaList = new QListView(centralwidget);
        axisCiteriaList->setObjectName(QStringLiteral("axisCiteriaList"));
        axisCiteriaList->setGeometry(QRect(70, 270, 256, 61));
        axisCiteriaList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        jointBox2 = new QComboBox(centralwidget);
        jointBox2->setObjectName(QStringLiteral("jointBox2"));
        jointBox2->setGeometry(QRect(380, 510, 69, 22));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 30, 111, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(650, 310, 16, 20));
        newGestureButton = new QPushButton(centralwidget);
        newGestureButton->setObjectName(QStringLiteral("newGestureButton"));
        newGestureButton->setGeometry(QRect(420, 90, 71, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 250, 111, 16));
        movementCiteriaList = new QListView(centralwidget);
        movementCiteriaList->setObjectName(QStringLiteral("movementCiteriaList"));
        movementCiteriaList->setGeometry(QRect(70, 470, 256, 61));
        movementCiteriaList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(80, 550, 141, 16));
        EMGBox = new QComboBox(centralwidget);
        EMGBox->setObjectName(QStringLiteral("EMGBox"));
        EMGBox->setGeometry(QRect(170, 550, 69, 22));
        updateEMGButton = new QPushButton(centralwidget);
        updateEMGButton->setObjectName(QStringLiteral("updateEMGButton"));
        updateEMGButton->setGeometry(QRect(250, 540, 71, 31));
        GestureEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GestureEditor);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        GestureEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(GestureEditor);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        GestureEditor->setStatusBar(statusbar);

        retranslateUi(GestureEditor);

        QMetaObject::connectSlotsByName(GestureEditor);
    } // setupUi

    void retranslateUi(QMainWindow *GestureEditor)
    {
        GestureEditor->setWindowTitle(QApplication::translate("GestureEditor", "\346\211\213\345\212\277\347\274\226\350\276\221\345\231\250", 0));
        label_4->setText(QApplication::translate("GestureEditor", "Movement Citeria List", 0));
        updateGestureButton->setText(QApplication::translate("GestureEditor", "Update", 0));
        label_5->setText(QApplication::translate("GestureEditor", "x", 0));
        updateMoveButton->setText(QApplication::translate("GestureEditor", "Update", 0));
        loadLibButton->setText(QApplication::translate("GestureEditor", "Load Library", 0));
        deleteAxisButton->setText(QApplication::translate("GestureEditor", "Delete", 0));
        label_8->setText(QApplication::translate("GestureEditor", "Angle", 0));
        label_10->setText(QApplication::translate("GestureEditor", "Name", 0));
        label_9->setText(QApplication::translate("GestureEditor", "Movement", 0));
        saveLibButton->setText(QApplication::translate("GestureEditor", "Save Library", 0));
        newAxisButton->setText(QApplication::translate("GestureEditor", "New", 0));
        addDefaultButton->setText(QApplication::translate("GestureEditor", "Add Defaults", 0));
        newAngleButton->setText(QApplication::translate("GestureEditor", "New", 0));
        updateAxisButton->setText(QApplication::translate("GestureEditor", "Update", 0));
        label_11->setText(QApplication::translate("GestureEditor", "Command", 0));
        deleteMoveButton->setText(QApplication::translate("GestureEditor", "Delete", 0));
        descriptionEdit->setPlainText(QString());
        updateAngleButton->setText(QApplication::translate("GestureEditor", "Update", 0));
        label_6->setText(QApplication::translate("GestureEditor", "y", 0));
        deleteAngleButton->setText(QApplication::translate("GestureEditor", "Delete", 0));
        label_12->setText(QApplication::translate("GestureEditor", "Description", 0));
        deleteGestureButton->setText(QApplication::translate("GestureEditor", "Delete", 0));
        label_3->setText(QApplication::translate("GestureEditor", "Angle Citeria List", 0));
        newMoveButton->setText(QApplication::translate("GestureEditor", "New", 0));
        label->setText(QApplication::translate("GestureEditor", "Gesture List", 0));
        label_7->setText(QApplication::translate("GestureEditor", "z", 0));
        newGestureButton->setText(QApplication::translate("GestureEditor", "New", 0));
        label_2->setText(QApplication::translate("GestureEditor", "Axis Citeria List", 0));
        label_13->setText(QApplication::translate("GestureEditor", "EMG Citerion", 0));
        updateEMGButton->setText(QApplication::translate("GestureEditor", "Update", 0));
    } // retranslateUi

};

namespace Ui {
    class GestureEditor: public Ui_GestureEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTUREEDITOR_H
