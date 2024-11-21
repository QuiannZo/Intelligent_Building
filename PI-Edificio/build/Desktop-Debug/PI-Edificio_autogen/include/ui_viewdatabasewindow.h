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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewdatabasewindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton8;
    QPushButton *pushButton1_2;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *viewdatabasewindow)
    {
        if (viewdatabasewindow->objectName().isEmpty())
            viewdatabasewindow->setObjectName("viewdatabasewindow");
        viewdatabasewindow->resize(1000, 600);
        centralwidget = new QWidget(viewdatabasewindow);
        centralwidget->setObjectName("centralwidget");
        pushButton8 = new QPushButton(centralwidget);
        pushButton8->setObjectName("pushButton8");
        pushButton8->setGeometry(QRect(120, 90, 211, 41));
        pushButton8->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
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
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(120, 130, 761, 421));
        viewdatabasewindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(viewdatabasewindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
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
        pushButton8->setText(QCoreApplication::translate("viewdatabasewindow", "View Sensor Database", nullptr));
        pushButton1_2->setText(QCoreApplication::translate("viewdatabasewindow", "Return", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewdatabasewindow: public Ui_viewdatabasewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWDATABASEWINDOW_H
