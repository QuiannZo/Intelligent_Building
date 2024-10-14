/********************************************************************************
** Form generated from reading UI file 'sensorbuilding.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORBUILDING_H
#define UI_SENSORBUILDING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sensorBuilding
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *sensorBuilding)
    {
        if (sensorBuilding->objectName().isEmpty())
            sensorBuilding->setObjectName("sensorBuilding");
        sensorBuilding->resize(1000, 600);
        centralwidget = new QWidget(sensorBuilding);
        centralwidget->setObjectName("centralwidget");
        sensorBuilding->setCentralWidget(centralwidget);
        menubar = new QMenuBar(sensorBuilding);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        sensorBuilding->setMenuBar(menubar);
        statusbar = new QStatusBar(sensorBuilding);
        statusbar->setObjectName("statusbar");
        sensorBuilding->setStatusBar(statusbar);

        retranslateUi(sensorBuilding);

        QMetaObject::connectSlotsByName(sensorBuilding);
    } // setupUi

    void retranslateUi(QMainWindow *sensorBuilding)
    {
        sensorBuilding->setWindowTitle(QCoreApplication::translate("sensorBuilding", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sensorBuilding: public Ui_sensorBuilding {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORBUILDING_H
