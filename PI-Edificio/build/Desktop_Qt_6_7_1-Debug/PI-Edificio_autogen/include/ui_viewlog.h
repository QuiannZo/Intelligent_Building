/********************************************************************************
** Form generated from reading UI file 'viewlog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWLOG_H
#define UI_VIEWLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewLog
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *viewLog)
    {
        if (viewLog->objectName().isEmpty())
            viewLog->setObjectName("viewLog");
        viewLog->resize(1000, 600);
        centralwidget = new QWidget(viewLog);
        centralwidget->setObjectName("centralwidget");
        viewLog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(viewLog);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        viewLog->setMenuBar(menubar);
        statusbar = new QStatusBar(viewLog);
        statusbar->setObjectName("statusbar");
        viewLog->setStatusBar(statusbar);

        retranslateUi(viewLog);

        QMetaObject::connectSlotsByName(viewLog);
    } // setupUi

    void retranslateUi(QMainWindow *viewLog)
    {
        viewLog->setWindowTitle(QCoreApplication::translate("viewLog", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewLog: public Ui_viewLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWLOG_H
