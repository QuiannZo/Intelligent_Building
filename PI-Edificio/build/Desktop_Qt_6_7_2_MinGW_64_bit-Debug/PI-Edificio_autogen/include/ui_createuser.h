/********************************************************************************
** Form generated from reading UI file 'createuser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEUSER_H
#define UI_CREATEUSER_H

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

class Ui_createuser
{
public:
    QWidget *centralwidget;
    QWidget *widgetUser;
    QLabel *nombre;
    QLineEdit *lineEdit_2;
    QLabel *rol;
    QLabel *contrasena;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton1;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *createuser)
    {
        if (createuser->objectName().isEmpty())
            createuser->setObjectName("createuser");
        createuser->resize(1000, 600);
        centralwidget = new QWidget(createuser);
        centralwidget->setObjectName("centralwidget");
        widgetUser = new QWidget(centralwidget);
        widgetUser->setObjectName("widgetUser");
        widgetUser->setGeometry(QRect(380, 60, 171, 151));
        nombre = new QLabel(centralwidget);
        nombre->setObjectName("nombre");
        nombre->setGeometry(QRect(340, 230, 261, 31));
        QFont font;
        font.setPointSize(16);
        nombre->setFont(font);
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(360, 270, 221, 26));
        rol = new QLabel(centralwidget);
        rol->setObjectName("rol");
        rol->setGeometry(QRect(360, 370, 241, 31));
        rol->setFont(font);
        contrasena = new QLabel(centralwidget);
        contrasena->setObjectName("contrasena");
        contrasena->setGeometry(QRect(380, 300, 181, 31));
        contrasena->setFont(font);
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(360, 340, 221, 26));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(360, 410, 221, 26));
        pushButton1 = new QPushButton(centralwidget);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(400, 460, 141, 26));
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
        createuser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(createuser);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        createuser->setMenuBar(menubar);
        statusbar = new QStatusBar(createuser);
        statusbar->setObjectName("statusbar");
        createuser->setStatusBar(statusbar);

        retranslateUi(createuser);

        QMetaObject::connectSlotsByName(createuser);
    } // setupUi

    void retranslateUi(QMainWindow *createuser)
    {
        createuser->setWindowTitle(QCoreApplication::translate("createuser", "MainWindow", nullptr));
        nombre->setText(QCoreApplication::translate("createuser", "Ingrese nombre de usuario:", nullptr));
        rol->setText(QCoreApplication::translate("createuser", "Rol que se quiere asignar:", nullptr));
        contrasena->setText(QCoreApplication::translate("createuser", "Ingrese contrase\303\261a:", nullptr));
        pushButton1->setText(QCoreApplication::translate("createuser", "Agregar usuario", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createuser: public Ui_createuser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEUSER_H
