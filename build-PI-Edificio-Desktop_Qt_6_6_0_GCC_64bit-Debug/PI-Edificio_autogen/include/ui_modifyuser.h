/********************************************************************************
** Form generated from reading UI file 'modifyuser.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYUSER_H
#define UI_MODIFYUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
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
    QPushButton *pushButton1;
    QPushButton *pushButton1_2;
    QComboBox *comboBox;
    QLabel *name;
    QLabel *lastName;
    QLabel *username;
    QLineEdit *apellido;
    QLineEdit *nombre_3;
    QLineEdit *user;
    QListWidget *listWidget;
    QLabel *nombre_2;
    QLineEdit *password;
    QLabel *lastName_2;
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
        widgetUser->setGeometry(QRect(790, 30, 71, 61));
        nombre = new QLabel(centralwidget);
        nombre->setObjectName("nombre");
        nombre->setGeometry(QRect(310, 120, 61, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        nombre->setPalette(palette);
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        nombre->setFont(font);
        pushButton1 = new QPushButton(centralwidget);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(260, 490, 151, 41));
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
        pushButton1_2 = new QPushButton(centralwidget);
        pushButton1_2->setObjectName("pushButton1_2");
        pushButton1_2->setGeometry(QRect(10, 10, 141, 26));
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
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(250, 160, 161, 26));
        name = new QLabel(centralwidget);
        name->setObjectName("name");
        name->setGeometry(QRect(300, 270, 61, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        name->setPalette(palette1);
        name->setFont(font);
        lastName = new QLabel(centralwidget);
        lastName->setObjectName("lastName");
        lastName->setGeometry(QRect(280, 330, 111, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        lastName->setPalette(palette2);
        lastName->setFont(font);
        username = new QLabel(centralwidget);
        username->setObjectName("username");
        username->setGeometry(QRect(280, 210, 111, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        username->setPalette(palette3);
        username->setFont(font);
        apellido = new QLineEdit(centralwidget);
        apellido->setObjectName("apellido");
        apellido->setGeometry(QRect(220, 360, 221, 26));
        nombre_3 = new QLineEdit(centralwidget);
        nombre_3->setObjectName("nombre_3");
        nombre_3->setGeometry(QRect(220, 300, 221, 26));
        user = new QLineEdit(centralwidget);
        user->setObjectName("user");
        user->setGeometry(QRect(220, 240, 221, 26));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(700, 140, 256, 391));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        listWidget->setFont(font2);
        nombre_2 = new QLabel(centralwidget);
        nombre_2->setObjectName("nombre_2");
        nombre_2->setGeometry(QRect(770, 100, 121, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        nombre_2->setPalette(palette4);
        nombre_2->setFont(font);
        password = new QLineEdit(centralwidget);
        password->setObjectName("password");
        password->setGeometry(QRect(220, 430, 221, 26));
        lastName_2 = new QLabel(centralwidget);
        lastName_2->setObjectName("lastName_2");
        lastName_2->setGeometry(QRect(280, 400, 111, 31));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        lastName_2->setPalette(palette5);
        lastName_2->setFont(font);
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
        nombre->setText(QCoreApplication::translate("ModifyUser", "Role", nullptr));
        pushButton1->setText(QCoreApplication::translate("ModifyUser", "Guardar", nullptr));
        pushButton1_2->setText(QCoreApplication::translate("ModifyUser", "Return", nullptr));
        name->setText(QCoreApplication::translate("ModifyUser", "Name", nullptr));
        lastName->setText(QCoreApplication::translate("ModifyUser", "Last Name", nullptr));
        username->setText(QCoreApplication::translate("ModifyUser", "Username", nullptr));
        nombre_2->setText(QCoreApplication::translate("ModifyUser", "Select user", nullptr));
        password->setText(QString());
        lastName_2->setText(QCoreApplication::translate("ModifyUser", "Password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModifyUser: public Ui_ModifyUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYUSER_H
