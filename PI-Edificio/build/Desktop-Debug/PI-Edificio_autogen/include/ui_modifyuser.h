/********************************************************************************
** Form generated from reading UI file 'modifyuser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYUSER_H
#define UI_MODIFYUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModifyUser
{
public:
    QWidget *centralwidget;
    QWidget *widgetUser;
    QLabel *nombre;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton1;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ModifyUser)
    {
        if (ModifyUser->objectName().isEmpty())
            ModifyUser->setObjectName("ModifyUser");
        ModifyUser->resize(1000, 600);
        centralwidget = new QWidget(ModifyUser);
        centralwidget->setObjectName("centralwidget");
        widgetUser = new QWidget(centralwidget);
        widgetUser->setObjectName("widgetUser");
        widgetUser->setGeometry(QRect(370, 50, 171, 151));
        nombre = new QLabel(centralwidget);
        nombre->setObjectName("nombre");
        nombre->setGeometry(QRect(400, 220, 121, 31));
        QFont font;
        font.setPointSize(16);
        nombre->setFont(font);
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(350, 260, 221, 26));
        pushButton1 = new QPushButton(centralwidget);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(380, 300, 151, 41));
        QFont font1;
        font1.setBold(true);
        pushButton1->setFont(font1);
        pushButton1->setStyleSheet(QString::fromUtf8("    QPushButton {\n"
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
        ModifyUser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ModifyUser);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        ModifyUser->setMenuBar(menubar);
        statusbar = new QStatusBar(ModifyUser);
        statusbar->setObjectName("statusbar");
        ModifyUser->setStatusBar(statusbar);

        retranslateUi(ModifyUser);

        QMetaObject::connectSlotsByName(ModifyUser);
    } // setupUi

    void retranslateUi(QMainWindow *ModifyUser)
    {
        ModifyUser->setWindowTitle(QCoreApplication::translate("ModifyUser", "MainWindow", nullptr));
        nombre->setText(QCoreApplication::translate("ModifyUser", "Cambiar rol:", nullptr));
        pushButton1->setText(QCoreApplication::translate("ModifyUser", "Guardar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModifyUser: public Ui_ModifyUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYUSER_H
