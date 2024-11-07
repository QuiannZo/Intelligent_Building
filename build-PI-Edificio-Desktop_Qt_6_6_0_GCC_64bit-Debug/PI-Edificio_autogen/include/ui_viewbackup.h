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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewBackup
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton1_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ViewBackup)
    {
        if (ViewBackup->objectName().isEmpty())
            ViewBackup->setObjectName("ViewBackup");
        ViewBackup->resize(1000, 600);
        centralwidget = new QWidget(ViewBackup);
        centralwidget->setObjectName("centralwidget");
        pushButton1_2 = new QPushButton(centralwidget);
        pushButton1_2->setObjectName("pushButton1_2");
        pushButton1_2->setGeometry(QRect(20, 10, 141, 26));
        QFont font;
        font.setBold(true);
        pushButton1_2->setFont(font);
        pushButton1_2->setStyleSheet(QString::fromUtf8("    QPushButton {\n"
"        background-color: white;\n"
"        color: #007ACC; /* Text color */\n"
"        border-radius: 25px; /* Rounded corners */\n"
"        font-weight: bold;\n"
"        font-size: 16px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #E0E0E0; /* Hover effect */\n"
"        box-shadow: 0px 4px 8px rgba(0, 0, 0, 0.2);\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #B0B0B0; /* Click effect */\n"
"    }"));
        ViewBackup->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ViewBackup);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 23));
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
        pushButton1_2->setText(QCoreApplication::translate("ViewBackup", "Return", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewBackup: public Ui_ViewBackup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWBACKUP_H
