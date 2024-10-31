/********************************************************************************
** Form generated from reading UI file 'removeuser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOVEUSER_H
#define UI_REMOVEUSER_H

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

class Ui_RemoveUser
{
public:
    QWidget *centralwidget;
    QWidget *widgetUser;
    QLabel *nombre;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton1;
    QPushButton *pushButton1_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RemoveUser)
    {
        if (RemoveUser->objectName().isEmpty())
            RemoveUser->setObjectName("RemoveUser");
        RemoveUser->resize(1000, 600);
        centralwidget = new QWidget(RemoveUser);
        centralwidget->setObjectName("centralwidget");
        widgetUser = new QWidget(centralwidget);
        widgetUser->setObjectName("widgetUser");
        widgetUser->setGeometry(QRect(380, 60, 171, 151));
        nombre = new QLabel(centralwidget);
        nombre->setObjectName("nombre");
        nombre->setGeometry(QRect(380, 220, 181, 31));
        QFont font;
        font.setPointSize(16);
        nombre->setFont(font);
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(360, 250, 221, 26));
        pushButton1 = new QPushButton(centralwidget);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(390, 300, 151, 41));
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
        RemoveUser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RemoveUser);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 23));
        RemoveUser->setMenuBar(menubar);
        statusbar = new QStatusBar(RemoveUser);
        statusbar->setObjectName("statusbar");
        RemoveUser->setStatusBar(statusbar);

        retranslateUi(RemoveUser);

        QMetaObject::connectSlotsByName(RemoveUser);
    } // setupUi

    void retranslateUi(QMainWindow *RemoveUser)
    {
        RemoveUser->setWindowTitle(QCoreApplication::translate("RemoveUser", "MainWindow", nullptr));
        nombre->setText(QCoreApplication::translate("RemoveUser", "Usuario a eliminar: ", nullptr));
        pushButton1->setText(QCoreApplication::translate("RemoveUser", "Eliminar usuario", nullptr));
        pushButton1_2->setText(QCoreApplication::translate("RemoveUser", "Return", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoveUser: public Ui_RemoveUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOVEUSER_H
