/********************************************************************************
** Form generated from reading UI file 'viewdatabasewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWDATABASEWINDOW_H
#define UI_VIEWDATABASEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewdatabasewindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton8;
    QLabel *label_13;
    QPushButton *pushButton8_2;
    QLabel *label_14;
    QPushButton *pushButton8_3;
    QLabel *label_15;
    QPushButton *pushButton1_2;
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
        pushButton8->setGeometry(QRect(140, 200, 191, 131));
        pushButton8->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(170, 300, 141, 20));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8("color: white;"));
        pushButton8_2 = new QPushButton(centralwidget);
        pushButton8_2->setObjectName("pushButton8_2");
        pushButton8_2->setGeometry(QRect(400, 200, 191, 131));
        pushButton8_2->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(420, 300, 151, 20));
        label_14->setFont(font);
        label_14->setStyleSheet(QString::fromUtf8("color: white;"));
        pushButton8_3 = new QPushButton(centralwidget);
        pushButton8_3->setObjectName("pushButton8_3");
        pushButton8_3->setGeometry(QRect(660, 200, 191, 131));
        pushButton8_3->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(700, 300, 121, 20));
        label_15->setFont(font);
        label_15->setStyleSheet(QString::fromUtf8("color: white;"));
        pushButton1_2 = new QPushButton(centralwidget);
        pushButton1_2->setObjectName("pushButton1_2");
        pushButton1_2->setGeometry(QRect(20, 10, 141, 26));
        QFont font1;
        font1.setBold(true);
        pushButton1_2->setFont(font1);
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
        viewdatabasewindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(viewdatabasewindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 23));
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
        pushButton8->setText(QString());
        label_13->setText(QCoreApplication::translate("viewdatabasewindow", "View Sensor Building", nullptr));
        pushButton8_2->setText(QString());
        label_14->setText(QCoreApplication::translate("viewdatabasewindow", "View Node Information", nullptr));
        pushButton8_3->setText(QString());
        label_15->setText(QCoreApplication::translate("viewdatabasewindow", "View Sensor Floor", nullptr));
        pushButton1_2->setText(QCoreApplication::translate("viewdatabasewindow", "Return", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewdatabasewindow: public Ui_viewdatabasewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWDATABASEWINDOW_H
