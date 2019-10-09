/********************************************************************************
** Form generated from reading UI file 'camerawindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAWINDOW_H
#define UI_CAMERAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QMainWindow *CameraWindow)
    {
        if (CameraWindow->objectName().isEmpty())
            CameraWindow->setObjectName(QString::fromUtf8("CameraWindow"));
        CameraWindow->resize(537, 414);
        CameraWindow->setMinimumSize(QSize(358, 276));
        CameraWindow->setMaximumSize(QSize(537, 414));
        centralwidget = new QWidget(CameraWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 521, 391));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        CameraWindow->setCentralWidget(centralwidget);

        retranslateUi(CameraWindow);

        QMetaObject::connectSlotsByName(CameraWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CameraWindow)
    {
        CameraWindow->setWindowTitle(QCoreApplication::translate("CameraWindow", "Camera", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraWindow: public Ui_CameraWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAWINDOW_H
