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
        pushButton8->setGeometry(QRect(130, 130, 191, 131));
        pushButton8->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(160, 230, 141, 20));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8("color: white;"));
        pushButton8_2 = new QPushButton(centralwidget);
        pushButton8_2->setObjectName("pushButton8_2");
        pushButton8_2->setGeometry(QRect(350, 340, 191, 131));
        pushButton8_2->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(370, 440, 151, 20));
        label_14->setFont(font);
        label_14->setStyleSheet(QString::fromUtf8("color: white;"));
        pushButton8_3 = new QPushButton(centralwidget);
        pushButton8_3->setObjectName("pushButton8_3");
        pushButton8_3->setGeometry(QRect(570, 130, 191, 131));
        pushButton8_3->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(610, 230, 121, 20));
        label_15->setFont(font);
        label_15->setStyleSheet(QString::fromUtf8("color: white;"));
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
        pushButton8->setText(QString());
        label_13->setText(QCoreApplication::translate("viewdatabasewindow", "View Sensor Building", nullptr));
        pushButton8_2->setText(QString());
        label_14->setText(QCoreApplication::translate("viewdatabasewindow", "View Node Information", nullptr));
        pushButton8_3->setText(QString());
        label_15->setText(QCoreApplication::translate("viewdatabasewindow", "View Sensor Floor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewdatabasewindow: public Ui_viewdatabasewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWDATABASEWINDOW_H
