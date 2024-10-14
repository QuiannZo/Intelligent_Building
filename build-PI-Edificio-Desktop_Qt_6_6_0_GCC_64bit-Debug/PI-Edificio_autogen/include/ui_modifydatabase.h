/********************************************************************************
** Form generated from reading UI file 'modifydatabase.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYDATABASE_H
#define UI_MODIFYDATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModifyDataBase
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton8;
    QPushButton *pushButton8_2;
    QPushButton *pushButton8_3;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ModifyDataBase)
    {
        if (ModifyDataBase->objectName().isEmpty())
            ModifyDataBase->setObjectName("ModifyDataBase");
        ModifyDataBase->resize(1000, 600);
        centralwidget = new QWidget(ModifyDataBase);
        centralwidget->setObjectName("centralwidget");
        pushButton8 = new QPushButton(centralwidget);
        pushButton8->setObjectName("pushButton8");
        pushButton8->setGeometry(QRect(170, 90, 191, 131));
        pushButton8->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        pushButton8_2 = new QPushButton(centralwidget);
        pushButton8_2->setObjectName("pushButton8_2");
        pushButton8_2->setGeometry(QRect(560, 90, 191, 131));
        pushButton8_2->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        pushButton8_3 = new QPushButton(centralwidget);
        pushButton8_3->setObjectName("pushButton8_3");
        pushButton8_3->setGeometry(QRect(360, 270, 191, 131));
        pushButton8_3->setStyleSheet(QString::fromUtf8("background-color: #32383D;\n"
"                                  color: white;\n"
"                                  }\n"
"                                  QPushButton:pressed {\n"
"                                  background-color: rgba(255, 255, 255, 0.2);"));
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(200, 190, 151, 20));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        label_13->setFont(font);
        label_13->setStyleSheet(QString::fromUtf8("color: white;"));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(380, 370, 161, 20));
        label_14->setFont(font);
        label_14->setStyleSheet(QString::fromUtf8("color: white;"));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(590, 190, 151, 20));
        label_15->setFont(font);
        label_15->setStyleSheet(QString::fromUtf8("color: white;"));
        ModifyDataBase->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ModifyDataBase);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        ModifyDataBase->setMenuBar(menubar);
        statusbar = new QStatusBar(ModifyDataBase);
        statusbar->setObjectName("statusbar");
        ModifyDataBase->setStatusBar(statusbar);

        retranslateUi(ModifyDataBase);

        QMetaObject::connectSlotsByName(ModifyDataBase);
    } // setupUi

    void retranslateUi(QMainWindow *ModifyDataBase)
    {
        ModifyDataBase->setWindowTitle(QCoreApplication::translate("ModifyDataBase", "MainWindow", nullptr));
        pushButton8->setText(QString());
        pushButton8_2->setText(QString());
        pushButton8_3->setText(QString());
        label_13->setText(QCoreApplication::translate("ModifyDataBase", "Modify Sensor Building", nullptr));
        label_14->setText(QCoreApplication::translate("ModifyDataBase", "Modify Node Information", nullptr));
        label_15->setText(QCoreApplication::translate("ModifyDataBase", "Modify Sensor Floor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModifyDataBase: public Ui_ModifyDataBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYDATABASE_H
