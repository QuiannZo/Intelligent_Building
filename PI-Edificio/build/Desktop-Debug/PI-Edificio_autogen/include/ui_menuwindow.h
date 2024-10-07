/********************************************************************************
** Form generated from reading UI file 'menuwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWINDOW_H
#define UI_MENUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menuwindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *menuwindow)
    {
        if (menuwindow->objectName().isEmpty())
            menuwindow->setObjectName("menuwindow");
        menuwindow->resize(800, 600);
        centralwidget = new QWidget(menuwindow);
        centralwidget->setObjectName("centralwidget");
        menuwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(menuwindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(menuwindow);
        statusbar->setObjectName("statusbar");
        menuwindow->setStatusBar(statusbar);

        retranslateUi(menuwindow);

        QMetaObject::connectSlotsByName(menuwindow);
    } // setupUi

    void retranslateUi(QMainWindow *menuwindow)
    {
        menuwindow->setWindowTitle(QCoreApplication::translate("menuwindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menuwindow: public Ui_menuwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWINDOW_H
