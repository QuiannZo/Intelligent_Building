/********************************************************************************
** Form generated from reading UI file 'viewbackup.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWBACKUP_H
#define UI_VIEWBACKUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewBackup
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ViewBackup)
    {
        if (ViewBackup->objectName().isEmpty())
            ViewBackup->setObjectName("ViewBackup");
        ViewBackup->resize(1000, 600);
        centralwidget = new QWidget(ViewBackup);
        centralwidget->setObjectName("centralwidget");
        ViewBackup->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ViewBackup);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        ViewBackup->setMenuBar(menubar);
        statusbar = new QStatusBar(ViewBackup);
        statusbar->setObjectName("statusbar");
        ViewBackup->setStatusBar(statusbar);

        retranslateUi(ViewBackup);

        QMetaObject::connectSlotsByName(ViewBackup);
    } // setupUi

    void retranslateUi(QMainWindow *ViewBackup)
    {
        ViewBackup->setWindowTitle(QCoreApplication::translate("ViewBackup", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewBackup: public Ui_ViewBackup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWBACKUP_H
