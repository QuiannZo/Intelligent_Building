/********************************************************************************
** Form generated from reading UI file 'viewdatabasewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWDATABASEWINDOW_H
#define UI_VIEWDATABASEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewdatabasewindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *viewdatabasewindow)
    {
        if (viewdatabasewindow->objectName().isEmpty())
            viewdatabasewindow->setObjectName("viewdatabasewindow");
        viewdatabasewindow->resize(1000, 600);
        centralwidget = new QWidget(viewdatabasewindow);
        centralwidget->setObjectName("centralwidget");
        viewdatabasewindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(viewdatabasewindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        viewdatabasewindow->setMenuBar(menubar);
        statusbar = new QStatusBar(viewdatabasewindow);
        statusbar->setObjectName("statusbar");
        viewdatabasewindow->setStatusBar(statusbar);

        retranslateUi(viewdatabasewindow);

        QMetaObject::connectSlotsByName(viewdatabasewindow);
    } // setupUi

    void retranslateUi(QMainWindow *viewdatabasewindow)
    {
        viewdatabasewindow->setWindowTitle(QCoreApplication::translate("viewdatabasewindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewdatabasewindow: public Ui_viewdatabasewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWDATABASEWINDOW_H
