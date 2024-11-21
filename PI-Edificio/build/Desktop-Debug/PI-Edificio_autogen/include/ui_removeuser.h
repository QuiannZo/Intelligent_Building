/********************************************************************************
** Form generated from reading UI file 'removeuser.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOVEUSER_H
#define UI_REMOVEUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
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
    QPushButton *pushButton1;
    QPushButton *pushButton1_2;
    QListWidget *listWidget;
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
        widgetUser->setGeometry(QRect(430, 40, 81, 71));
        nombre = new QLabel(centralwidget);
        nombre->setObjectName("nombre");
        nombre->setGeometry(QRect(390, 150, 181, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        nombre->setPalette(palette);
        QFont font;
        font.setPointSize(16);
        nombre->setFont(font);
        pushButton1 = new QPushButton(centralwidget);
        pushButton1->setObjectName("pushButton1");
        pushButton1->setGeometry(QRect(400, 480, 151, 41));
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
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(340, 190, 261, 261));
        RemoveUser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RemoveUser);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
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
        nombre->setText(QCoreApplication::translate("RemoveUser", "User to remove:", nullptr));
        pushButton1->setText(QCoreApplication::translate("RemoveUser", "Delete user", nullptr));
        pushButton1_2->setText(QCoreApplication::translate("RemoveUser", "Return", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoveUser: public Ui_RemoveUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOVEUSER_H
