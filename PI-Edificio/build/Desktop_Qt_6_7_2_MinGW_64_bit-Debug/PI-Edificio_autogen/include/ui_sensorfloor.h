/********************************************************************************
** Form generated from reading UI file 'sensorfloor.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORFLOOR_H
#define UI_SENSORFLOOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SensorFloor
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SensorFloor)
    {
        if (SensorFloor->objectName().isEmpty())
            SensorFloor->setObjectName("SensorFloor");
        SensorFloor->resize(1000, 600);
        centralwidget = new QWidget(SensorFloor);
        centralwidget->setObjectName("centralwidget");
        SensorFloor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SensorFloor);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        SensorFloor->setMenuBar(menubar);
        statusbar = new QStatusBar(SensorFloor);
        statusbar->setObjectName("statusbar");
        SensorFloor->setStatusBar(statusbar);

        retranslateUi(SensorFloor);

        QMetaObject::connectSlotsByName(SensorFloor);
    } // setupUi

    void retranslateUi(QMainWindow *SensorFloor)
    {
        SensorFloor->setWindowTitle(QCoreApplication::translate("SensorFloor", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SensorFloor: public Ui_SensorFloor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORFLOOR_H
